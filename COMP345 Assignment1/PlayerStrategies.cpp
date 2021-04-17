#include <iostream>
#include <algorithm>
#include <list>
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

//HUMAN GARBAGE
int humanPlayer::getPriority(Card* c) {return 0;}
int humanPlayer::safelyOwned(Player* p, Region* r) {return 0;}
Region* humanPlayer::findTarget(Player* p, Map* m) {return new Region();}
vector<Region*> humanPlayer::findPath(Player*, Map* m, Region* r) {return {};}

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
Strategy::Strategy() {
	name = "NONE";
}

humanPlayer::humanPlayer() {
	name = "HUMAN";
}

agroPlayer::agroPlayer() {
	name = "AGRO";
}

chillPlayer::chillPlayer() {
	name = "CHILL";
}

int agroPlayer::getPriority(Card *c) {
	string a = c->getActionString();
	if (((a.find("Place")) != string::npos)||((a.find("Move")) != string::npos))
		return (2 + c->getCost());
	else
		return (0 + c->getCost());
	
}

int agroPlayer::getPriority(Player* p, Card *c, Map* m) {
	string a = c->getActionString();
	if (((a.find("Destroy")) != string::npos)&&(m->canDestroy(p)))
		return (0 + c->getCost());
	else if (a.find("Build") != string::npos)
		return (0 + c->getCost());
	else
		return (1 + c->getCost());
	
}

Card* agroPlayer::chooseCard(Player *p, Map* m, Deck *d) {
	
	Hand* h = d->getHand();
	Card* theCard = h->getCardByIndex(0);
	int priority = this->getPriority(p, h->getCardByIndex(0), m);
	int handSize = d->getHand()->getSize();

	for (int i = 1; i < handSize; i++) {
		
		if (this->getPriority(p, h->getCardByIndex(i), m) <= priority) {
			if ((h->getCardByIndex(i)->getCost()) <= p->getCoins()) {
				
				priority = this->getPriority(p, h->getCardByIndex(i), m);
				theCard = h->getCardByIndex(i);
				
			}
		}
	}
	cout << "\n***************************************\nSELECTING THE FOLLOWING CARD: \n" << *theCard;
	p->exchange(d, theCard);
	return theCard;

}

int agroPlayer::safelyOwned(Player *p, Region *r) {
	int mover = 0;
	int challenger = 0;
	int ret = 0;
	for (pair<Player*, int> o : r->getPlayerArmies()) {
		if (o.first == p)
			mover = o.second;
		else if (o.second > challenger)
			challenger = o.second;
		}
	/*if ((mover-challenger)>0)	
		ret = mover-challenger;
	else
		ret = 0;*/
	ret = mover;
	return ret;
}
	
	



Region* agroPlayer::findTarget(Player* p, Map *m) {
	Region* target = NULL;
	int weakestRegion = 100;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			if (p->getName() != r->getOwner()) {
				int temp = 0;
				for (pair<Player*, int> o : r->getPlayerArmies()) {
					if (o.first != p)
						temp += o.second;
					//else
						//temp -= o.second;
				}
				if (temp <= weakestRegion) {
					weakestRegion = temp;
					target = r;
				}
			}
			else if (target == NULL)
				target = r;
		}
	}
	cout << "\n**************************************\nTarget Region is #" << target->getId() << endl;
	return target;
}

