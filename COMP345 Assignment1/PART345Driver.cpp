#include <iostream>
#include "mainLoop.h"
#include "gameStart.h"
#include "GameStartUp.h"
using namespace std;

int main() {
	//PART 1
	//	Manually select map
	//	Map* map = GameStart::selectMap();
	Map* map = GameStart::selectMap("./maps/BirdsL.map");
	
	//	//manually enter players
	//	vector<Player*> players= GameStart::setPlayers();
	vector<Player*> pl;
	pl.push_back(new Player("anna"));
	pl.push_back(new Player("paul"));
	pl = GameStart::setPlayers(pl);
	
	//PART 2
	GameStartUp::setPlayerPieces(pl, map);
	Deck* deck = GameStart::setDeck();
	GameStartUp::setPlayerPieces(pl, map);
	GameStartUp::shuffleDeck(deck);
	GameStartUp::setCardCost(deck);
	//	GameStartUp::placeInitialPieces(players, map);
	int index[10] = {13,9,4,8,8,7,3,15,14,11};
	GameStartUp::placeInitialPieces(pl, map, index);
	pl.erase(pl.begin()+2);
//
	MainLoop ml = MainLoop(pl, deck, map);
	
	ml.playGame();
}