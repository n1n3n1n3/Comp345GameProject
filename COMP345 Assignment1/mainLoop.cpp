#include <iostream>
#include <string>
#include "mainLoop.h"
using namespace std;

int MainLoop::numPlayers = 0;
int MainLoop::turnsRemaining = 0;

//Constructor that currently can only handle a 2 player game
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


//Displays whose turn is it and how many game turns remain
std::ostream& operator<<(std::ostream& strm, const MainLoop& m) {
	Player* turn = m.whoseTurn();
	return strm << "It is " << turn->getName() << "'s turn. " << m.turnsRemaining << " turns remaining in the game.";
}


//Check whose turn it is
Player* MainLoop::whoseTurn() const{
	//int turn = turnsRemaining%(this->players.size());
	return this->players.at(turnsRemaining%numPlayers);
}


//Display Map&Hand
void MainLoop::showBoard() {
	cout << "**************************\n"; 
	//map->printMap();
	cout << *deck;
	
}

//Determine the action from a card and have the player execute the action
void MainLoop::takeAction(Player* p, Card *c) {
	cout << "\nAction taken!\n";
}

//A single turn
void MainLoop::singleTurn(Player *p) {
	
	//Display the Map & Hand
	showBoard();
	
	//Player chooses the card they want from the hand
	int cardChoice;
	cout << p->getName() <<"... Enter the card selection # that you would like to choose: ";
	cin >> cardChoice;
	
	//Find and display the card;
	Card* theCard = deck->getHand()->getCardByIndex(cardChoice);
	cout << *theCard << endl;
	
	//Player takes the card from the hand, hand is updated
	p->exchange(deck, theCard);
	
	//Player takes the action of the Card
	takeAction(p, theCard);
	
	//Show the player all their cards, end turn
	cout << "\n\n**************************\nHere are all your cards: \n";
	for (Card* c : p->getPlayerCards()) {
		cout << *c;
	}
	cout << "\n**************************\n...Turn Over...\n\n";
}

void MainLoop::playGame() {
	
	//Welcome message
	cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n*~*~Welcome to Eight-Minute Empire: Legends!~*~*\n";
	
	//Fixed # of turns per game to manage the mainloop
	while (turnsRemaining > 0) {
		
		//determine whose turn
		Player* thePlayer = whoseTurn();
		
		//Run turn for the player
		singleTurn(thePlayer);
		
		//Decrement turns
		turnsRemaining--;
	}
	
	cout << "\nCard limit reached! Time to tally the score...\n";
	
}

