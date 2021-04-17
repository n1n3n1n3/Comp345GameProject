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
}

//this function gives the user the option to display extra Information if desired

void GameObserver::userDisplay(){
//	cout << currPlayer->getName() << " coins : " << currPlayer->getCoins() << " armies: " << currPlayer->getArmy()<< " cities: " << currPlayer->getCity() << endl;
}
void GameObserver::showTurn(){
//	currPlayer = ml->whoseTurn();
	cout << "*************DISPLAY TURN ****************" << endl;
}