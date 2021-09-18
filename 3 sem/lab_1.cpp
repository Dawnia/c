#include <iostream>
#include <string>

using namespace std;

class Matrix{
	private:
		int lines, columns;
		int** main;
	
	public:
		bool full=false;
		
		Matrix(uint64_t r): Matrix(r, r){}
		Matrix(uint64_t lines, uint64_t columns): lines(lines), columns(columns){
			if(lines * columns){
				main = new int* [lines];
				for(int i = 0; i < columns; ++i){
					int* line = new int [columns];
					main[i] = line;
				}
			}
			
			else
				cout << '?';
		}
		
		~Matrix(){
			for(int i = 0; i < columns; ++i)
				delete[] main[i];
			delete[] main;
		}
		
		void write(uint64_t i, uint64_t j, int num){
			main[i][j] = num;
		}
		
		int get(uint64_t i, uint64_t j){
			return main[i][j];
		}
};


class Hash{
	private:
		uint64_t len=1;
		string** main;
		uint64_t* depth;
		uint64_t free_nums;
		
		uint64_t h_1(string s, uint64_t i=0){
			if(i == s.length())
				return 1;
			else
				return (s[i] + 101 * h_1(s, i+1)) % len;
		}
		
		void _add(string s, uint64_t pos){
			uint64_t curr_depth = depth[pos];
			uint64_t new_depth = curr_depth + 1;
			depth[pos] = new_depth;
			
			if(main[pos] != nullptr){
				string* new_ptr = new string[new_depth];
				for(uint64_t i = 0; i < curr_depth; ++i)
					new_ptr[i] = main[pos][i];
				
				new_ptr[new_depth-1] = s;
				delete[] main[pos];
				main[pos] = new_ptr;
			}
			
			else{
				string* new_ptr = new string[1];
				new_ptr[0] = s;
				main[pos] = new_ptr;
				--free_nums;
			}
		}
		
		void rehash(uint64_t new_len){
			uint64_t new_free_nums = new_len;
			string** new_main = new string*[new_len];
			uint64_t* new_depth = new uint64_t[new_len];
			for(int i = 0; i < new_len; ++i){
				new_depth[i] = 0;
				new_main[i] = nullptr;
			}
			
			string** last_main = main;
			uint64_t* last_depth = depth;
			uint64_t last_len = len;
			
			len = new_len;
			free_nums = new_free_nums;
			main = new_main;
			depth = new_depth;
			
			for(uint64_t i = 0; i < last_len; ++i){
				for(uint64_t j = 0; j < last_depth[i]; ++j){
					string s = last_main[i][j];
					uint64_t pos = h_1(s);
					_add(s, pos);
				}
			}
			
			for(uint64_t i = 0; i < last_len; ++i){
				if(last_depth[i])
					delete[] last_main[i];
			}
			
			delete[] last_main;
			delete[] last_depth;
		}
	
	public:
		Hash(){
			free_nums = len;
			main = new string*[len];
			depth = new uint64_t[len];
			for(int i = 0; i < len; ++i){
				depth[i] = 0;
				main[i] = nullptr;
			}
		}
		
		void add(string s){
			if(free_nums == 0)
				rehash(len * 2);
				
			uint64_t pos = h_1(s);
			_add(s, pos);
		}
		
		uint64_t* find(string s){
			uint64_t* nums = new uint64_t[2];
			uint64_t pos_1 = h_1(s);
			uint64_t d = depth[pos_1];
			bool trig_fill = false;
			if(d){
				for(uint64_t pos_2 = 0; pos_2 < d; ++pos_2){
					if(s == main[pos_1][pos_2]){
						nums[0] = pos_1;
						nums[1] = pos_2;
						trig_fill = true;
					}
				}
			}
			
			if(trig_fill)
				return nums;
			
			else{
				delete[] nums;
				return nullptr;
			}
		}
		
		void del(string s){
			uint64_t* nums = find(s);
			
			if(nums != nullptr){
				uint64_t first_num = nums[0];
				uint64_t second_num = nums[1];
				uint64_t d = depth[first_num];
				if(d){
					if(d == 1){
						delete[] main[first_num];
						main[first_num] = nullptr;
						++free_nums;
					}
					
					else{
						string* new_ptr = new string[d-1];
						for(int i = 0; i < d; ++i){
							if(i < second_num)
								new_ptr[i] = main[first_num][i];
							if(i > second_num)
								new_ptr[i-1] = main[first_num][i];
						}
						
						delete[] main[first_num];
						main[first_num] = new_ptr;
					}
					
					--depth[first_num];
				}
				
				else
					cout << "???";
				
				if(len > 1 && free_nums > len / 2)
					rehash(len / 2);
			}
			
			else
				cout << "???";
		}
		
