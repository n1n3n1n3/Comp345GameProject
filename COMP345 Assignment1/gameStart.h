
#ifndef GAMESTART_H
#define GAMESTART_H

#include <iostream>

#include "map.h"
#include "mapLoader.h"

using namespace std;

class GameStart {
private:
	
	//Pointers to bjects of territory on Map, hand of Cards, and Bid obkject
	string path;
	//list of map files
	vector<string> mapFiles;
	//Output
	MapLoader *mapLoader;
	Map *map;
	
	vector<Player*> players;
	
	friend std::ostream& operator<<(std::ostream&, const GameStart&);
	
public:
	
	//Constructor that sets starting coins, copy, assignment
	GameStart();
//	~GameStart();
	
	//functions
	void loadMapFilePaths();
	void selectMap();
	void enterNbPlayers();
};

#endif