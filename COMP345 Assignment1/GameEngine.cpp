#include <iostream>
#include <iostream>
#include <random>
#include "PlayerStrategies.h"
#include "mainLoop.h"
#include "GameStartUp.h"
#include "GameEngine.h"

using namespace std;

Tournament::Tournament() {
	
	int matches;
	int agro = 0;
	int chill = 0;
	
	string p1Name;
	string p2Name;
	int p1Strat;
	int p2Strat;
	int mapChoice;
	
	cout << "# of tournaments to run -> ";
	cin >> matches;
	
	cout << "\nPlayer 1 name: ";
	cin >> p1Name;
	while (true) {
		cout << "\nPlayer 1 strategy: ";
		cin >> p1Strat;
		if ((p1Strat < 0)||(p1Strat > 2))
			cout << "\n..invalid...\n";
		else 
			break;
	}
	cout << "\nPlayer 2 name: ";
	cin >> p2Name;
	while (true) {
		cout << "\nPlayer 2 strategy: ";
		cin >> p2Strat;
		if ((p2Strat < 0)||(p2Strat > 2))
			cout << "\n..invalid...\n";
		else 
			break;
	}
	Map* m = GameStart::selectMap();

	
	ml = new MainLoop;
	
	for (int i = 0; i < matches; i++) {
		//cout << "\nSetting up..." << endl;
		ml->tourneySetup(p1Name, p1Strat, p2Name, p2Strat, m);
		//cout << "\nResetting turns remaining..." << endl;
		ml->setTurnsRemaining(20);
		//cout << "\nSetting tournament mode..." << endl;
		ml->setTournamentMode(true);
		//cout << "\nReady to play game..." << endl;
		
		if (ml->playGame()->getStrat() == "AGRO")
			agro++;
		else
			chill++;
		
		//cout << "\nDone a phase";
	}
	
	cout << "\n\n******************************\nAfter " << matches << " matches........\nAGRO: " << agro << "\nCHILL: " << chill << endl;
	
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