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

void GameStartUp::setPlayerPieces(vector<Player*> pl, Map* m){
	cout << "\n+++++++++++ setting player pieces ++++++++++" << endl;
	cout << "       each player has 18 armies and 3 cities" << endl;
	for (Player* p :pl){
		p->setCoin(14);
		p->setArmy(18);
		p->setCity(3);
	}
	m->loadPlayers(pl);
	cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void GameStartUp::chooseStartingRegion(Map* m){
	m->determineStartingRegion();
}

Player* GameStartUp::makeBids(vector<Player*> pl){
	Bid::makeBids();
	Bid* winningBid = Bid::compareBids();
	for (Player* p: pl){
		if (p->getName().compare(winningBid->getName()) == 0 && p->getName() != "neutral"){
			cout << "++++++++++++++++++++++++++++++++++++" << endl;
			p->payCoin(p->getBid()->getBid());
			return p;
		}
	}
	cout << "error :: nobody won the bid" << endl;
	return new Player();
}

void GameStartUp::placeInitialPieces(vector<Player*> pl, Map* m){
	cout << "\n+++++++++++ Placing initial Armies ++++++++++" << endl;
	for(int i = 0; i < pl.size(); i++){
		if (pl.at(i)->getName().compare("neutral") != 0){
			cout << "\n";
			m->getStartingRegion()->addArmies(pl.at(i), 4);
		}
	}
	cout << endl;
//	
	// if its a 2 player game
	int currPlayer = 0;
	if (GameStart::getNbPlayers() == 2){
		int neutralArmyIndexes[10];
		cout << "--- adding neutral armies to the board---" << endl;
		m->printRegions();
		for (int i = 0; i < 10; i++){
			cout << "[" << i << "] " << pl.at(currPlayer)->getName() << " place 1 neutral army on map  (enter index): ";
			int index;
			cin >> neutralArmyIndexes[i];
			
			//while the player is entering an invalid id
			while(!m->hasRegionById(neutralArmyIndexes[i])){
				cout << neutralArmyIndexes[i] << " is an invalid region id please enter an index (integer): ";
				cin >> neutralArmyIndexes[i];
			}
			
			m->getRegionById(neutralArmyIndexes[i])->addArmies(pl.at(2), 1);
			currPlayer = (currPlayer + 1)% 2;
		}
		cout << "\nNeutral armies were added to regions";
		for (int i = 0; i < 10; i++){
			cout << " " << neutralArmyIndexes[i] << " ";
		}
		cout << endl;
	}
}

void GameStartUp::placeInitialPieces(vector<Player*> pl, Map* m, int indexes[10]){
	cout << "\n+++++++++++ Placing initial Armies ++++++++++" << endl;
	for(int i = 0; i < pl.size(); i++){
		if (pl.at(i)->getName().compare("neutral") != 0){
			cout << "\n";
			m->getStartingRegion()->addArmies(pl.at(i), 4);
		}
	}
	cout << endl;
	//	
	// if its a 2 player game
	int currPlayer = 0;
	if (GameStart::getNbPlayers() == 2){
		int neutralArmyIndexes[10];
		cout << "--- adding neutral armies to the board---" << endl;
		m->printRegions();
		for (int i = 0; i < 10; i++){
			cout << "[" << i << "] " << pl.at(currPlayer)->getName() << " placed 1 neutral army on region " << indexes[i] << endl;
			
			m->getRegionById(indexes[i])->addArmies(pl.at(2), 1);
			currPlayer = (currPlayer + 1)% 2;
		}
		cout << "\nNeutral armies were added to regions";
		for (int i = 0; i < 10; i++){
			cout << " " << indexes[i] << " ";
		}
		cout << endl;
	}
}
