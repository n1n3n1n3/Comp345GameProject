#include <iostream>
#include "mainLoop.h"
#include "gameStart.h"
using namespace std;

int main() {
	//*******************************
	//COPY FROM GAMESTART FOR TESTING
	//*******************************
	GameStart gs = GameStart();
	gs.selectMap();
	//manually set players
	//	gs.setPlayers();
	//set players with a list cus we debugging
	vector<Player*> pl;
	pl.push_back(new Player("anna"));
	pl.push_back(new Player("paul"));
	gs.setPlayers(pl);
	gs.setDeck();
	
	
	Map* m = gs.getMap();
	Deck* d = gs.getDeck();
	
	Bid::makeBids();
	Bid::compareBids();
	//*******************************
	//COPY FROM GAMESTART FOR TESTING
	//*******************************
	
	MainLoop ml = MainLoop(pl, d, m);
	
	ml.showBoard();
	cout << ml;
	
	
}