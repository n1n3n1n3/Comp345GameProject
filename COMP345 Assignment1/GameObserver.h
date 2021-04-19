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
		
		
		void gameStatisticsController();
		
		void gameStatisticsMenu();
		void displayGlobalPlayerAssets();
		void displayPlayerOwnedRegions();
		void displayPlayerArmies();
		void displayAllPlayerArmies();
		void displayPlayerCities();
		void displayAllPlayerCities();
		void displayPlayerVictoryPoints();
		void displayTotalGameStatistics();
		void displayRegionOccupation();
		void displayVictoryPoints();
		void displayAllPlayerVictoryPoints();
		void displayHand();
		
	private:
		Player* currPlayer;
		Hand* currHand;
		MainLoop* ml;
		bool viewOn;
};
