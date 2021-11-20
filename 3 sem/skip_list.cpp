#include <iostream>
#include <iterator>
#include <list>
#include <cassert>

using namespace std;

template <class T>
T vl(list<T>& thelist, uint64_t num){
	auto it = thelist.begin();
	for(uint64_t i = 0; i < num && it != thelist.end(); ++i, ++it);
	return *it;
}

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
	SL_iterator(const SL_iterator<T>& oth): SL_iterator(oth.cur, oth.thelist){}
	
	friend class SkipList<T>;
	
	SL_iterator& operator = (const SL_iterator<T>& oth){
		ifend = oth.ifend;
		cur = oth.cur;
		thelist = oth.thelist;
		
		return *this;
		}
	
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
    
    SL_knot<T>* operator ~ () {
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
	uint64_t level;
	SL_iterator<T> first;
	SL_iterator<T> last;
	const SkipList<T>& thelist;
	bool filled;
	
	Floor(uint64_t level, SL_iterator<T>& first, const SkipList<T>& thelist): level(level), first(first), last(first), thelist(thelist){
		filled = false;
	}
	
	Floor(uint64_t level, const SkipList<T>& thelist): Floor(level, thelist.end(), thelist){}
};


template <class T>
class SkipList {
private:
	uint64_t len;
	uint64_t max_len;
	uint64_t max_height;
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
		
		max_height = 0;
		for(uint64_t i = max_len; i > 1; i /= 2)
			++max_height;
	}
	
	SkipList(SkipList<T>& oth): len(oth.len), high(oth.high), max_len(oth.max_len), floors(oth.floors), p(oth.p){}
	SkipList(const SkipList<T>& oth) = default;
	SkipList& operator = (const SkipList<T>& oth) = default;
	SkipList(SkipList<T>&& oth) = default;
	SkipList& operator = (SkipList<T>&& oth) = default;
	
	friend class SL_iterator<T>;
	
	SL_iterator<T> end(){
		return SL_iterator<T>(nullptr, *this);
	}
	
	SL_iterator<T> begin(){
		if(len)
			return floors[0].first;
		else
			return SL_iterator<T>(nullptr, *this);
	}
	
	SL_iterator<T>& find(T key){
		SL_iterator<T> i = end();
		
		if(len){
			Floor<T>& last_floor = floors.back();
			i = last_floor.first;
			uint64_t curr_level = last_floor.level;
			for(i; i != end(); ++i){
				if(*i > key){
					if(i != end() && i != vl(floors, curr_level).first){
						--i;
						i.get_lower();
					}
					
					else if(i != end() && curr_level)
						i = vl(floors, curr_level - 1).first;
					
					else
						i = end();
						
					--curr_level;
				}
				
				else if(*i == key)
					break;
			}
			
			for(curr_level; curr_level > 0; --curr_level)
				i.get_lower();
		}
		
		return i;
	}
	
	void insert(T val){
		if(!len){
			SL_knot<T>* first_knot = new SL_knot<T>(val);
			SL_iterator<T> first_it = SL_iterator<T>(first_knot, *this);
			Floor<T> first_floor(0, first_it, *this);
			floors.push_back(first_floor);
			++len;
		}
		
		else{
			
		}
	}
};


int main(){
	SkipList<int> mylist;
	mylist.insert(5);
	auto it = mylist.find(5);
	
	return 0;
}

