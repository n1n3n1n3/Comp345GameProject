#include <iostream>
#include <random>
#include "PlayerStrategies.h"
#include "mainLoop.h"
#include "GameStartUp.h"

using namespace std;
int main() {
	
	int matches;
	int agro = 0;
	int chill = 0;
	
	cout << "***Strategy Battle Sim***" << endl;
	cout << "num iterations: ";
	cin >> matches;
	
	
	
	for (int i = 0; i < matches; i++) {
		cout << i << endl;
		cout.ios_base::setstate(ios_base::failbit);
		//	Map* map = GameStart::selectMap();
		Map* map = GameStart::selectMap("./maps/BirdsL.map");
		
		//	//manually enter players
		//	vector<Player*> players= GameStart::setPlayers();
		
		vector<Player*> players;
		players.push_back(new Player("MAËLLE"));
		players.push_back(new Player("SIMON"));
		
		players = GameStart::setPlayers(players);
		
		if (i%2 == 1) {
			players.at(0)->setStrat(1);
			players.at(1)->setStrat(2);
		}
		else {
			players.at(0)->setStrat(2);
			players.at(1)->setStrat(1);
		}
		
		
		GameStartUp::setPlayerPieces(players, map);
		
		Deck* deck = GameStart::setDeck();
		//part one
		GameStartUp::shuffleDeck(deck);
		GameStartUp::setCardCost(deck);
		
		
		//	GameStartUp::placeInitialPieces(players, map);
		
		
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> distr(1, 20);
		
		int index[10];
		for (int i = 0; i < 10; i++) {
			index[i] = distr(gen);
			cout << index[i] << endl;
		}
		
		GameStartUp::placeInitialPieces(players, map, index);
		players.erase(players.begin()+2);
		/*Player* startingPlayer = GameStartUp::makeBids(players);
		
		
		if (players.front() != startingPlayer) {
			int pos;
			for (int i = 0; i < players.size(); i++) {
				if (players.at(i) == startingPlayer)
					pos = i;
			}
			Player* temp = players.at(0);
			players.at(0) = startingPlayer;
			players.at(pos) = temp;
			
		}*/
		
		MainLoop game = MainLoop(players, deck, map);
		
		if (game.playGame()->getStrat() == "AGRO")
			agro++;
		else
			chill++;
		
		cout.ios_base::clear();
	}
	
	cout << "\n\n******************************\nAfter " << matches << " matches........\nAGRO: " << agro << "\nCHILL: " << chill << endl;
	
}