#include <iostream>

#include "Player.h"
#include "Cards.h"
#include <string>
#include "PlayerStrategies.h"

using namespace std;

Card* humanPlayer::chooseCard(Player *p, Map* m, Deck *d) {
	Card* theCard;
	bool valid = false;
	while (!valid) {
		int cardChoice;
		cout << p->getName() <<"\n***************************************\n... Enter the card selection # that you would like to choose: ";
		cin >> cardChoice;
		
		if ((cardChoice >= d->getHand()->getSize())||(cardChoice < 0)) {
			cout << "\n***************************************\nInvalid input...\n";
		}
		else {	
			//Find and display the card;
			theCard = d->getHand()->getCardByIndex(cardChoice);
			cout << *theCard << endl;
			
			//Player takes the card from the hand, hand is updated
			if (p->exchange(d, theCard))
				valid = true;
		}
	}

	return theCard;
	
}

//PRIORITY SYSTEM//
/*
Priority = Action priority + Card cost

Lowest Priority value is chosen by player. 

Agro Priority values:
Destroy Army & Build City - 0.
Move & Place Armies - 2.

Chill Priority values:
Move & Place Armies - 0.
Destroy Army & Build City - 2.

Agro takes expensive ties, Chill takes cheap ties.


*/

int agroPlayer::getPriority(Card *c) {
	string a = c->getActionString();
	if (((a.find("Destroy")) != string::npos)||((a.find("Build")) != string::npos))
		return (0 + c->getCost());
	else
		return (2 + c->getCost());
	
}

Card* agroPlayer::chooseCard(Player *p, Map* m, Deck *d) {
	
	Hand* h = d->getHand();
	Card* theCard = h->getCardByIndex(0);
	int priority = this->getPriority(h->getCardByIndex(0));
	int handSize = d->getHand()->getSize();

	for (int i = 1; i < handSize; i++) {
		
		if ((this->getPriority(h->getCardByIndex(i))) >= priority) {
			if ((h->getCardByIndex(i)->getCost()) <= p->getCoins()) {
				priority = this->getPriority(h->getCardByIndex(i));
				theCard = h->getCardByIndex(i);
			}
		}
	}
			
	return theCard;

}

int chillPlayer::getPriority(Card *c) {
	string a = c->getActionString();
	if (((a.find("Place")) != string::npos)||((a.find("Move")) != string::npos))
		return (0 + c->getCost());
	else
		return (2 + c->getCost());
	
}

Card* chillPlayer::chooseCard(Player *p, Map* m, Deck *d) {
	
	Hand* h = d->getHand();
	Card* theCard = h->getCardByIndex(0);
	int priority = this->getPriority(h->getCardByIndex(0));
	int handSize = d->getHand()->getSize();
	
	for (int i = 1; i < handSize; i++) {
		
		if ((this->getPriority(h->getCardByIndex(i))) > priority) {
			if ((h->getCardByIndex(i)->getCost()) <= p->getCoins()) {
				priority = this->getPriority(h->getCardByIndex(i));
				theCard = h->getCardByIndex(i);
			}
		}
	}
	
	return theCard;
	
}



