#include <iostream>
#include <iterator>
#include <list>
#include <cassert>

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
class SkipList;

template <class T>
class SL_iterator: public std::iterator<std::bidirectional_iterator_tag, SL_knot<T>> {
private:
	SkipList<T>& thelist;
	SL_knot<T>* cur;
	bool ifend;

public:
	explicit SL_iterator(SL_knot<T>* cur, SkipList<T>& thelist): cur(cur), thelist(thelist){
		if(cur == nullptr)
			ifend = true;
		else
			ifend = false;
	}
	SL_iterator(SL_iterator<T>& oth): SL_iterator(oth.cur, oth.thelist){}
	SL_iterator(const SL_iterator<T>& oth) = default;
	SL_iterator& operator = (const SL_iterator<T>& oth) = default;
	
	SL_iterator<T>& operator ++ (){
		if(!ifend)
			cur = cur -> next;
		return *this;
	}
	
	SL_iterator<T>& operator--() {
		if(!ifend)
        	cur = cur -> pre;
        else
        	return thelist.floor[0] -> second;
        
        return *this;
    }
    
    typename SL_iterator<T>::reference* operator ~ () {
    	assert(!ifend);
        return cur;
    }
    
    T& operator * () {
    	assert(!ifend);
        return cur -> val;
    }
    
    const T& operator * () const {
    	assert(!ifend);
        return cur -> val;
    }
    
    bool operator == (const SL_iterator<T>& oth) const {
        return cur == oth.cur && thelist == oth.thelist;
    }
    
    bool operator != (const SL_iterator<T>& oth) const {
        return cur != oth.cur || thelist != oth.thelist;
    }
    
protected:
	SL_iterator<T>& get_lower(){
		assert(!ifend);
		cur = cur -> low;
		return *this;
	}
};


template <class T>
struct Floor {
private:
	uint64_t level;
	SL_iterator<T> first;
	SL_iterator<T> last;
	bool filled;
	
	Floor(SL_iterator<T> first): first(first), last(first){
		filled = false;
	}
	
	FLoor(){
		filled = false;
	}
};


template <class T>
class SkipList {
private:
	uint64_t len;
	uint64_t max_len;
	uint64_t high;
	double p;
	list<Floor<T>> floors;
	
	void resize(uint64_t new_len);
	
public:
	SkipList(){
		len = 0;
		high = 1;
		max_len = 8;
		p = 0.5;
	}
	friend class SL_iterator<T>;
	
	SkipList(SkipList<T>& oth): len(oth.len), high(oth.high), max_len(oth.max_len), floors(oth.floors), p(oth.p){}
	SkipList(const SkipList<T>& oth) = default;
	SkipList& operator = (const SkipList<T>& oth) = default;
	SkipList(SkipList<T>&& oth) = default;
	SkipList& operator = (SkipList<T>&& oth) = default;
	
	SL_iterator<T> end(){
		return SL_iterator<T>(nullptr);
	}
	
	SL_iterator<T> begin(){
		if(len)
			return floors[0].first;
		else
			return SL_iterator<T>(nullptr, this);
	}
	
	SL_iterator<T>& find(T key){
		Floor<T>& last_floor = floors.back();
		SL_iterator<T> i = last_floor.first;
		for(i; i != this -> end(); ++i){
			if(*i > key){
				--i;
				if(i != floors.end())
					i.get_lower;
			}
			else if(*i == key)
				break;
		}
		return i;
	}
	
	
};


