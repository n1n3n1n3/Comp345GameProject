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

void GameObserver::showTurn(){
	cout << "*************DISPLAY TURN ****************" << endl;
	cout << ml->whoseTurn()->getName() << endl;
}