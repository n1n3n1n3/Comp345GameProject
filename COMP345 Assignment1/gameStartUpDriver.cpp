#include <iostream>
#include "gameStart.h"
#include "GameStartUp.h"


using namespace std;
int main(int argc, char *argv[]) {
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
}