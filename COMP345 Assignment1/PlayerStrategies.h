#include <iostream>
#pragma once

#ifndef STRAT
#define STRAT
#include "map.h"
//#include "Cards.h"
using namespace std;




class Strategy {
public:
	string name;
	Strategy();
	//virtual ~Strategy() = 0;
	
	virtual Card* chooseCard(Player* p, Map* m, Deck* d) = 0;
	virtual int getPriority(Card* c) = 0;
	virtual int safelyOwned(Player* p, Region* r) = 0;
	virtual Region* findTarget(Player* p, Map* m) = 0;
	virtual vector<Region*> findPath(Player*, Map* m, Region* r) = 0;
	
	virtual void PlaceNewArmies(Player* p, int a, Map* m) = 0;
	virtual void MoveArmies(Player* p, int a, Map* m) = 0;
	virtual void BuildCity(Player* p, Map* m) = 0;
	virtual void DestroyArmy(Player* p, Map* m) = 0;
};



class humanPlayer : public Strategy {
public:
	humanPlayer();
	Card* chooseCard(Player* p,Map* m, Deck* d);
	void PlaceNewArmies(Player* p, int a, Map* m);
	void MoveArmies(Player* p, int a, Map* m);
	void BuildCity(Player* p, Map* m);
	void DestroyArmy(Player* p, Map* m);
	
	//Garbage
	int getPriority(Card* c);
	int safelyOwned(Player* p, Region* r);
	Region* findTarget(Player* p, Map* m);
	vector<Region*> findPath(Player*, Map* m, Region* r);
};


class agroPlayer : public Strategy {
public:
	agroPlayer();
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
	chillPlayer();
	Card* chooseCard(Player* p, Map* m, Deck* d);
	int getPriority(Card* c);
	void PlaceNewArmies(Player* p, int a, Map* m);
	void MoveArmies(Player* p, int a, Map* m);
	void BuildCity(Player* p, Map* m);
	void DestroyArmy(Player* p, Map* m);
	
	int safelyOwned(Player* p, Region* r);
	Region* findTarget(Player* p, Map* m);
	vector<Region*> findPath(Player*, Map* m, Region* r);
};





#endif