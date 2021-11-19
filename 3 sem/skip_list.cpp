#include <iostream>
#include <iterator>

using namespace std;

template <class T>
struct SL_knot{
	T val;
	SL_knot<T>* pre;
	SL_knot<T>* next;
	SL_knot<T>* low;
	
	explicit SL_knot<T>(T val, SL_knot<T>* pre, SL_knot<T>* next, SL_knot<T>* low):
	val(val), pre(pre), next(next), low(low){}
	
	SL_knot<T>(T val, SL_knot<T>* pre, SL_knot<T>* next): SL_knot(val, pre, next, nullptr){}
	SL_knot<T>(T val, SL_knot<T>* pre): SL_knot(val, pre, nullptr){}
	SL_knot<T>(T val): SL_knot(val, nullptr){}
	
	SL_knot<T>(const SL_knot& other) = delete;
	SL_knot<T>(SL_knot&& other) = delete;
};

template <class T>
class SL_itertor: public std::iterator<std::bidirectional_iterator_tag, SL_knot<T>> {
private:
	SL_knot<T>* cur;

public:
	explicit SL_itertor(SL_knot<T>* cur): cur(cur){};
	
	SL_iterator<T>& operator ++ (){
		cur = cur -> next;
		return *this;
	}
	
	SL_iterator<T>& operator--() {
        current = current -> pre;
        return *this;
    }
    
    SL_knot<T>* operator ~ () {
        return cur;
    }
    
    T& operator * () {
        return cur -> val;
    }
    
    const T& operator * () const {
        return cur -> val;
    }
    
    bool operator == (const SL_iterator<T>& oth) const {
        return cur == oth.cur;
    }
    
    bool operator != (const SL_iterator<T>& oth) const {
        return cur != oth.cur;
    }
};


template <class T>
class SkipList {
private:
	uint64_t len;
	uint64_t high;
	SL_knot* floors;
	
	void resize(new_len);
	
public:
	SkipList()
};

/*
    SlipList& operator * () const {return *ptr;}
    pointer operator->() {return ptr}

    Itertor& operator++() {ptr++; return *this;}
    Itertor operator++(int) {return ++(*this);}

*/

/*class MySomeClass {
private:
    int* data;
    int len = 100;

public:
    Itertor begin() {return Itertor(&data);}
    Itertor end() {return Itertor(&data + len);}
};*/

