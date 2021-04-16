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
	void PlaceNewArmies(Player* p, int a, Map* m);
	void MoveArmies(Player* p, int a, Map* m);
	void BuildCity(Player* p, Map* m);
	void DestroyArmy(Player* p, Map* m);
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