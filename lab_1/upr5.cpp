#include <iostream>

using namespace std;

int main(){
	int N;
	cin >> N;
	for(int i = 1; i <= N; ++i){
		for(int j = N; j >= i; --j){
			cout << '*';
		}
		if(i != N)
			cout << endl;
	}
	
	return 0;
}
