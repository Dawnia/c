#include <iostream>
#include <map>
#include <string>

using namespace std;

int datize(string data){
	int date =
	(data[6] - '0')*10000000 +
	(data[7] - '0')*1000000 +
	(data[8] - '0')*100000 +
	(data[9] - '0')*10000 +
	(data[3] - '0')*1000 +
	(data[4] - '0')*100 +
	(data[0] - '0')*10 +
	(data[1] - '0');
		
	return date;
}


int main(){
	map<int, int> coll;
	int maxim = 0;
	
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i){
		string data;
		cin >> data;
		int num;
		cin >> num;
		
		int date = datize(data);
		
		if(coll.count(date)){
			if(coll[date] < num)
				coll[date] = num;
		}
		else
			coll.insert(make_pair(date, num));
	}
	
	int first = coll.begin() -> first;
	--first;
	
	int p;
	cin >> p;
	int arr[p];
	for(int i = 0; i < p; ++i){
		string data;
		cin >> data;
		int date = datize(data);
		arr[i] = 0;
		if(date > first){
			for(map<int, int> :: iterator it = coll.begin(); it -> first < date + 1 && it != coll.end(); ++it){
				int v = it -> second;
				if(arr[i] < v)
					arr[i] = v;
			}
		}
	}
	
	for(int i = 0; i < p; ++i){
		cout << arr[i];
		if(i < p-1)
			cout << endl;
	}
	
	return 0;
}