vector<Region*> agroPlayer::findPath(Player* p, Map* m, Region* r) {
	vector<Region*> visited;
	list<vector<Region*>> tbv;
	visited.push_back(r);
	for (Continent* c : m->getContinents()) {
		for (Region* q : c->getRegions()) {
			if (m->areAdjacent(r, q))
				tbv.push_back({q,r});
		}
	}
	
	while (!tbv.empty()) {
		if ((safelyOwned(p, tbv.front().front())) > 0)
			return tbv.front();
		else {
			for (Continent* c : m->getContinents()) {
				for (Region* q : c->getRegions()) {
					if (find(visited.begin(), visited.end(), q) == visited.end()) {
						if (m->areAdjacent(tbv.front().front(), q))
							tbv.push_back({q,tbv.front().front()});
					}
				}
			}
			visited.push_back(tbv.front().front());
			tbv.pop_front();
		}
		
		
	}
	cout << "\nNo valid armies to move, returning NULL" << endl;
	return {NULL, NULL};
	
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
	int maxMoves = 0;
	bool tswitch = false;
	while (a > 0) {
		if (!tswitch)
			target = findTarget(p, m);
		start_and_move = findPath(p, m, target);
		Region* start = start_and_move.at(0);
		Region* move = start_and_move.at(1);
		if (start == NULL) {
			cout << "\nPlayer does not have any armies available to move.\n" << endl;
			a = 0;
		}
		else {
			toMove = safelyOwned(p, start);
			if (toMove > a) 
				toMove = a;
			
			if (m->borderIsWater(start, move)) {
				maxMoves = toMove/p->checkFlying();
				toMove = (p->checkFlying()*maxMoves);
				cout << "\nBorder between " << start->getId() << " and " << move->getId() << " is water, movement costs " << p->checkFlying() << " giving the player " << maxMoves << endl;
			}
			else 
				maxMoves = toMove;
			
			
			if (maxMoves == 0) {
				tswitch = true;
				target = m->getRegionById((target->getId()+1)%m->getNbRegions());
				cout << "New target is Region #" << target->getId() << endl;
			}
			
			else {
				
				
				start->removeArmies(p, maxMoves);
				move->addArmies(p, maxMoves);
				cout << "\nMoving " << toMove << " armies from " << start->getName() << " to " << move->getName() << "...\n" << endl;
				
				a-=toMove;
			}
			
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
			if ((temp > most)&&!(r->checkCity(p))&&!(r->checkStartingRegion(m))) {
				most = temp;
				toBuild = r;
			}
				
		}
	}
	if (toBuild == NULL) {
		for (Continent* c : m->getContinents()) {
			for (Region* r : c->getRegions()) {
				if ((!r->checkCity(p))&&!(r->checkStartingRegion(m))) {
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
		if (a.find("Place") != string::npos)
			return (0 + c->getCost());
		else if (a.find("Move") != string::npos)
			return (1 + c->getCost());
		else
			return (2 + c->getCost());
		
	}
	
	Card* chillPlayer::chooseCard(Player *p, Map* m, Deck *d) {
		
		Hand* h = d->getHand();
		Card* theCard = h->getCardByIndex(0);
		int priority = this->getPriority(h->getCardByIndex(0));
		int handSize = d->getHand()->getSize();
		
		for (int i = 1; i < handSize; i++) {
			
			if ((this->getPriority(h->getCardByIndex(i))) < priority) {
				if ((h->getCardByIndex(i)->getCost()) <= p->getCoins()) {
					priority = this->getPriority(h->getCardByIndex(i));
					theCard = h->getCardByIndex(i);
				}
			}
		}
		cout << "\n***************************************\nSELECTING THE FOLLOWING CARD: \n" << *theCard;
		p->exchange(d, theCard);
		return theCard;
		
	}

void chillPlayer::PlaceNewArmies(Player* p, int a, Map* m) {
	Region* target = NULL;
	int biggestThreat = 0;
	cout << "\nPlacing " << a << " armies..." << endl;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			if ((p->getName() != r->getOwner())&&((r->checkCity(p))||r->checkStartingRegion(m))) {
				cout << "\n" << p->getName() << " has a city on Region #" << r->getId() << endl;
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
		target->addArmies(p, a);
	}
	else {
		cout << "\nNo initial target..." << endl;
		for (Continent* c : m->getContinents()) {
			for (Region* r : c->getRegions()) {
				if ((r->checkCity(p))||(r->checkStartingRegion(m))) {
					cout << "\n" << p->getName() << " can place on Region #" << r->getId() << endl;
					int temp = 0;
					/*for (pair<Player*, int> o : r->getPlayerArmies()) {
						if (o.first != p)
							temp += o.second;
					}
					if (temp > biggestThreat) {
						biggestThreat = temp;*/
						target = r;
					//}
				}
				
			}
		}
		target->addArmies(p, a);
	}

	
}
	
	
	
void chillPlayer::MoveArmies(Player* p, int a, Map* m) {
	
	vector<Region*> start_and_move;
	Region* target = findTarget(p, m);
	int toMove = 0;
	int maxMoves = 0;
	bool tswitch = false;
	while (a > 0) {
		if (!tswitch)
			target = findTarget(p, m);
		start_and_move = findPath(p, m, target);
		Region* start = start_and_move.at(0);
		Region* move = start_and_move.at(1);
		if ((start == NULL)||(safelyOwned(p, start) == 0)) {
		//	cout << "\nPlayer does not have any armies available to move.\n" << endl;
			a = 0;
		}
		 
		else {
			toMove = safelyOwned(p, start);
			if (toMove > a) 
				toMove = a;
			
			if (m->borderIsWater(start, move)) {
				maxMoves = toMove/p->checkFlying();
				toMove = (p->checkFlying()*maxMoves);
				//cout << "\nBorder between " << start->getId() << " and " << move->getId() << " is water, movement costs " << p->checkFlying() << " giving the player " << maxMoves << endl;
			}
			else 
				maxMoves = toMove;
			
			
			if (maxMoves == 0) {
				tswitch = true;
				target = m->getRegionById((target->getId()+1)%m->getNbRegions());
			//	cout << "New target is Region #" << target->getId() << endl;
			}
			
			else {
				
				
				start->removeArmies(p, maxMoves);
				move->addArmies(p, maxMoves);
				cout << "\nMoving " << toMove << " armies from " << start->getName() << " to " << move->getName() << "...\n" << endl;
				
				a-=toMove;
			}
			
		}
		
	}

	
}

Region* chillPlayer::findTarget(Player* p, Map* m) {	
	Region* target = NULL;
	int weakestRegion = 100;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			if (p->getName() != r->getOwner()) {
				int temp = 0;
				for (pair<Player*, int> o : r->getPlayerArmies()) {
					if (o.first != p)
						temp += o.second;
					else
						temp -= o.second;
				}
				if (temp <= weakestRegion) {
					weakestRegion = temp;
					target = r;
				}
			}
			else if (target == NULL)
				target = r;
		}
	}
	cout << "\n**************************************\nTarget Region is #" << target->getId() << endl;
	return target;
}	

vector<Region*> chillPlayer::findPath(Player* p, Map* m, Region* r) {
	
	vector<Region*> visited;
	list<vector<Region*>> tbv;
	visited.push_back(r);
	for (Continent* c : m->getContinents()) {
		for (Region* q : c->getRegions()) {
			if (m->areAdjacent(r, q))
				tbv.push_back({q,r});
		}
	}
	
	while (!tbv.empty()) {
		if ((safelyOwned(p, tbv.front().front())) > 0)
			return tbv.front();
		else {
			for (Continent* c : m->getContinents()) {
				for (Region* q : c->getRegions()) {
					if (find(visited.begin(), visited.end(), q) == visited.end()) {
						if (m->areAdjacent(tbv.front().front(), q))
							tbv.push_back({q,tbv.front().front()});
					}
				}
			}
			visited.push_back(tbv.front().front());
			tbv.pop_front();
		}
		
		
	}
	cout << "\nNo valid armies to move, returning NULL" << endl;
	return {NULL, NULL};

}

int chillPlayer::safelyOwned(Player* p, Region* r) {
	int mover = 0;
	int challenger = 0;
	int ret = 0;
	for (pair<Player*, int> o : r->getPlayerArmies()) {
		if (o.first == p)
			mover = o.second;
		else if (o.second > challenger)
			challenger = o.second;
	}
	if ((mover-challenger)>0)	
		ret = mover-challenger;
	else
		ret = 0;
	return ret;
	
}

void chillPlayer::DestroyArmy(Player* p, Map* m) {
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



void chillPlayer::BuildCity(Player* p, Map* m) {
	Region* toBuild = NULL;
	int most = 0;
	for (Continent* c : m->getContinents()) {
		for (Region* r : c->getRegions()) {
			int temp = 0;
			for (pair<Player*, int> o : r->getPlayerArmies()) {
				if (o.first != p)
					temp += o.second;
			}
			if ((temp > most)&&!(r->checkCity(p))&&!(r->checkStartingRegion(m))) {
				most = temp;
				toBuild = r;
			}
			
		}
	}
	if (toBuild == NULL) {
		for (Continent* c : m->getContinents()) {
			for (Region* r : c->getRegions()) {
				if ((!r->checkCity(p))&&!(r->checkStartingRegion(m))) {
					r->addCity(p);
					return;
				}
			}
		}
	}
	else 
		toBuild->addCity(p);

	
}
	