		~Hash(){
			for(int i = 0; i < len; ++i){
				if(depth[i])
					delete[] main[i];
			}
			
			delete[] main;
			delete[] depth;
		}
};


class Hhash{
	private:
		const uint64_t _prime_delta_number = 1100101;
		uint64_t len=1;
		string* main;
		bool* depth;
		uint64_t free_nums;
		
		uint64_t h_1(string s, uint64_t i=0){
			if(i == s.length())
				return 1;
			else
				return (s[i] + 101 * h_1(s, i+1)) % len;
		}
		
		uint64_t h_2(string s, uint64_t i=0){
		if(i == s.length())
			return 1;
		else
			return (s[i] + 149 * h_2(s, i+1)) % len;
		}
		
		void _add(string s){
			uint64_t pos = h_1(s);
			uint64_t delta = pos%_prime_delta_number ? _prime_delta_number : _prime_delta_number + 1;
			for(; depth[pos]; pos = (pos + delta) % len);
			main[pos] = s;
			depth[pos] = true;
			--free_nums;
		}
		
		void rehash(uint64_t new_len){
			string* new_main = new string[new_len];
			bool* new_depth = new bool[new_len];
			uint64_t new_free_nums = new_len;
			for(uint64_t i = 0; i < new_len; ++i)
				new_depth[i] = false;
			
			uint64_t last_len = len;
			string* last_main = main;
			bool* last_depth = depth;
			
			len = new_len;
			main = new_main;
			depth = new_depth;
			free_nums = new_free_nums;
			
			for(uint64_t i = 0; i < last_len; ++i){
				if(last_depth[i]){
					string s = last_main[i];
					_add(s);
				}
			}
			
			delete[] last_main;
			delete[] last_depth;
		}
		
		public:
			Hhash(){
				len = 4;
				free_nums = len;
				main = new string[len];
				depth = new bool[len];
				for(uint64_t i = 0; i < len; ++i)
					depth[i] = false;
			}
			
			void add(string s){
				if(!free_nums)
					rehash(len * 2);
				
				_add(s);
			}
			
			uint64_t find(string s){
				uint64_t pos = h_1(s);
				uint64_t delta = pos%_prime_delta_number ? _prime_delta_number : _prime_delta_number + 1;
				for(; main[pos] != s; pos = (pos + delta) % len);
				if(depth[pos])
					return pos;
				else
					cout << "??";
			}
			
			void del(string s){
				uint64_t pos = find(s);
				depth[pos] = false;
				
				if(free_nums > len / 2 && len > 1)
					rehash(len / 2);
			}
			
			~Hhash(){
				delete[] main;
				delete[] depth;
			}
			
			void test1(){
				for(int i = 0; i < len; ++i)
					cout << main[i] << endl;
			}
			
			void test2(){
				for(int i = 0; i < len; ++i)
					cout << depth[i] << endl;
			}
			
			void test3(){
				cout << free_nums << endl;
			}
};


int main1(){
	Matrix matrix(2);
	for(int i = 0; i < 4; ++i)
		matrix.write(i/2, i%2, i);
	
	cout << matrix.get(0,0);
	cout << ' ';
	cout << matrix.get(0,1);
	cout << endl;
	cout << matrix.get(1,0);
	cout << ' ';
	cout << matrix.get(1,1);
	
	return 0;
}


int main2(){
	Hash hash;
	hash.add("FIRST");
	hash.add("FIRST");
	hash.add("SECOND");
	hash.add("THIRD");
	uint64_t* ns = hash.find("SECOND");
	cout << ns[0] << ' ' << ns[1] << endl;
	delete[] ns;
	ns = hash.find("FIRST");
	cout << ns[0] << ' ' << ns[1] << endl;
	delete[] ns;
	ns = hash.find("THIRD");
	cout << ns[0] << ' ' << ns[1] << endl;
	hash.del("SECOND");
	delete[] ns;
	ns = hash.find("SECOND");
	if(ns != nullptr)
		cout << ns[0] << ' ' << ns[1];
	delete[] ns;
	
	return 0;
}


int main3(){
	Hhash hash;
	hash.add("FIRST");
	hash.add("FIRST");
	hash.add("SECOND");
	uint64_t ns = hash.find("SECOND");
	hash.add("THIRD");
	hash.add("FOURTH");
	//hash.test1();
	//hash.test2();
	//hash.test3();
	cout << ns << endl;
	//ns = hash.find("FIRST");
	//cout << ns << endl;
	//ns = hash.find("THIRD");
	//cout << ns << endl;
	hash.del("SECOND");
	ns = hash.find("SECOND");
	
	return 0;
}


int main(){
//	main1();
//	main2();
	main3();
	
	return 0;
}
