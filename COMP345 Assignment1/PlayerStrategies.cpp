#include <iostream>
#pragma once
#include <string>
#include "PlayerStrategies.h"

using namespace std;

//HUMAN PLAYER - SAME AS BEFORE COPIED INTO HUMAN STRATEGY CLASS

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

void humanPlayer::PlaceNewArmies(Player* p, int a, Map* m) {
	while (a > 0) {
		bool valid = false;
		while (!valid) {
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID that you would like to place on ->";
			cin >> choice;
			Region* r = m->getRegionById(choice);
			if (p->checkPlacementValidity(m, r)) {
				valid = true;
				bool val = false;
				while (!val) {
					int arms = 0;
					cout << "\n***************************************\nEnter # of armies to place (max " << a << ") ->";
					cin >> arms;
					if (arms > a)
						cout << "\n***************************************\nInvalid, try again...\n";
					else {
						val = true;
						r->addArmies(p, arms);
						a -= arms;
					}
				}
			}
			else 
				cout << "\n***************************************\nInvalid Region, must be the Starting Region or a region where you own a city...\n";
		}
	}
	cout << "\n***************************************\nDone placing Armies!";
}
void humanPlayer::MoveArmies(Player* p, int a, Map* m) {
	while (a > 0) {
		bool valid = false;
		Region* starting;
		Region* moving;
		cout << "\n***************************************\nYou have " << a << " movement points...\n";
		while (!valid) {
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID that you would like to move armies from (0 to skip) ->";
			cin >> choice;
			if (choice == 0) {
				return;
			}
			starting = m->getRegionById(choice);
			vector<pair<Player*, int>> players = starting->getPlayerArmies();
			for (int i = 0; i < players.size(); i++){
				if (players.at(i).first == p) {
					if (players.at(i).second > 0) {
						valid = true;
					}
					else {
						cout << "\n***************************************\nInvalid Region, no armies to move...\n";
					}
				}
			}
		}
		
		valid = false;
		while (!valid) {
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID that you would like to move to (consult the borders displayed above) ->";
			cin >> choice;
			moving = m->getRegionById(choice);
			if (m->areAdjacent(starting, moving)) {
				int moves = a;
				if ((m->getRegionContinent(starting)) != (m->getRegionContinent(moving))) {
					if (a < p->checkFlying()) {
						cout << "\n***************************************\nRegions are adjacent, but you need at least " << p->checkFlying() << " movements to move over water...\n";
					}
					//MOVE OVER WATER
					else {
						a -= p->MoveOverWater(moves, starting, moving);
						valid = true;
					}
				}
				//MOVE OVER LAND
				else {
					a -= p->MoveOverLand(moves, starting, moving);
					valid = true;
				}
			}
			else 
				cout << "\n***************************************\nInvalid Region, must be adjacent to " << starting->getName() << "...\n";
		}
		
	}

}
void humanPlayer::BuildCity(Player* p, Map* m) {
	bool valid = false;
	while (!valid) {
		int choice = 0;
		cout << "\n***************************************\nEnter the Region ID that you would like to build a city on ->";
		cin >> choice;
		Region* r = m->getRegionById(choice);
		if (r->addCity(p))
			valid = true;
	}

}
void humanPlayer::DestroyArmy(Player* p, Map* m) {
	bool valid = false;
	Region* r;
	vector<pair<Player*, int>> players;
	while (true) {
		while (!valid) {
			bool hasOp = false;
			bool hasSelf = false;
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID where you would like to destroy an opponent's army (or 0 to skip) ->";
			cin >> choice;
			if (choice == 0)
				return;
			r = m->getRegionById(choice);
			players = r->getPlayerArmies();
			for (int i = 0; i < players.size(); i++) {
				if (players.at(i).first != p) {
					if (players.at(i).second > 0) {
						hasOp = true;
					}
				}
				else if (players.at(i).first == p) {
					if (players.at(i).second > 0)
						hasSelf = true;
				}
			}
			if ((hasOp)&&(hasSelf))
				valid = true;
			else 
				cout << "\n***************************************\nThis Region either has no opponent armies on it or you don't have an army on it...\n";
		}
		valid = false;
		
		while (!valid) {
			int choice = 0;
			cout << *r << "\n***************************************\nEnter the # of the Player whose army you want to destroy (top = 1, 0 to go back) ->";
			cin >> choice;
			if (choice == 0)
				break;
			choice -= 1;
			
			if ((choice < 0)||(choice >= players.size()))
				cout << "\n***************************************\nInvalid...\n";
			else if (players.at(choice).first == p)
				cout << "\n***************************************\nYou can't destroy yourself, silly!!\n";
			else if (players.at(choice).first == m->getImmunePlayer())
				cout << "\n***************************************\n" << players.at(choice).first->getName() << " has immunity! You can't destroy their armies...";
			else {
				cout << "\n***************************************\nDestroying one army of " << players.at(choice).first->getName() << " from Region " << r->getName() << ".\n";
				r->removeArmies(players.at(choice).first, 1);
				return;
			}
		}
		
	}
	
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

int agroPlayer::getPriority(Player* p, Card *c, Map* m) {
	string a = c->getActionString();
	if (((a.find("Destroy")) != string::npos)&&(m->canDestroy(p)))
		return (0 + c->getCost());
	else if (a.find("Build") != string::npos)
		return (0 + c->getCost());
	else
		return (2 + c->getCost());
	
}

Card* agroPlayer::chooseCard(Player *p, Map* m, Deck *d) {
	
	Hand* h = d->getHand();
	Card* theCard = h->getCardByIndex(0);
	int priority = this->getPriority(p, h->getCardByIndex(0), m);
	int handSize = d->getHand()->getSize();

	for (int i = 1; i < handSize; i++) {
		
		if (this->getPriority(p, h->getCardByIndex(i), m) >= priority) {
			if ((h->getCardByIndex(i)->getCost()) <= p->getCoins()) {
				
				priority = this->getPriority(p, h->getCardByIndex(i), m);
				theCard = h->getCardByIndex(i);
				
			}
		}
	}
			
	return theCard;

}

int agroPlayer::safelyOwned(Player *p, Region *r) {
	int owner = 0;
	int challenger = 0;
	if (r->getOwner() != p->getName())
		return 0;
	else {
		for (pair<Player*, int> o : r->getPlayerArmies()) {
			if (o.first == p)
				owner = o.second;
			else if (o.second > challenger)
				challenger = o.second;
		}
		return (owner - challenger)-1;
	}
}


Region* agroPlayer::findTarget(Player* p, Map *m) {
	Region* target = NULL;
	int biggestThreat = 0;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			if (p->getName() != r->getOwner()) {
				int temp = 0;
				for (pair<Player*, int> o : r->getPlayerArmies()) {
					if (o.first != p)
						temp += o.second;
				}
				if (temp > biggestThreat) {
					biggestThreat = temp;
					target = r;
				}
			}
			else if (target == NULL)
				target = r;
		}
	}
	return target;
}

