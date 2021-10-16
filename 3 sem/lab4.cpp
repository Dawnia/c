#include <iostream>
#include <string>

using namespace std;

template <class T>
T maximum(T one, T two){
	if(one > two)
		return one;
	else
		return two;
}


template <class D>
D fucktorial(D chislo){
	if(chislo < 1)
		return 1;
	
	return chislo * fucktorial(chislo - 1);
}


template <class C>
struct CaterpillarChain {
		C value;
		CaterpillarChain* next_chain=nullptr;
};


template <class E>
class Vector {
	private:
		uint64_t len;
		CaterpillarChain <E>* first_element;
		CaterpillarChain <E>* last_element;
		
	public:
		Vector(){
			len = 0;
		}
		
		void append(E new_val){
			if(len){
				CaterpillarChain <E>* new_element = new CaterpillarChain <E>;
				new_element -> value = new_val;
				last_element -> next_chain = new_element;
				last_element = new_element;
			}
			
			else{
				first_element = new CaterpillarChain <E>;
				first_element -> value = new_val;
				last_element = first_element;
			}
			
			++len;
		}
		
		E getval(uint64_t num){
			CaterpillarChain <E>* current_elem = first_element;
			if(num == len - 1)
				return last_element -> value;
			
			for(int i = 0; i < num; ++i)
				current_elem = current_elem -> next_chain;
			
			return current_elem -> value;
		}
		
		void wipe(void){
			if(len > 1){
				CaterpillarChain <E>* current_elem = first_element;
				current_elem = first_element -> next_chain;
				delete first_element;
				first_element = current_elem;
				wipe();
			}
			else{
				delete first_element;
				first_element = nullptr;
				last_element = nullptr;
				len = 0;
			}
		}
			
};

int main(){
	string a, b, c;
	a = "a";
	b = "bca";
	c = maximum(a, b);
	cout << c << endl;
	cout << fucktorial(5.32) << endl;
	
	Vector<int> vector;
	vector.append(3);
	int val = vector.getval(0);
	cout << val << endl;
	
	return 0;
}
