#include <iostream>
#include "gameStart.h"


using namespace std;
int main(int argc, char *argv[]) {
	
	Map* map = GameStart::selectMap();
//	vector<Player*> players= GameStart::setPlayers();
//	gs.setPlayers();
//	gs.setDeck();
	vector<Player*> pl;
	pl.push_back(new Player("anna"));
	pl.push_back(new Player("paul"));
	GameStart::setPlayers(pl);
	
	
	Deck* deck = GameStart::setDeck();

//	gs.exchange(pl.at(0));
}