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
	cout << "\nAction taken!\n";
}

void MainLoop::singleTurn(Player *p) {
	showBoard();
	int cardChoice;
	cout << p->getName() <<"... Enter the card selection # that you would like to choose: ";
	cin >> cardChoice;
	Card* theCard = deck->getHand()->getCardByIndex(cardChoice);
	cout << *theCard << endl;
	p->exchange(deck, theCard);
	
	takeAction(theCard);
	
	cout << "\n\n**************************\nHere are all your cards: \n";
	for (Card* c : p->getPlayerCards()) {
		cout << *c;
	}
	cout << "\n**************************\n...Turn Over...\n\n";
}

void MainLoop::playGame() {
	cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n*~*~Welcome to Eight-Minute Empire: Legends!~*~*\n";
	while (turnsRemaining > 0) {
		Player* thePlayer = players.at(turnsRemaining%numPlayers);
		singleTurn(thePlayer);
		turnsRemaining--;
	}
	
	cout << "\nCard limit reached! Time to tally the score...\n";
	
}

