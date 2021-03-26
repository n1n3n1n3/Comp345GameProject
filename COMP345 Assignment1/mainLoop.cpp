#include <iostream>
#include <string>
#include "mainLoop.h"
using namespace std;

MainLoop::MainLoop(vector<Player*> players, Deck* deck, Map* map) {
	this->players = players;
	this->deck = deck;
	this->map = map;
	numPlayers = players.size();
	if (numPlayers == 2)
		turnsRemaining = 26;
	else {
		cout << "\n*Error*, must be two players.";
		exit(0);
	}
}


std::ostream& operator<<(std::ostream& strm, const MainLoop& m) {
	Player* turn = m.whoseTurn();
	return strm << "It is " << turn->getName() << "'s turn. " << m.turnsRemaining << " turns remaining in the game.";
}


Player* MainLoop::whoseTurn() const{
	//int turn = turnsRemaining%(this->players.size());
	return this->players.at(turnsRemaining%(this->players.size()));
}


void MainLoop::showBoard() {
	cout << "**************************\n"; 
	//map->printMap();
	cout << *deck;
	
	
}