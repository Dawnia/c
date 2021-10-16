#include <iostream>

using namespace std;

template <class T>
class Grid {
	private:
		T* memory;
		uint64_t x_size;
		uint64_t y_size;
		uint64_t size;
	
	public:
		Grid(uint64_t x_size, uint64_t y_size): x_size(x_size), y_size(y_size){
			memory = new T[x_size * y_size];
			size = x_size * y_size;
		}
		
		uint64_t get_xsize() const{
			return x_size;
		}
		
		uint64_t get_ysize() const{
			return y_size;
		}
		
		T operator()(uint64_t x, uint64_t y) const{
			if(x < x_size && y < y_size)
				return memory[x * x_size + y];
			else{
				cout << "invalid reference, value (0, 0) returned" << endl;
				return memory[0];
			}
		}
		
		T& operator()(uint64_t x, uint64_t y){
			if(x < x_size && y < y_size)
				return memory[x * x_size + y];
			else{
				cout << "invalid reference, value (0, 0) returned" << endl;
				return memory[0];
			}
		}
		
		Grid& operator=(T val){
			for(uint64_t i = 0; i < size; ++i)
				memory[i] = val;
			
			return *this;
		}
		
		friend ostream& operator<<(ostream& out, Grid const& g){
			for(uint64_t i = 0; i < g.size; ++i)
				out << g.memory[i] << endl;
			return out;
		}
		
		friend istream& operator>>(istream& in, Grid& g){
			for(uint64_t i = 0; i < g.size; ++i)
				in >> g.memory[i];
			return in;
		}
		
		~Grid(){
			delete[] memory;
		}
};


int main(){
	Grid<int> g(2, 2);
	g = 2;
	int a = g(0, 0);
	cout << a << ' ';
	int b = g(0, 1);
	cout << b << endl;
	cout << g << endl;
	cin >> g;
	cout << g;
	int c = g(5, 8);
	cout << c;
	
//	g.~Grid();
	
	return 0;
}

