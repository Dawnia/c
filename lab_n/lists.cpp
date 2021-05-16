#include <iostream>
#include <chrono>

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


// создаёт списочек
list* list_create(unsigned int len, int* values=NULL){
	list* new_list = new list;
	if(len){
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
		}
		
		new_list -> last_element = current_elem;
	}
	
	return new_list;
}


void list_append(list* _list, int new_val){
	element* new_elem = new element;
	new_elem -> value = new_val;
	element*& c_l_elem = _list -> last_element;
	new_elem -> previous_element = c_l_elem;
	c_l_elem -> next_element = new_elem;
	_list -> last_element = new_elem;
	++(_list -> length_of_list);
}


void list_appinception(list* _list, int new_val){
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
void list_apply(list* _list, unsigned int pos, int new_val){
	unsigned int len = _list -> length_of_list;
	
	if(!pos){
		list_appinception(_list, new_val);
	}
	
	else if(pos == len){
		list_append(_list, new_val);
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
void list_remove(list* _list, int val){
	unsigned int len = _list -> length_of_list;
	element* current_elem = _list -> first_element;
	
	if(len == 1){
		int current_val = list_val(_list, 0);
		if(current_val == val){
			delete current_elem;
			_list -> first_element = _list -> last_element = 0;
		}
	}
	
	else if(len == 2){
		int current_val = list_val(_list, 0);
		if(current_val == val){
			delete current_elem;
			_list -> first_element = _list -> last_element;
			list_remove(_list, val);
		}
		else{
			element* next_elem = current_elem -> next_element;
			int next_val = next_elem -> value;
			if(next_val == val){
				delete next_elem;
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

// Здесь наблюдаем слияние
list* list_merge(list* list_1, list* list_2){
	if(list_1 != NULL, list_2 != NULL){
		unsigned int len_1 = list_1 -> length_of_list;
		unsigned int len_2 = list_2 -> length_of_list;
		unsigned int len = len_1 + len_2;
		list* new_list = new list;
		new_list -> length_of_list = len;
		new_list -> first_element = list_1 -> first_element;
		new_list -> last_element = list_2 -> last_element;
		
		element* el1 = list_1 -> last_element;
		element* el2 = list_2 -> first_element;
		el1 -> next_element = el2;
		el2 -> previous_element = el1;
		
		return new_list;
	}
}


/*list* list_copy(list* _list){
	list* nov = new list;
	unsigned int len = _list -> length_of_list;
	element* current_element = _list -> first_element;
	nov -> first_element = current_element;
	
	for(int i = 0; i < len; ++i){
		
	}
}*/


void list_merge_sort(list* _list){
	
}


void list_print(list* _list){
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
	int arr[] = {1};
	/*list* nl = list_create(5, arr);
	list_print(nl);
	cout << endl << endl;
	list_apply(nl, 5, 6);
	list_print(nl);*/
	
	list* nov = list_create(1, arr);
	auto start_time = std::chrono::steady_clock::now();
	
	for(int i = 0; i < 10000; ++i){
		auto time_1 = std::chrono::steady_clock::now();
		list_append(nov, i);
		auto time_2 = std::chrono::steady_clock::now();
		auto dur = time_2 - time_1;
		cout << i+1 << ": " << std::chrono::duration_cast<std::chrono::microseconds>(dur).count() << endl;
	}
	
	auto stop_time = std::chrono::steady_clock::now();
	cout << std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time).count();
	
	return 0;
}

