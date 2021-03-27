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
	GameStart::setPlayers(players);
	cout << players.at(0)->getArmy() << endl;
	cout << players.at(1)->getArmy() << endl;
	
	
//	Deck* deck = GameStart::setDeck();
//	deck->shuffle();
	//	deck->getHand()->printCardNames();
	//	players.at(0)->exchange(deck, deck->getHand()->getCards().at(5));
	//	deck->getHand()->printCardNames();
	
//	Bid::makeBids();
////	Bid::compareBids();
//	
//	cout << players.at(1)->getCoins() << endl;
}