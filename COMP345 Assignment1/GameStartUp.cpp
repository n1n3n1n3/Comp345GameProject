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
	Bid::compareBids();
}

void GameStartUp::placeInitialPieces(vector<Player*> pl, Map* m){
	cout << "adding 4 armies to the starting region for each player" << endl;
	for(int i = 0; i < pl.size(); i++){
		if (pl.at(i)->getName().compare("neutral") != 0){
			m->getStartingRegion()->addArmies(pl.at(i), 4);
		}
	}
	
	// if its a 2 player game
	if (GameStart::getNbPlayers() == 2){
		for (int i = 0; i < 10; i++){
			cout << "+++ place neutral army on map  +++" << endl;
			m->printRegions();
		}
	}
}