vector<Region*> agroPlayer::findPath(Player* p, Map* m, Region* r) {
	vector<Region*> visited;
	for (Continent* c : m->getContinents()) {
		for (Region* q : c->getRegions()) {
			if ((m->areAdjacent(q, r))&&(safelyOwned(p, q) > 0))
				return {q, r};
			else if (m->areAdjacent(q, r))
				visited.push_back(q);
		}
	}
	
	
	while (true) {
	for (Region* q : visited) {
		for (Continent* c : m->getContinents()) {
			for (Region* s : c->getRegions()) {
				if (find(visited.begin(), visited.end(), s) == visited.end()) {
					if ((m->areAdjacent(q, s))&&(safelyOwned(p, q) > 0)) 
						return {s, q};
					else if (m->areAdjacent(s, q))
						visited.push_back(s);
					}
				}	
			}
		}
		if (visited.size() >= m->getNbRegions())
			return {NULL, NULL};
	}
}


///////TAKING ACTIONS///////

void agroPlayer::PlaceNewArmies(Player* p, int a, Map* m) {
	Region* target = NULL;
	int biggestThreat = 0;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			if ((p->getName() != r->getOwner())&&((r->checkCity(p))||r->checkStartingRegion(m))) {
				int temp = 0;
				for (pair<Player*, int> o : r->getPlayerArmies()) {
					if (o.first != p)
						temp += o.second;
				}
				if (temp > biggestThreat) {
					biggestThreat = temp;
					target = r;
				}
			}
		}
	}
	if (target != NULL) {
		cout << "Adding " << a << " armies to " << target->getName() << endl; 
		target->addArmies(p, a);
	}
	else {
		for (Continent* c : m->getContinents()) {
			for (Region* r : c->getRegions()) {
				if ((r->checkCity(p))||(r->checkStartingRegion(m))) {
					int temp = 0;
					for (pair<Player*, int> o : r->getPlayerArmies()) {
						if (o.first != p)
							temp += o.second;
					}
					if (temp > biggestThreat) {
						biggestThreat = temp;
						target = r;
					}
				}
				
			}
		}
		target->addArmies(p, a);
	}

	
	
}


void agroPlayer::MoveArmies(Player* p, int a, Map* m) {
	vector<Region*> start_and_move;
	Region* target = findTarget(p, m);
	int toMove = 0;
	while (a > 0) {
		start_and_move = findPath(p, m, target);
		Region* start = start_and_move.at(0);
		Region* move = start_and_move.at(1);
		if (start == NULL)
			cout << "\nPlayer does not have any armies available to move.\n" << endl;
		else {
			toMove = safelyOwned(p, start);
			if (m->borderIsWater(start, move))
				toMove = toMove/p->checkFlying();
			
			if (toMove > a) 
				toMove = a;
				
			start->removeArmies(p, toMove);
			move->addArmies(p, toMove);
			cout << "\nMoving " << toMove << " armies from " << start->getName() << " to " << move->getName() << "...\n" << endl;
			
			a-=toMove;
			
		}
		
	}
	
}

void agroPlayer::BuildCity(Player* p, Map* m) {
	Region* toBuild = NULL;
	int most = 0;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			int temp = 0;
			for (pair<Player*, int> o : r->getPlayerArmies()) {
				if (o.first != p)
					temp += o.second;
			}
			if ((temp > most)&&!(r->checkCity(p))) {
				most = temp;
				toBuild = r;
			}
				
		}
	}
	if (toBuild == NULL) {
		for (Continent* c : m->getContinents()) {
			for (Region* r : c->getRegions()) {
				if (!r->checkCity(p)) {
					r->addCity(p);
					return;
				}
			}
		}
	}
	else 
		toBuild->addCity(p);
	
}

void agroPlayer::DestroyArmy(Player* p, Map* m) {
	Region* toAttack = NULL;
	Player* target;
	int least = 100;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			if (r->canDestroy(p)) {
				if (toAttack == NULL) {
					toAttack = r;
					for (pair<Player*, int> o : r->getPlayerArmies()) {
						if ((o.first != p)&&(o.second > 0)&&(o.second < least))
							target = o.first;
					}
				}
				else {
					for (pair<Player*, int> o : r->getPlayerArmies()) {
						if ((o.first != p)&&(o.second > 0)&&(o.second < least)) {
							target = o.first;
							toAttack = r;
						}
					}
				}
			}
		}
	}
	
	toAttack->removeArmies(target, 1);
	
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
	
	
	