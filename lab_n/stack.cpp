#include <iostream>

using namespace std;

struct element{
	int value;
	element* next_element=NULL;
};

struct stack{
	unsigned long long int depth=0;
	element* first_element=NULL;
};


stack* stack_create(void){
	stack* new_stack = new stack;
	return new_stack;
}


void stack_push(stack* _stack, int new_val){
	element* new_elem = new element;
	new_elem -> value = new_val;
	
	if(_stack -> depth)
		new_elem -> next_element = _stack -> first_element;
	
	_stack -> first_element = new_elem;
	++(_stack -> depth);
}


void stack_clear(stack* _stack, unsigned long long int deep_clearing=0){
	unsigned long long int len = _stack -> depth;
	element* current_elem = _stack -> first_element;
	if(!deep_clearing)
		deep_clearing = len;
	
	for(unsigned long long int i = 0; i < deep_clearing && current_elem != NULL; ++i){
		element* next_elem = current_elem -> next_element;
		delete current_elem;
		current_elem = next_elem;
		--(_stack -> depth);
	}
	
	_stack -> first_element = current_elem;
}


int* stack_val(stack* _stack, unsigned long long int deep_pop=1){
	unsigned long long int len = _stack -> depth;
	element* current_elem = _stack -> first_element;
	if(!deep_pop)
		deep_pop = len;
	
	if(len){
		int* vals = new int[min(deep_pop, len)];
		for(unsigned long long int i = 0; i < deep_pop && current_elem != NULL; ++i){
			vals[i] = current_elem -> value;
			element* next_elem = current_elem -> next_element;
			current_elem = next_elem;
		}
		return vals;
	}
	
	return NULL;	
}


int* stack_pop_some(stack* _stack, unsigned long long int deep_pop=1){
	unsigned long long int len = _stack -> depth;
	element* current_elem = _stack -> first_element;
	if(!deep_pop)
		deep_pop = len;
	
	if(len){
		int* vals = new int[min(deep_pop, len)];
		for(unsigned long long int i = 0; i < deep_pop && current_elem != NULL; ++i){
			vals[i] = current_elem -> value;
			element* next_elem = current_elem -> next_element;
			delete current_elem;
			current_elem = next_elem;
			--(_stack -> depth);
		}
		
		_stack -> first_element = current_elem;
		return vals;
	}

	return NULL;	
}


int stack_pop_one(stack* _stack){
	if(_stack -> depth){
		element* curr_first = _stack -> first_element;
		element* next_first = curr_first -> next_element;
		int val = curr_first -> value;
		
		_stack -> first_element = next_first;
		--(_stack -> depth);
		delete curr_first;
		return val;
	}
}


int main(){
	stack* nov = stack_create();
	for(int i = 0; i < 5; ++i)
		stack_push(nov, i);
	
	for(int i = 0; i < 5; ++i){
		int* val = stack_pop_some(nov);
		cout << *val << ' ';
	}
	
	cout << endl;
	
	for(int i = 0; i < 5; ++i)
		stack_push(nov, 1);
		
	stack_clear(nov, 3);
	int* arr = stack_pop_some(nov, 0);
	
	for(int i = 0; i < 2; ++i)
		cout << arr[i] << ' ';
	
	delete nov;
	
	return 0;
}
