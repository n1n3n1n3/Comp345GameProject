#pragma once
#include <vector>
#include <list>
#include "Player.h"

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;
};

class GameObserver : public Observer{
	public:
		GameObserver();
		GameObserver(list<Player*> players);
		void Update();
		void showTurn();
	private:
		Player* currPlayer;
		list<Player*> players;		
};