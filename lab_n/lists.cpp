#include <iostream>

using namespace std;

struct element{
	int value;
	element* next_element=NULL;
	element* previous_element=NULL;
};

struct list{
	unsigned int length_of_list=0;
	element* first_element=NULL;
	element* last_element=NULL;
};


// создаёт списочек (защита от дурака похерена)
list* create_list(int* values, unsigned int len){
	list* new_list = new list;
	element* current_elem = new element;
	new_list -> first_element = current_elem;
	new_list -> length_of_list = len;
	
	for(int i = 0; i < len; ++i){
		current_elem -> value = values[i];
		
		if(i < len-1){
			element* next_elem = new element;
			next_elem -> previous_element = current_elem;
			current_elem -> next_element = next_elem;
			current_elem = next_elem;
		}
		else
			new_list -> last_element = current_elem;
	}
	
	return new_list;
}


void apply_end(list* _list, int new_val){
	element* new_elem = new element;
	new_elem -> value = new_val;
	element*& c_l_elem = _list -> last_element;
	new_elem -> previous_element = c_l_elem;
	c_l_elem -> next_element = new_elem;
	_list -> last_element = new_elem;
	++(_list -> length_of_list);
}


void apply_inception(list* _list, int new_val){
	element* new_elem = new element;
	new_elem -> value = new_val;
	element*& c_l_elem = _list -> first_element;
	new_elem -> next_element = c_l_elem;
	c_l_elem -> previous_element = new_elem;
	_list -> first_element = new_elem;
	++(_list -> length_of_list);
}


// выдаёт ссылку на элемент списка
element* list_elem(list* _list, unsigned int pos){
	unsigned int len = _list -> length_of_list;
	
	if(pos < len){
		element* current_elem;
		if(pos < (len + 1) / 2){
			current_elem = _list -> first_element;
			for(int i = 0; i < pos; ++i)
				current_elem = current_elem -> next_element;
		}
		else{
			current_elem = _list -> last_element;
			for(int i = len-1; i > pos; --i)
				current_elem = current_elem -> previous_element;
		}
		
		return current_elem;
	}
	
	return NULL;
}


// выдаёт значение
int list_val(list* _list, unsigned int pos){
	unsigned int len = _list -> length_of_list;
	if(pos < len){
		element* needed_elem = list_elem(_list, pos);
		int val = needed_elem -> value;
		
		return val;
	}
}


// добавляет значение в  произвольное место (возможно, в самый конец)
void apply_val(list* _list, unsigned int pos, int new_val){
	unsigned int len = _list -> length_of_list;
	
	if(!pos){
		apply_inception(_list, new_val);
	}
	else if(pos == len){
		apply_end(_list, new_val);
	}
	else if(pos < len){
		element* new_elem = new element;
		element* pre_elem = list_elem(_list, pos-1);
		element* nex_elem = list_elem(_list, pos);
		
		new_elem -> value = new_val;
		pre_elem -> next_element = new_elem;
		new_elem -> next_element = nex_elem;
		nex_elem -> previous_element = new_elem;
		new_elem -> previous_element = pre_elem;
		
		++(_list -> length_of_list);
	}
}


// нерабочая remove, которая пока работает только для списков длины 1 и 2
void remove(list* _list, int val){
	unsigned int len = _list -> length_of_list;
	element* current_elem = _list -> first_element;
	
	if(len == 1){
		int current_val = list_val(_list, 0);
		if(current_val == val){
			delete[] current_elem;
			_list -> first_element = _list -> last_element = 0;
		}
	}
	
	else if(len == 2){
		int current_val = list_val(_list, 0);
		if(current_val == val){
			delete[] current_elem;
			_list -> first_element = _list -> last_element;
			remove(_list, val);
		}
		else{
			element* next_elem = current_elem -> next_element;
			int next_val = next_elem -> value;
			if(next_val == val){
				delete[] next_elem;
				_list -> last_element = _list -> first_element;
			}
		}
	}
	else{
		for(int i = 0; i < len; ++i){
			int current_val = list_val(_list, i);
			if(current_val == val){
				if(i+2 > len){
					
				}
			}
		}
	}
}


// неэффективное по памяти слияние списков (можно было массив не создавать, но пока так), а главное -- ненужное,
// потому что в сортировке я это использовать не собирался, но пусть будет.
list* merge_lists(list* list_1, list* list_2){
	unsigned int len_1 = list_1 -> length_of_list;
	unsigned int len_2 = list_2 -> length_of_list;
	unsigned int len = len_1 + len_2;
	int* values = new int[len];
	
	for(int i = 0; i < len_1; ++i)
		values[i] = list_val(list_1, i);
	for(int i = 0; i < len_2; ++i)
		values[i] = list_val(list_2, i);
	
	list* nova_list = create_list(values, len);
	delete[] values;
	
	return nova_list;
}


void printlist(list* _list){
	unsigned int len = _list -> length_of_list;
	element* current_elem = _list -> first_element;
	
	for(int i = 0; i < len; ++i){
		int currentvalue = current_elem -> value;
		cout << currentvalue;
		if(i < len-1)
			cout << endl;
		
		if(i < len-1){
			element* next_elem = current_elem -> next_element;
			current_elem = next_elem;
		}
	}
}


int main(){
	
	return 0;
}
