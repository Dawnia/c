#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int reverse(int n){
	int new_n = 0;
	for(short unsigned int i = 0; i < sizeof(n) << 3; ++i){
		int trig = 1 << i;
		short unsigned int new_bit = n & trig;
		new_bit = new_bit >> i;
		new_n = new_bit + (new_n << 1);
	}
	
	return new_n;
}

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

//--------------------------------------------------------------------------------------------------------------------------------------------------


struct knot_int{
	int value;
	uint64_t attached_quantity = 0;
	knot_int* left = nullptr;
	knot_int* right = nullptr;
	knot_int* pre_knot = nullptr;
	
	void applyval(int val);
	int balance(void);
	
};


int knot_int::balance(void){
	uint64_t r_q = 0;
	uint64_t l_q = 0;
	if(right != nullptr)
		r_q = this -> right -> attached_quantity + 1;
	if(left != nullptr)
		r_q = this -> left -> attached_quantity + 1;
	
	return r_q - l_q;
}


void knot_int::applyval(int val){
	++attached_quantity;
	
	if(val > value){
		if(right != nullptr){
			this -> right -> applyval(val);
		}
		
		else{
			knot_int* new_knot = new knot_int;
			new_knot -> value = val;
			new_knot -> pre_knot = this;
			this -> right = new_knot;
		}
	}
	
	else{
		if(left != nullptr)
			this -> left -> applyval(val);
		
		else{
			knot_int* new_knot = new knot_int;
			new_knot -> value = val;
			new_knot -> pre_knot = this;
			this -> left = new_knot;
		}
	}
	
	knot_int* current_knot = this;
	// for(current_knot; current_knot == nullptr ? false : abs(current_knot -> balance()) < 2; current_knot = current_knot -> pre_knot)
}




struct tree_search{
	knot_int* root = nullptr;
	uint64_t knot_quantity = 0;
	
	void applyval(int val);
	knot_int* search(int val);
	void delete_knot(knot_int* deleting_knot);
	void delete_val(int val);
	void print(void);
};


void tree_search::applyval(int val){
	++(this -> knot_quantity);
	
	if(this -> root != nullptr)
		this -> root -> applyval(val);
	
	else{
		knot_int* new_root = new knot_int;
		new_root -> value = val;
		this -> root = new_root;
	}
}


knot_int* tree_search::search(int val){
	knot_int* current_knot = this -> root;
	while(current_knot != nullptr){
		int current_value = current_knot -> value;
		
		if(current_value == val)
			return current_knot;
		
		else if(current_value > val)
			current_knot = current_knot -> left;
		
		else
			current_knot = current_knot -> right;
	}
	
	cout << endl << "The value has not been founded" << endl;
	return nullptr;
}


void tree_search::delete_knot(knot_int* deleting_knot){
	if(deleting_knot != nullptr){
		--this -> knot_quantity;
		int deleting_val = deleting_knot -> value;
		knot_int* pre_knot_deleting = deleting_knot -> pre_knot;
		int pre_deleting_val = pre_knot_deleting -> value;
		knot_int* nova_knot;
		--(pre_knot_deleting -> attached_quantity);
		
		knot_int* right_knot = deleting_knot -> right;
		knot_int* left_knot = deleting_knot -> left;
		if(right_knot != nullptr){
			knot_int* current_knot = right_knot;
			while(current_knot -> left != nullptr){
				--(current_knot -> attached_quantity);
				current_knot = current_knot -> left;
			}
			
			nova_knot = current_knot;
		}
		
		else
			nova_knot = deleting_knot -> left;
		
		if(nova_knot != nullptr){
			nova_knot -> right = right_knot;
			nova_knot -> left = left_knot;
			nova_knot -> pre_knot -> left = nullptr;
		}
		
		if(pre_deleting_val < deleting_val)
			pre_knot_deleting -> right = nova_knot;
		
		else
			pre_knot_deleting -> left = nova_knot;
		
		if(right_knot != nullptr)
			right_knot -> pre_knot = nova_knot;
		
		if(left_knot != nullptr)
			left_knot -> pre_knot = nova_knot;
		
		delete deleting_knot;
	}
	
	else
		return;
}


void tree_search::delete_val(int val){
	knot_int* deleting_knot = this -> search(val);
	delete_knot(deleting_knot);
}


// It doesn't work :(((((
void tree_search::print(void){
	int count = this -> knot_quantity;
	
	for(int level = 0; count > 0; ++level){
		knot_int* current_knot = this -> root;
		
		for(int i = 0; i < pow(2, level); ++i){
			int rev_i = reverse(i);
			
			for(int j = 1; j < level; ++j){
				if(current_knot != nullptr){
					bool current_bit = (rev_i & (1 << j - 1)) >> (j - 1);
					if(current_bit)
						current_knot = current_knot -> right;
					else
						current_knot = current_knot -> left;
				}
				
				else{
					cout << ' ';
					break;
				}
			}
			
			if(current_knot != nullptr){
				cout << (current_knot -> value) << ' ';
				--count;
			}
			
			current_knot = this -> root;
		}
		
		cout << endl << "//////" << endl << count << endl << "//" << endl;
	}
}



//------------------------------------------------------------------------------------------------------------------------------------------

struct knot_string{
	string function;
	knot_string* right;
	knot_string* left;
	
	void diff(void){
		
	}
};

struct tree_diff{
	knot_string* root = nullptr;
	
	void tree_applyval(string line){
		
	}
};
//----------------------------------------------------------


int main(){
	tree_search mytree;
	mytree.applyval(5);
	mytree.applyval(4);
	mytree.applyval(6);
	mytree.applyval(3);
	//mytree.applyval(4);
	//mytree.applyval(7);
	//mytree.applyval(8);
	//mytree.applyval(1);
	//cout << (mytree.root -> value) << endl;
	//cout << mytree.knot_quantity << endl;
	cout << mytree.root -> right -> value << endl;
	cout << mytree.root -> left -> value << endl;
	mytree.delete_val(4);
	if(mytree.root -> left == nullptr)
		cout << "YES";
	else
		cout << mytree.root -> left -> value;
	//mytree.print();
	
	return 0;
}
