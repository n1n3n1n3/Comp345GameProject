#include <iostream>
#include "gameStart.h"


using namespace std;
int main(int argc, char *argv[]) {
//	cout << "hello world" << endl;
	GameStart gs = GameStart();
	//	gs.selectMap();
	//	gs.setPlayers();
	
	vector<Player*> pl;
	pl.push_back(new Player("anna"));
	pl.push_back(new Player("paul"));
	gs.setPlayers(pl);
	gs.setDeck();
	gs.exchange(pl.at(0));
}