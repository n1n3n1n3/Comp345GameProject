#include <iostream>
#include <list>
#include "GameObserver.h"
#include "mainLoop.h"
#include "Player.h"
#include "Observer.h"

using namespace std;


GameObserver::GameObserver(){
	viewOn = false;
};

GameObserver::GameObserver(MainLoop* ml){
	viewOn = false;
	this->ml = ml;
}

void GameObserver::setViewOn(bool setting){
	viewOn = setting;
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

void GameObserver::viewStatistics(){
	if (viewOn){
	char answer;
	cout << "would you like to view game statistics (y) ?";
	cin >> answer;
	if (answer == 'y'){
		getUserInput();
	}
	}
}
void GameObserver::getUserInput(){
	int entry = 0;
		cout << "would you like to see any of the following :" << endl;
		cout << "(0) global assets (current victory points, regions owned, continents, cities)" << endl;
		cout << "(1) all your owned regions" << endl;
		cout << "(2) your armies on all regions" << endl;
		cout << "(3) your cities" << endl;
		cout << "(4) your current victory points" << endl;
		cout << "(5) global game statistics " << endl;
		cout << "(*) enter any other character to exit" << endl;
		cin >> entry;
		
		switch(entry){
			case 0:
				displayGlobalPlayerAssets();
				break;
			case 1:
				displayPlayerOwnedRegions();
				break;
			case 2: 
				displayAllPlayerArmies();
				break;
			case 3: displayAllPlayerCities();
				break;
			case 4:
				displayPlayerVictoryPoints();
				break;
			case 5:
				displayGameStatistics();
				break;
			default:
				break;
		}
		viewStatistics();
}

void GameObserver::displayGlobalPlayerAssets(){
	cout << " *** GLOBAL [" << currPlayer->getName() << "] ASSETS" << endl;
	currPlayer = ml->getCurrPlayer();
	cout << "total regions: " << ml->getMap()->getPlayersTotalNbRegions(currPlayer) << endl;;
	
}

void GameObserver::displayPlayerOwnedRegions(){
	currPlayer = ml->getCurrPlayer();
	cout << " *** DISPLAYING [" << currPlayer->getName() << "] OWNED REGIONS" << endl;
	for(Region* r : ml->getMap()->getPlayersRegions(currPlayer)){
		cout << r->getName() << ", ";
	}
	cout << ".\n";
}

void GameObserver::displayAllPlayerArmies(){
	currPlayer = ml->getCurrPlayer();
	cout << " *** DISPLAYING [" << currPlayer->getName() << "] PLACED ARMIES" << endl;
	for (Region* r: ml->getMap()->getPlayersRegions(currPlayer)){
		cout << "region: " << r->getName() << " armies: " << r->getNbArmiesByPlayer(currPlayer) << endl;
	}
}

void GameObserver::displayAllPlayerCities(){
	currPlayer = ml->getCurrPlayer();
	cout << "*** DISPLAYING [" << currPlayer->getName() << "] CITIES ***" << endl;
}

void GameObserver::displayPlayerVictoryPoints(){
	cout << "*** DISPLAYING [" << currPlayer->getName() << "] VICTORY POINTS" << endl;
}

void GameObserver::displayGameStatistics(){
	cout << "*** DISPLAYING ENTIRE GAME STATISTICS ***" << endl;
}