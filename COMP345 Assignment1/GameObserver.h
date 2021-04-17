#pragma once
#include <vector>
#include <list>
#include "Player.h"
#include "mainLoop.h"
#include "Observer.h"


class GameObserver : public Observer{
	public:
		GameObserver();
		GameObserver(MainLoop* ml);
		void Update();
		void showTurn();
		void userDisplay();
	private:
		Player* currPlayer;
		MainLoop* ml;
};