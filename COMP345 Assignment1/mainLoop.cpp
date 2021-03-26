#include <iostream>
#include <string>
#include "mainLoop.h"
using namespace std;

int MainLoop::numPlayers = 0;
int MainLoop::turnsRemaining = 0;

MainLoop::MainLoop(vector<Player*> players, Deck* deck, Map* map) {
	this->players = players;
	this->deck = deck;
	this->map = map;
	this->numPlayers = players.size();
	if (numPlayers == 2)
		this->turnsRemaining = 26;
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

void MainLoop::takeAction(Card *c) {
	
}

void MainLoop::singleTurn(Player *p) {
	showBoard();
	int cardChoice;
	cout << p->getName() <<"... Enter the card selection # that you would like to choose: ";
	cin >> cardChoice;
	Card* theCard = deck->getCardDeck().at(cardChoice);
	p->exchange(deck, theCard);
	
	takeAction(theCard);
	
}