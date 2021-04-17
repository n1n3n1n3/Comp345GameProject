#include <iostream>
#include <list>
#include "GameObserver.h"
#include "Player.h"

using namespace std;


//Observer virtual class

Observer::Observer(){
};
Observer::~Observer(){};


//Subject virtual class
Subject::Subject(){
	_observers = new list<Observer*>;
};

Subject::~Subject(){
	delete _observers;
};

void Subject::Attach(Observer* o){
	_observers->push_back(o);
};

void Subject::Detach(Observer* o){
	_observers->remove(o);
}

void Subject::Notify(){
	list<Observer * >::iterator i = _observers->begin();
	for (; i != _observers->end(); i++){
		(*i)->Update();
	}
}

GameObserver::GameObserver(){};

GameObserver::GameObserver(MainLoop* ml){
	this->ml = ml;
}

void GameObserver::Update(){
	showTurn();
}

//this function gives the user the option to display extra Information if desired

void GameObserver::userDisplay(){
	cout << currPlayer->getName() << " coins : " << currPlayer->getCoins() << " armies: " << currPlayer->getArmy()<< " cities: " << currPlayer->getCity() << endl;
}
void GameObserver::showTurn(){
	currPlayer = ml->whoseTurn();
	cout << "*************DISPLAY TURN ****************" << endl;
}