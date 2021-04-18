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
				cout << "\n\n*** OBSERVER :: GETTING CARD ***" << endl;
				cout << "Player:: " << *(ml->getCurrPlayer()) << " select a card from the hand";
				displayHand();
				if (viewOn){
					getUserInput();
				}
				break;
			}
		case Place:
			cout << "*** OBSERVER:: PLACING ARMIES ***" << endl;
			cout << "Player:: " << *(ml->getCurrPlayer());
			cout << "\n***************************************\nPlacing " << ml->getActionNbArmies() << " armies with a bonus of " << ml->getActionNbArmiesBonus() << " for a total of " << ml->getActionNbArmies() + ml->getActionNbArmiesBonus() << endl;
			cout << "Starting region: (" <<  ml->getStartingRegion()->getId() << ") " << ml->getStartingRegion()->getName()<< endl; 
				displayPlayerCities();
			if (viewOn){
				getUserInput();
			}
			break;
		
		case Move:
			cout << "*** OBSERVER :: MOVING ARMIES ***" << endl;
			cout << "player gets to move amount of armies on the map given by Card" << endl;
			displayPlayerArmies();
			cout << "\n***************************************\nMoving " << ml->getActionNbArmies() << " armies with a bonus of " << ml->getActionNbArmiesBonus() << " for a total of " << ml->getActionNbArmies() + ml->getActionNbArmiesBonus() << endl;
			if (viewOn){
				getUserInput();
			}
			break;
		
		case Destroy:
			{
				cout << "*** ACTION :: DESTROY ARMIES ***" << endl;
				cout << "Player:: " << *(ml->getCurrPlayer()) << " gets to destroy an army of opposing player";
				cout << "list of players" << endl;
				vector<Player*> players = ml->getPlayers();
				for (int i = 0; i < players.size(); i++){
					cout << "[" << i << "] " << players.at(i)->getName() << " ";
				}
				displayAllPlayerArmies();
				cout << "\n" << endl;
				if (viewOn){
					getUserInput();
				}
				break;
			}
		case Build:
			cout << "*** ACTION :: BUILD A CITY ***" << endl;
			cout << "Player:: " << *(ml->getCurrPlayer()) << " gets to build a city on any given region in the map" << endl;
			if (viewOn){
				getUserInput();
			}
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

void GameObserver::getUserInput(){
	if (viewOn){
	char answer;
	cout << "\nwould you like to view game information/statistics (y) (n)?";
	cin >> answer;
	if (answer == 'y'){
		gameStatisticsMenu();
	}
	}
}

void GameObserver::gameStatisticsMenu(){
	int entry = 0;
		cout << "(0) your global assets (regions owned, continents, cities)" << endl;
		cout << "(1) all your owned regions" << endl;
		cout << "(2) your armies on all regions" << endl;
		cout << "(3) all player armies" << endl;
		cout << "(4) your cities" << endl;
		cout << "(5) all player cities" << endl;
		cout << "(6) your current victory points" << endl;
		cout << "(7) all player victory points" << endl;
		cout << "(8) global game statistics " << endl;
		cout << "(9) see Hand" << endl;
		cout << "(9) Exit" << endl;
		cout << "select option :: ";
		cin >> entry;
		
		switch(entry){
			case 0:
				displayGlobalPlayerAssets();
				break;
			case 1:
				displayPlayerOwnedRegions();
				break;
			case 2: 
				displayPlayerArmies();
				break;
			case 3:
				displayAllPlayerArmies();
				break;
			case 4: 
				displayPlayerCities();
				break;
			case 5:
				displayAllPlayerCities();
				break;
			case 6:
				displayPlayerVictoryPoints();
				break;
			case 7: 
				displayAllPlayerVictoryPoints();
				break;
			case 8:
				displayTotalGameStatistics();
				break;
			case 9: 
				displayHand();
			default:
				break;
		}
	if (entry >= 0 && entry < 10){
		getUserInput();
	}
}

void GameObserver::displayHand(){
	cout << "\n~~~ Current Hand (scroll up for details) ~~~ \n" << endl;
	int i = 0;
	for (Card* c : ml->getCurrHand()->getCards()){
		cout << "(" << i << ") [" << c->getName() << " | cost: " << c->getCost() << "]  ";
		
		//formatting detail for my eyes
		if (i == 2){
			cout << "\n";
		}
		i++;
	}
	
	cout << "\n\n ~~~ End of Hand ~~~ \n" << endl;
}

void GameObserver::displayGlobalPlayerAssets(){
	currPlayer = ml->getCurrPlayer();
	cout << " *** GLOBAL [" << currPlayer->getName() << "] ASSETS" << endl;
	cout << "total regions: " << ml->getMap()->getPlayersTotalNbRegions(currPlayer) << endl;;
	cout << "total cities: " << ml->getMap()->getPlayerCities(currPlayer).size() << endl;
	cout << "total cards: " << currPlayer->getPlayerCards().size() << endl; 
}

void GameObserver::displayPlayerOwnedRegions(){
	currPlayer = ml->getCurrPlayer();
	cout << "\n *** DISPLAYING [" << currPlayer->getName() << "] OWNED REGIONS ***" << endl;
	vector<Region*> playersRegions = ml->getMap()->getPlayersRegions(currPlayer);
	
	if (playersRegions.size() == 0){
		cout << currPlayer->getName() << " does not own any regions yet." << endl;
	}
	
	else{
		for(Region* r : playersRegions){
			cout << "[" << r->getId() << "]" << r->getName() << endl;
		}
		cout << ".\n";
	}
}

