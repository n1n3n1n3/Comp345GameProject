#include <iostream>
#pragma once

#ifndef STRAT
#define STRAT
#include "map.h"
//#include "Cards.h"
using namespace std;




class Strategy {
public:
	
	Strategy();
	virtual ~Strategy();
	virtual Card* chooseCard(Player* p, Map* m, Deck* d) = 0;
	virtual int getPriority(Card* c);
	virtual int safelyOwned(Player* p, Region* r);
	virtual Region* findTarget(Player* p, Map* m);
	virtual vector<Region*> findPath(Player*, Map* m, Region* r);
	
	virtual void PlaceNewArmies(Player* p, int a, Map* m);
	virtual void MoveArmies(Player* p, int a, Map* m);
	virtual void BuildCity(Player* p, Map* m);
	virtual void DestroyArmy(Player* p, Map* m);
};



class humanPlayer : public Strategy {
public:
	Card* chooseCard(Player* p,Map* m, Deck* d);
	void PlaceNewArmies(Player* p, int a, Map* m);
	void MoveArmies(Player* p, int a, Map* m);
	void BuildCity(Player* p, Map* m);
	void DestroyArmy(Player* p, Map* m);
};


class agroPlayer : public Strategy {
public:
	Card* chooseCard(Player* p, Map* m, Deck* d);
	int getPriority(Card* c);
	int getPriority(Player* p, Card* c, Map* m);
	void PlaceNewArmies(Player* p, int a, Map* m);
	void MoveArmies(Player* p, int a, Map* m);
	void BuildCity(Player* p, Map* m);
	void DestroyArmy(Player* p, Map* m);
	int safelyOwned(Player* p, Region* r);
	Region* findTarget(Player* p, Map* m);
	vector<Region*> findPath(Player*, Map* m, Region* r);
};


class chillPlayer : public Strategy {
public:
	Card* chooseCard(Player* p, Map* m, Deck* d);
	int getPriority(Card* c);
	void PlaceNewArmies(Player* p, int a, Map* m);
	void MoveArmies(Player* p, int a, Map* m);
	void BuildCity(Player* p, Map* m);
	void DestroyArmy(Player* p, Map* m);
};





#endif