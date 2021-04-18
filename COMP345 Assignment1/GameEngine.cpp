#include <iostream>
#include <iostream>
#include <random>
#include "PlayerStrategies.h"
#include "mainLoop.h"
#include "GameStartUp.h"
#include "GameEngine.h"

using namespace std;

Tournament::Tournament() {
	
	ml = new MainLoop;
	ml->tourneySetup();
	
	ml->setTurnsRemaining(20);
	ml->setTournamentMode(true);
	ml->playGame();
	
	
}

SingleGame::SingleGame() {
	ml = new MainLoop;
	ml->manualSetup();
	ml->setTournamentMode(false);
	ml->playGame();
	
	
}

int main() {
	
	int gameType;
	cout << "*cool startup noise*...\n\nWelc-uhh welcome to the...the game it's time to the we're gonna it's let\'s now time to let\'s play the game right now ok?\n\n\nEnter 0 for Tournament Mode, 1 for a manual Single Game-> ";
	cin >> gameType;
	
	while ((gameType < 0)||(gameType > 1)) {
		cout << "\nThis shouldn't be that hard, there are only two options... -> ";
		cin >> gameType;
	}
	
	if (gameType == 0)
		Tournament t;
	else
		SingleGame s;
	
	
}