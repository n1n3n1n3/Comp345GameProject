#include <iostream>
#include <list>
#include "GameObserver.h"
#include "mainLoop.h"
#include "Player.h"
#include "Observer.h"

using namespace std;


GameObserver::GameObserver(){};

GameObserver::GameObserver(MainLoop* ml){
	this->ml = ml;
}

void GameObserver::Update(){
	displayGame();
}

//this function gives the user the option to display extra Information if desired
void GameObserver::displayGame(){	
	switch(ml->getState()){
		case Initiated:
			cout << "\n\n*** OBSERVER :: GAME OF EIGHT MINUTE EMPIRE LEGENDS INITIATED ***\n" << endl;
			cout << " the game is created but the game hast not been set up yet" << endl;
			break;
		
		case Bidding:
			cout << "*** OBSERVER :: BIDDING DONE ***\n" << endl;
			cout << ml->getPlayers().at(0)->getName() << " won the bid with " << *(ml->getPlayers().at(0)->getBid()) << " coins\n" << endl;
			cout << "current player assets:" << endl;
			for (Player* p :ml->getPlayers()){
				cout << *p;
			}
			break;
		
		case Ready:
			cout << "\n\n*** GAME OF EIGHT MINUTE EMPIRE LEGENDS READY ***\n" << endl;
			cout << "board, deck and players are set..." << endl;
			cout << "may the best conquerer win..let the game begin!!!" << endl;
			break;
		
		case GetCard:
			{
				cout << "\n*** OBSERVER :: GETTING CARD ***" << endl;
				cout << "Player:: " << *(ml->getCurrPlayer());
				cout << "~~~ Current Hand (scroll up for details) ~~~ " << endl;
				int i = 0;
				for (Card* c : ml->getCurrHand()->getCards()){
					cout << "(" << i << ") [" << c->getName() << " | cost: " << c->getCost() << "]  ";
					
					//formatting detail for my eyes
					if (i == 2){
						cout << "\n";
					}
					i++;
				}
				
				break;
			}
		case Place:
			cout << "*** OBSERVER:: PLACING ARMIES ***" << endl;
			cout << "Player:: " << *(ml->getCurrPlayer());
			cout << "\n***************************************\nPlacing " << ml->getActionNbArmies() << " armies with a bonus of " << ml->getActionNbArmiesBonus() << " for a total of " << ml->getActionNbArmies() + ml->getActionNbArmiesBonus() << endl;
			cout << "Starting region: (" <<  ml->getStartingRegion()->getId() << ") " << ml->getStartingRegion()->getName()<< endl; 
			break;
		
		case Move:
			cout << "*** OBSERVER :: MOVING ARMIES ***" << endl;
			cout << "\n***************************************\nMoving " << ml->getActionNbArmies() << " armies with a bonus of " << ml->getActionNbArmiesBonus() << " for a total of " << ml->getActionNbArmies() + ml->getActionNbArmiesBonus() << endl;
			break;
		
		case Destroy:
			cout << "*** OBSERVER :: DESTROYING ARMIES ***" << endl;
			cout << "Player:: " << *(ml->getCurrPlayer());
			break;
		
		case Build:
			cout << "*** OBSERVER :: BUILDING CITY ***" << endl;
			cout << "Player:: " << *(ml->getCurrPlayer());
			break;
		
		case CountingScore: 
			cout << "*** OBSERVER :: ALL TURNS HAVE BEEN PLAYED ***" << endl;
			cout << "    determining winner     " << endl;
			break;
		case Done:
			cout << "\n\nOBSERVER :: the game is over" << endl;
			break;
	}
}