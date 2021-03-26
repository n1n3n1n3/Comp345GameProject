#include <iostream>
using namespace std;
#include "mapLoader.h"
#include "map.h"

int main(){
	MapLoader *ml = new MapLoader("./maps/BirdsL.map");
//	MapLoader *ml = new MapLoader();
//	ml->setPath("./maps/BirdsL.map");
//	ml->loadMap();
//	ml->printBorders();
	ml->getMap()->validate();
//	vector<Continent*> c = ml->getMap()->getContinents();
//	cout << *ml << endl;
}