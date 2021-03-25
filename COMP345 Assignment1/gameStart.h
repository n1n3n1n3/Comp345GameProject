
#ifndef GAMESTART_H
#define GAMESTART_H

#include <iostream>

#include "map.h"
#include "mapLoader.h"
#include "Cards.h"

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
	int nbPlayers;
	
	Deck *deck;
	
	friend std::ostream& operator<<(std::ostream&, const GameStart&);
	
public:
	
	//Constructor that sets starting coins, copy, assignment
	GameStart();
//	~GameStart();
	
	
	//functions
	void loadMapFilePaths();
	void selectMap();
	void setPlayers();
	void setPlayers(vector<Player*> playerList);
//	void setDeck();
	
//	Deck* getDeck();
//	Hand getHand();
	Player* getPlayerByIndex(int index);
	
	void exchange(Player* p);
};

#endif