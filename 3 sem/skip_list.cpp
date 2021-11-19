#include <iostream>
#include <iterator>
#include <list>

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
class SL_iterator: public std::iterator<std::bidirectional_iterator_tag, SL_knot<T>> {
private:
	SL_knot<T>* cur;

public:
	explicit SL_iterator(SL_knot<T>* cur): cur(cur){}
	SL_iterator(SL_iterator<T>& oth): SL_iterator(oth.cur){}
	SL_iterator(const SL_iterator<T>& oth) = default;
	SL_iterator& operator = (const SL_iterator<T>& oth) = default;
	
	SL_iterator<T>& operator ++ (){
		cur = cur -> next;
		return *this;
	}
	
	SL_iterator<T>& operator--() {
        cur = cur -> pre;
        return *this;
    }
    
    typename SL_iterator::reference* operator ~ () {
        return cur;
    }
    
    typename SL_iterator::reference operator * (){
    	return *cur;
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
	uint64_t max_len;
	uint64_t high;
	list<pair<SL_knot<T>*, bool>> floors;
	
	void resize(uint64_t new_len);
	
public:
	SkipList(){
		len = 0;
		high = 1;
		max_len = 8;
	}
	
	SkipList(SkipList<T>& oth): len(oth.len), high(oth.high), max_len(oth.max_len), floors(oth.floors){}
	SkipList(const SkipList<T>& oth) = default;
	SkipList& operator = (const SkipList<T>& oth) = default;
	SkipList(SkipList<T>&& oth) = default;
	SkipList& operator = (SkipList<T>&& oth) = default;
	
	
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

