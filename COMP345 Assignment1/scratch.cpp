#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "PlayerStrategies.h"
#include "mainLoop.h"
#include "GameStartUp.h"

using namespace std;
int main(int argc, char *argv[]) {
	
	
	Map* map = GameStart::selectMap("./maps/BirdsL.map");
	
	vector<Player*> players;
	players.push_back(new Player("MAËLLE"));
	players.push_back(new Player("SIMON"));
	//part two is already done in gameStart
	players = GameStart::setPlayers(players);
	
	
	GameStartUp::setPlayerPieces(players, map);
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1, 20);
	
	int index[10];
	for (int i = 0; i < 10; i++) {
		index[i] = distr(gen);
		cout << index[i] << endl;
	}
	
	
	GameStartUp::placeInitialPieces(players, map, index);
	map->printMap();
	players.at(0)->setStrat(1);
	players.at(0)->MoveArmies(2, map);
	
	
}