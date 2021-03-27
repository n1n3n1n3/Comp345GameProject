#include <iostream>
#include "gameStart.h"
#include "GameStartup.h"


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

void GameStartUp::setPlayerTokens(vector<Player*> pl){
	
}

void GameStartUp::chooseStartingRegion(Map* m){
	m->determineStartingRegion();
}

void GameStartUp::makeBids(){
	Bid::makeBids();
}

