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
		void displayGame();
		void displayAction();
		
		
		void getUserInput();
		void viewStatistics();
		void showPlayer();
		void showGameStatistics();
		void showMap();
		void setViewOn(bool setting);
		
		void displayGlobalPlayerAssets();
		void displayPlayerOwnedRegions();
		void displayAllPlayerArmies();
		void displayAllPlayerCities();
		void displayPlayerVictoryPoints();
		void displayGameStatistics();
		
	private:
		Player* currPlayer;
		Hand* currHand;
		MainLoop* ml;
		bool viewOn;
};
