#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main(){
	map<uint64_t, multiset<double>> res;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i){
		uint64_t id;
		double act;
		int m1; double m2;
		
		cin >> m1;
		cin >> id;
		cin >> act >> act >> act >> act;
		cin >> m2;
		
		if(res.count(id))
			res[id].insert(act);
		else{
			multiset<double> new_acts;
			new_acts.insert(act);
			res.insert(make_pair(id, new_acts));
		}
	}
	
	map<double, uint64_t> imps;
	for(map<uint64_t, multiset<double>> :: iterator i = res.begin(); i != res.end(); ++i){
		if(i -> second.size() > 1){
			uint64_t id = i -> first;
			double mi = *(i -> second.begin());
			double ma = *(i -> second.rbegin());
			double delta = ma - mi;
			imps.insert(make_pair(delta, id));
		}
	}
	
	map<double, uint64_t> :: iterator i = imps.begin();
	for(int j = 0; j < 3; ++j){
		cout << i -> second;
		++i;
		
		if(j < 2)
			cout << ' ';
	}
	
	return 0;
}

