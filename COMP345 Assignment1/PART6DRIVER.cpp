#include <iostream>
#include <algorithm>
#include <random> 
#include "mainLoop.h"
#include "gameStart.h"
using namespace std;

int main() {
	//*******************************
	//COPY FROM GAMESTART FOR TESTING
	//*******************************
	Map* map = GameStart::selectMap("./maps/BirdsL.map");
	
	//	//manually enter players
	//	vector<Player*> players= GameStart::setPlayers();
	
	vector<Player*> pl;
	pl.push_back(new Player("anna"));
	pl.push_back(new Player("paul"));
	GameStart::setPlayers(pl);
	map->loadPlayers(pl);
	
	Deck* deck = GameStart::setDeck();
	//*******************************
	//COPY FROM GAMESTART FOR TESTING
	//*******************************
	map->setStartingRegion(map->getRegionById(5));
	map->getStartingRegion()->setArmies(pl.at(0), 4);
	map->getStartingRegion()->setArmies(pl.at(1), 4);
	
	
		
		for (int i = 0; i < 13; i++) {
			pl.at(0)->exchange(deck, deck->getHand()->getCardByIndex(0));
			pl.at(1)->exchange(deck, deck->getHand()->getCardByIndex(0));
		}
		
		for (int i = 0; i < 29; i++) {
			srand(i);
			int select = rand() % 20 + 1;
			int armz = rand() % 3;
			cout << "\nSelect: " << select << "\nArmz: " << armz;
			map->getRegionById(select)->addArmies(pl.at(i%2), armz);
		}
		
		
	
	
	
	
	map->printMap();
	cout << "\n\n**************************\nHere are all Anna's cards: \n";
	for (Card* c : pl.at(0)->getPlayerCards()) {
		cout << *c;
	}
	cout << "\n\n**************************\nHere are all Paul's cards: \n";
	for (Card* c : pl.at(1)->getPlayerCards()) {
		cout << *c;
	}
	
	
	
	
	MainLoop ml = MainLoop(pl, deck, map);
	Player* theWinner = ml.determineWinner();
	cout << "\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n*~*~*!Congratulations to " << theWinner->getName() << " for their victory!*~*~*\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
	
	cout << "\n\n...............\n.......Goodbye for now.......\n...............";

}