#include <iostream>

using namespace std;

struct element{
	int value;
	element* next_element=nullptr;
	element* previous_element=nullptr;
};

struct queue{
	uint64_t depth=0;
	element* first_element=nullptr;
	element* last_element=nullptr;
	
	void push(int new_val){
		element* new_elem = new element;
		new_elem -> value = new_val;
		new_elem -> previous_element = first_element;
		
		if(depth)
			first_element -> next_element = new_elem;
		
		else
			last_element = new_elem;
		
		first_element = new_elem;
		++depth;
	}
	
	
	void clear(uint64_t deep_clearing=0){
		element* current_elem = last_element;
		if(!deep_clearing){
			deep_clearing = depth;
		}
		
		for(uint64_t i = deep_clearing; i > 0 && current_elem != nullptr; --i){
			element* prev_elem = current_elem -> previous_element;
			delete current_elem;
			current_elem = prev_elem;
			--depth;
		}
		
		last_element = current_elem;
	}
	
	
	int pop(void){
		element* current_elem = last_element;
		
		if(depth){
			int val = last_element -> value;
			element* new_last_element = last_element -> next_element;
			delete last_element;
			last_element = new_last_element;
			return val;
		}
	}
};


queue* queue_create(void){
	queue* new_queue = new queue;
	return new_queue;
}


int main(){
	return 0;
}
