#include <iostream>
#include "gameStart.h"
#include "GameStartUp.h"
//#include "Ca"


void GameStartUp::setCardCost(Deck* d){
	d->setCardCosts();
}

void GameStartUp::shuffleDeck(Deck* d){
	d->shuffle();
}

void GameStartUp::setPlayerPieces(vector<Player*> pl){
	for (Player* p :pl){
		p->setArmy(18);
		p->setCity(3);
	}
}

void GameStartUp::chooseStartingRegion(Map* m){
	m->determineStartingRegion();
}

void GameStartUp::makeBids(){
	Bid::makeBids();
}

void GameStartUp::placeInitialPieces(vector<Player*> pl, Map* m){
	cout << "adding 4 armies to the starting region" << endl;
}
