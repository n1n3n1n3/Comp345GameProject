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
	cout << ml->getState() << endl;
//	showTurn();
	displayGame();
}

//this function gives the user the option to display extra Information if desired

//void GameObserver::userDisplay(){
////	cout << currPlayer->getName() << " coins : " << currPlayer->getCoins() << " armies: " << currPlayer->getArmy()<< " cities: " << currPlayer->getCity() << endl;
//}
void GameObserver::displayGame(){	
	switch(ml->getState()){
		case initiated:
			cout << "\n\n*** GAME OF EIGHT MINUTE EMPIRE LEGENDS INITIATED ***" << endl;
			cout << " the game is created but the game hast not been set up yet" << endl;
			break;
		case ready:
			cout << "\n\n*** GAME OF EIGHT MINUTE EMPIRE LEGENDS READY ***" << endl;
			cout << "board, deck and players are set..." << endl;
			cout << "may the best conquerer win..let the game begin!!!" << endl;
			break;
		case bidding:
			break;
		case playing:
			cout << "*** PLAYING ACTION***" << endl;
			break;
		case marking: 
			cout << "*** ALL TURNS HAVE BEEN PLAYED ***" << endl;
			cout << "determining winner" << endl;
			break;
		case done:
			cout << "\n\nthe game is over" << endl;
	}
}