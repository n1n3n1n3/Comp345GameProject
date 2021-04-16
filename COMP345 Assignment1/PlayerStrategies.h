#include <iostream>


#ifndef STRAT
#define STRAT
#include "map.h"
#include "Cards.h"
using namespace std;

//class Player;


class Strategy {
public:

	virtual ~Strategy();
	virtual Card* chooseCard(Player* p, Map* m, Deck* d) = 0;
	virtual int getPriority(Card* c) = 0;
	
};



class humanPlayer : public Strategy {
public:
	Card* chooseCard(Player* p,Map* m, Deck* d);
};


class agroPlayer : public Strategy {
public:
	Card* chooseCard(Player* p, Map* m, Deck* d);
	int getPriority(Card* c);
};


class chillPlayer : public Strategy {
public:
	Card* chooseCard(Player* p, Map* m, Deck* d);
	int getPriority(Card* c);
};





#endif