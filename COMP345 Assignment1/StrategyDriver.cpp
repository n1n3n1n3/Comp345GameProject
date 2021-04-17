#include <iostream>
#include <random>
#include "PlayerStrategies.h"
#include "mainLoop.h"
#include "GameStartUp.h"

using namespace std;
int main() {
	
	//	Map* map = GameStart::selectMap();
	Map* map = GameStart::selectMap("./maps/BirdsL.map");
	
	//	//manually enter players
	//	vector<Player*> players= GameStart::setPlayers();
	
	vector<Player*> players;
	players.push_back(new Player("KIPPER"));
	players.push_back(new Player("FERRIS"));

	players = GameStart::setPlayers(players);
	
	
	GameStartUp::setPlayerPieces(players, map);
	
	Deck* deck = GameStart::setDeck();
	//part one
	GameStartUp::shuffleDeck(deck);
	GameStartUp::setCardCost(deck);
	
	
	//	GameStartUp::placeInitialPieces(players, map);
	
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1, 20);
	
	int index[10];
	for (int i = 0; i < 10; i++) {
		index[i] = distr(gen);
		cout << index[i] << endl;
	}

	GameStartUp::placeInitialPieces(players, map, index);
	players.erase(players.begin()+2);
	Player* startingPlayer = GameStartUp::makeBids(players);
	
	
	if (players.front() != startingPlayer) {
		int pos;
		for (int i = 0; i < players.size(); i++) {
			if (players.at(i) == startingPlayer)
				pos = i;
		}
		Player* temp = players.at(0);
		players.at(0) = startingPlayer;
		players.at(pos) = temp;
		
	}
	
	MainLoop game = MainLoop(players, deck, map);
	
	game.playGame();

	//	map->printMap();

}




	
	
	

	