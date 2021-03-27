#include <iostream>
#include "gameStart.h"


using namespace std;
int main(int argc, char *argv[]) {
	
//	Map* map = GameStart::selectMap();
	Map* map = GameStart::selectMap("./maps/BirdsPyramid.map");
	
	
//	//manually enter players
//	vector<Player*> players= GameStart::setPlayers();

	vector<Player*> players;
	players.push_back(new Player("anna"));
	players.push_back(new Player("paul"));
	GameStart::setPlayers(players);
	
	
	Deck* deck = GameStart::setDeck();
	
	map->determineStartingRegion();
//	
//	Region* r1 =map->getRegionById(16);
//	
//	cout << map->connectedToOtherContinent(r1) << endl;
	
//	cout << *map->getRegionById(18) << endl;
//	deck->getHand()->printCardNames();
//	players.at(0)->exchange(deck, deck->getHand()->getCards().at(5));
//	deck->getHand()->printCardNames();
}