void GameObserver::displayPlayerArmies(){
	currPlayer = ml->getCurrPlayer();
	cout << "\n *** DISPLAYING [" << currPlayer->getName() << "] PLACED ARMIES ***" << endl;
	if (ml->getMap()->getPlayersTotalNbArmies(currPlayer) == 0){
		cout << " player has no armies... for some reason" << endl;
	}
	for (Continent* c : ml->getMap()->getContinents()){
		for (Region* r : c->getRegions()){
			if(r->getNbArmiesByPlayer(currPlayer) > 0){
				cout << "[" << r->getId() << "] " << r->getName() << " armies: " <<  r->getNbArmiesByPlayer(currPlayer) << endl;
			}
		}
	}
}


void GameObserver::displayPlayerCities(){
	currPlayer = ml->getCurrPlayer();
	cout << "\n*** DISPLAYING [" << currPlayer->getName() << "] CITIES ***" << endl;
	
	vector<Region*> cities = ml->getMap()->getPlayerCities(currPlayer);
	
	if (cities.size() == 0){
		cout << "Player has not yet built any cities" << endl;
	}
	
	else {
		for (Region* r : cities){
			cout << "[" << r->getId() << "] " << r->getName() << ", " << endl;
		}
		cout << "\n";
	}
}

void GameObserver::displayAllPlayerCities(){
	char playerSymbols[4] = {'*', 'x', 'o', '+'};
	vector<Player*> players = ml->getPlayers();
	
	cout << "\n*** DISPLAYING ALL PLAYER CITIES ***" << endl;
	
	for (Player* p : players){
		
		vector<Region*> cities = ml->getMap()->getPlayerCities(p);
		cout << "[" <<p->getName() << "] " << endl; 
		if (cities.size() == 0){
			cout << "Player has not yet built any cities" << endl;
		}
		
		else {
			for (Region* r : cities){
				cout << "[" << r->getId() << "] " << r->getName() << ", " << endl;
			}
			cout << "\n";
		}
	}
}

void GameObserver::displayPlayerVictoryPoints(){
	currPlayer = ml->getCurrPlayer();
	currPlayer->getScore(ml->getMap());
	if (currPlayer->getScore(ml->getMap()) == 0){
		cout << currPlayer->getName() << " has no victory points yet" << endl;
	};
}

void GameObserver::displayAllPlayerVictoryPoints(){
	char playerSymbols[4] = {'*', 'x', 'o', '+'};
	vector<Player*> players = ml->getPlayers();
	
	cout << "\n*** ALL PLAYER VICTORY POINTS ***" << endl;
	
	
	for (Player* p : players){
		p->getScore(ml->getMap());
	}
}

void GameObserver::displayTotalGameStatistics(){
	char playerSymbols[4] = {'*', 'x', 'o', '+'};
	vector<Player*> players = ml->getPlayers();
	
	cout << "\n*** TOTAL GAME STATISTICS ***" << endl;
	
	//show the symbols for the graphs
	cout << "[player symbols]  ";
	for (int i = 0 ; i < players.size(); i++){
		cout << "[ " << players.at(i)->getName() << " -> " << playerSymbols[i] << "  ]  ";
	}
	
	cout << "\n\n[TOTAL ARMIES]   [";
	for (int i = 0; i < players.size(); i++){
		int nbArmies = ml->getMap()->getPlayersTotalNbArmies(players.at(i));
		for (int j = 0; j < nbArmies; j++){
			cout << playerSymbols[i];
		}
	}
	cout << "]" << endl;
	for (Player* p : players){
		cout << p->getName() << ": " << ml->getMap()->getPlayersTotalNbArmies(p) << "    ";
	}
	
	cout << "\n\n[TOTAL CITIES]   [";
	int nbCities;
	
	for (int i = 0; i < players.size(); i++){
				nbCities = ml->getMap()->getPlayerTotalCities(players.at(i));
		for (int j = 0; j < nbCities; j++){
			cout << playerSymbols[i];
		}
	}
	cout << "]" << endl;
	for (Player* p: players){
		cout << p->getName() << ": " << ml->getMap()->getPlayerTotalCities(p) << "  ";
	}
	
	cout <<"\n\n [TOTAL VICTORY POINTS] [";
	for (int i = 0; i < players.size(); i++){
		nbCities = ml->getMap()->getPlayerTotalCities(players.at(i));
		int victoryPoints = players.at(i)->getScore(ml->getMap());
		
		for (int j = 0; j < victoryPoints; j++){
			cout << playerSymbols[i];
		}
		cout << "]\n";
	}
	
	for (Player* p: players){
		p->getScore(ml->getMap());
	}
	cout << "\n\n";
}

void GameObserver::displayAllPlayerArmies(){
	char playerSymbols[4] = {'*', 'x', 'o', '+'};
	vector<Player*> players = ml->getPlayers();
	
	cout << "\n*** DISPLAYING ALL PLAYER ARMIES ***" << endl;
			for (Continent* c : ml->getMap()->getContinents()){
				for (Region* r : c->getRegions()){
					if (r->getTotalArmies() > 0){
					cout << "[" << r->getId() << "] " << r->getName() << "   [";
					for (int i = 0; i < players.size(); i++){
					for(int j = 0; j < r->getNbArmiesByPlayer(players.at(i)); j++){
						cout << playerSymbols[i];
					}
				}
				cout << "]   region owner: " << r->getOwner() << "\n";	
			
					}
				}
	}
}