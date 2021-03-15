#include <iostream>
#include <string>

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


int string_reader(string inp){
	if(!inp.empty()){
		int value = 0;
		char start_iteration = 0;
		char factor = 1;
		int len = inp.length();
		if(inp[0] == '-' && len-1){
			++start_iteration;
			factor = -1;
		}
		
		for(int i = start_iteration; i < len; ++i){
			value += inp[i] - 48;
			for(int j = 1; j < len - i; ++j)
				value *= 10;
		}
		
		return value * factor;
	}
}


void demonstration(stack* _stack){
	int len = _stack -> depth;
	int arr[len];
	for(int i = 0; i < len; ++i)
		arr[i] = stack_pop_one(_stack);
	
	for(int i = len - 1; i > -1; --i){
		cout << arr[i];
		if(i > 0)
			cout << ' ';
		else
			cout << endl;
		
		stack_push(_stack, arr[i]);
	}
}


int main(){
	string inp;
	bool trig_correct_input = true;
	bool trig_continue = true;
	bool trig_demonstration = true;
	stack* symbs = stack_create();
	
	cout <<
	"You able to enter any positive or negative numbers" <<
	endl <<
	"And also any operations of '*', '+', '-', '/'" <<
	endl <<
	"The equal sign (=) is used as an end of the entering" <<
	// endl <<
	// "This is caused by an author's conviction that computer is needless for calculations with zero." <<
	endl <<
	endl <<
	"There is a demontration of the entered values provided" <<
	endl <<
	"And you may turn it off at any moment (just enter OF_DEM)" <<
	endl <<
	"Or renew it (ON_DEM)" <<
	endl <<
	endl <<
	"Przyjemne uzytkowanie!" <<
	endl <<
	"//////////" <<
	endl <<
	endl;
	
	while(trig_continue){
		trig_correct_input = true;
		cin >> inp;
		int new_val;
		
		if(inp == "ON_DEM"){
			trig_demonstration = true;
			cout <<
			endl <<
			"//////////" <<
			endl <<
			"Demonstration turned on" <<
			endl <<
			"//////////" <<
			endl <<
			endl;
			
			trig_correct_input = false;
		}
		
		else if(inp == "OF_DEM"){
			trig_demonstration = false;
			cout <<
			endl <<
			"//////////" <<
			endl <<
			"Demonstration turned off" <<
			endl <<
			"//////////" <<
			endl <<
			endl;
			
			trig_correct_input = false;
		}
		
		else if(inp == "*" || inp == "+" || inp == "-" || inp == "/"){
			if(symbs -> depth > 1){
				int pre_val_1 = stack_pop_one(symbs);
				int pre_val_2 = stack_pop_one(symbs);
				char inp_light = char(inp[0]);
				
				switch(inp_light){
					case '*':
						new_val = pre_val_1 * pre_val_2;
						break;
						
					case '+':
						new_val = pre_val_1 + pre_val_2 ;
						break;
					
					case '-':
						new_val = pre_val_1 - pre_val_2 ;
						break;
					
					case '/':
						if(pre_val_2)
							new_val = pre_val_1 / pre_val_2 ;
						else{
							cout <<
							endl <<
							"//////////" <<
							endl <<
							"You can not devide by zero" <<
							endl <<
							"//////////" <<
							endl <<
							endl;
							stack_push(symbs, pre_val_2);
							stack_push(symbs, pre_val_1);
							
							trig_correct_input = false;
						}
						break;
				}
			}
			
			else{
				cout <<
				endl <<
				"//////////" <<
				endl <<
				"Incorrect input" <<
				endl <<
				"Please, re-inter the last symbol" <<
				endl <<
				"//////////" <<
				endl <<
				endl;
				
				trig_correct_input = false;
			}
		}
		
		else if(inp != "=")
			new_val = string_reader(inp);
			
		else if(symbs -> depth != 1){
			cout <<
			endl <<
			"//////////" <<
			endl <<
			"You can not stop entering here" <<
			endl <<
			"//////////" <<
			endl <<
			endl;
			trig_correct_input = false;
		}
		
		else{
			char new_inp;
			cout <<
			endl <<
			"//////////" <<
			endl <<
			"Please enter '=' once more if you want to get a result" <<
			endl <<
			"Or enter anything else if you want to continue" <<
			endl <<
			"//////////" <<
			endl <<
			endl;
			
			cin >> new_inp;
			if(new_inp == '='){
				int result = stack_pop_one(symbs);
				cout << endl << "Result is: " << result << endl;
				delete symbs;
				trig_continue = false;
			}
			
			else{
				cout <<
				endl <<
				"//////////" <<
				endl <<
				"You may continue" <<
				endl <<
				"//////////" <<
				endl <<
				endl;
				
				trig_correct_input = false;
			}
		}
		
		if(trig_continue && trig_correct_input)
			stack_push(symbs, new_val);
		
		if(trig_continue && trig_demonstration)
			demonstration(symbs);
	}
	
	return 0;
}

