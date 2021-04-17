#pragma once

class Observer {
public:
	~Observer();
	virtual void Update() = 0;

protected:
	Observer();
};