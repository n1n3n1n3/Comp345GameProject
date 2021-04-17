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
	cout << "\n***************************************\n"; 
	map->printMap();
	cout << *deck;
	
}

//Determine the action from a card and have the player execute the action
void MainLoop::takeAction(Player* p, Card *c) {
	
	bool andAction = false;
	bool orAction = false;
	int bonus = 0;
	int num = 0;
	int len = 0;
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;
	string split = "";
	string ret = "";
	int looper = 1;
	int tempAction = c->getAction();
	if (tempAction < 0) {
		orAction = true;
		tempAction*=-1;
	}
	
	for (int i = tempAction; i > 0; i = i/10) {
		len++;
	}
	
	if (len == 4) {
		if (!orAction) {
			andAction = true;
			looper = 2;
		}
		
		first = tempAction/1000;
		second = (tempAction/100)%10;
		third = (tempAction/10)%10;
		fourth = tempAction%10;
	}
	else if (len == 2) {
		first = tempAction/10;
		second = tempAction%10;
	}
	else {
		first = tempAction;
	}
	
	for (int i = 0; i < looper; i++) {

		if (orAction) {
			int choice = 0;
			cout << *c << endl;
			cout << "\n***************************************\nWhich action would you like to take? (0 or 1, anything else for skip.) ->";
			cin >> choice;
		
			if (choice == 1) {
				first = third;
				second = fourth;
			}
		}
		else {
			
		}
		
		if (i == 1) {
			int choice = 0;
			cout << *c <<endl;
			cout << "\n***************************************\nWould you like to take the second action? (0 for No, 1 for Yes) ->";
			cin >> choice;
			if (choice == 1) {
				first = third;
				second = fourth;
			}
			else
				break;
		}
		map->printMap();
		switch (first) {
			case 1:
				bonus = p->checkPlacementBonus();
				num = second + bonus;
				cout << "\n***************************************\nPlacing " << second << " armies with a bonus of " << bonus << " for a total of " << num;
				
				p->PlaceNewArmies(num, map);
				break;
			case 2:
				bonus = p->checkMovementBonus();
				num = second + bonus;
				cout << "\n***************************************\nMoving " << second << " armies with a bonus of " << bonus << " for a total of " << num << ".\nMoving over water costs " << p->checkFlying() << " per Army.";
				
				p->MoveArmies(num, map);
				break;
			case 3:
				cout << "\n***************************************\nDestroying an army...";
				
				p->DestroyArmy(map);
				break;
			case 4:
				cout << "\n***************************************\nBuilding a city...";
				
				p->BuildCity(map);
				break;
			default:
				ret+= "\n***************************************\nInvalid...";
		}
	}
	
}

//A single turn
void MainLoop::singleTurn(Player *p) {
	
	//Display the Map & Hand
	showBoard();
	//Show the player all their cards, end turn
	cout << "\n\n**************************\nHere are all your cards: \n";
	for (Card* c : p->getPlayerCards()) {
		cout << *c;
	}
	
	int St;
	cout << "\n\n" << p->getName() << ". Your current Strategy is " << p->getStrat() << ".\nEnter 0 to change the strategy, anything else to skip->";
	cin >> St;
	
	if (St == 0) {
		while (true) {
			int s;
			cout << "\nEnter 0 for Human, 1 for AgroCPU, 2 for ChillCPU ->";
			cin >> s;
			if ((s < 0)||(s > 2))
				cout << "\nInvalid...." << endl;
			else {
				p->setStrat(s);
				break;
			}
		}
	}
	
	
	
	//Player chooses the card they want from the hand
	Card* theCard = p->selectCard(this->map, this->deck);
	
	//check Immune card
	if (theCard->getGood() == 9)
		map->setImmunePlayer(p);
	
	//Player takes the action of the Card
	takeAction(p, theCard);
	
		cout << "\n***************************************\n...Turn Over...\n***************************************\n\n";
}

void MainLoop::playGame() {
	
	//Welcome message
	cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n*~*~Welcome to Eight-Minute Empire: Legends!~*~*\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
	
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
	Player* theWinner = determineWinner();
	cout << "\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n*~*~*!Congratulations to " << theWinner->getName() << " for their victory!*~*~*\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
	
	cout << "\n\n...............\n.......Goodbye for now.......\n...............";
}

Player* MainLoop::determineWinner() {
	Player* winner = players.at(0);
	int winningScore = players.at(0)->computeScore(this->map);
	
	for (int i = 1; i < numPlayers; i++) {
		int compareScore = players.at(i)->computeScore(this->map);
		if (compareScore > winningScore) {
			winningScore = compareScore;
			winner = players.at(i);
		}
		else if (compareScore == winningScore) {
			if (winner->getCoins() < players.at(i)->getCoins()) {
				winner = players.at(i);
				cout << "\nTIE! But " << winner->getName() << " has more coins, so they are the winner!\n";
			}
			else if (winner->getCoins() > players.at(i)->getCoins()) {
				cout << "\nTIE! But " << winner->getName() << " has more coins, so they are the winner!\n";
			}
			else if (winner->getOwned() < players.at(i)->getOwned()) {
				winner = players.at(i);
				cout << "\nTIE! Even with coins! But " << winner->getName() << " has more regions, so they are the winner!\n";
			}
			else
				cout << "\nTIE! Even with coins! But " << winner->getName() << " has more regions, so they are the winner!\n";
		}
	}
	
	return winner;
}


