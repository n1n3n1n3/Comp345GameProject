#include <iostream>
#include "gameStart.h"
#include "GameStartUp.h"
#include "Bid.h"

using namespace std;
int main(int argc, char *argv[]) {
	//	Map* map = GameStart::selectMap();
	Map* map = GameStart::selectMap("./maps/BirdsL.map");
		
	//	//manually enter players
	//	vector<Player*> players= GameStart::setPlayers();
	
	vector<Player*> players;
	players.push_back(new Player("anna"));
	players.push_back(new Player("paul"));
	//part two is already done in gameStart
	players = GameStart::setPlayers(players);
	cout << players.at(2)->getName() << endl;
	
	
//	Deck* deck = GameStart::setDeck();
	//part one
//	GameStartUp::shuffleDeck(deck);
//	GameStartUp::setCardCost(deck);
	
	
	GameStartUp::placeInitialPieces(players, map);
//	GameStartUp::makeBids();
}