// Subject.h

#pragma once
#include <iostream>
#include <list>
using namespace std;

class Observer;

class Subject {
  public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	string getState();
	Subject();
	~Subject();
  private:
	list<Observer*> *_observers;
	string state;
};