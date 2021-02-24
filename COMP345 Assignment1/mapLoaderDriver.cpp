#include <iostream>
using namespace std;
#include "mapLoader.h"
#include "map.h"

int main(){
	MapLoader *ml = new MapLoader("Birds.map");

	vector<vector<string>> lc = ml->getListContinents();
	vector<vector<string>> lr = ml->getListRegions();
	vector<vector<string>> lb = ml->getListBorders();
	Map *m = new Map(lc, lr, lb);
	cout << m->validate() << endl;
}