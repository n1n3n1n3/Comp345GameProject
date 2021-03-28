
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
	static string path;
	//list of map files
	static vector<string> mapFiles;
	//Output
	static MapLoader *mapLoader;
	static Map *map;
	
	static vector<Player*> players;
	static int nbPlayers;
	
	static Deck *deck;
	
	friend std::ostream& operator<<(std::ostream&, const GameStart&);
	
public:
	
	//Constructor that sets starting coins, copy, assignment
	GameStart();
//	~GameStart();
	
	
	//functions
	static void loadMapFilePaths();
	static Map* selectMap();
	static Map* selectMap(string path);
	static vector<Player*> setPlayers();
	static vector<Player*> setPlayers(vector<Player*> playerList);
	static Deck* setDeck();
	
	static Deck* getDeck();
	static Hand* getHand();
	static Map* getMap();
	static vector<Player*> getPlayers();
	static int getNbPlayers();
};

#endif