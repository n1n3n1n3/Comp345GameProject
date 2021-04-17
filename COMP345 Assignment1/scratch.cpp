#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
	
	
	vector<int> x;
	x.assign({1,2,3,4,5});
	for (int i : x) {
		cout << i << endl;
	
	}
	
	int temp = x.at(0);
	x.at(0) = 3;
	cout << x.size();
	
}