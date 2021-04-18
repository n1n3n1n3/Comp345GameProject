#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include "mainLoop.h"
#include "gameStart.h"
#include "GameStartUp.h"

using namespace std;

int MainLoop::numPlayers = 0;
int MainLoop::turnsRemaining = 0;

MainLoop::MainLoop(){
	state = initiated;
}
//Constructor that currently can only handle a 2 player game
MainLoop::MainLoop(vector<Player*> players, Deck* deck, Map* map) {
	this->players = players;
	this->deck = deck;
	this->map = map;
	this->numPlayers = players.size();
	state = initiated;
	if (numPlayers == 2)
		this->turnsRemaining = 26;
	else {
		cout << "\n*Error*, must be two players.";
		exit(0);
	}
}


//Displays whose turn is it and how many game turns remain
std::ostream& operator<<(std::ostream& strm, const MainLoop& m) {
	Player* turn = m.whoseTurn();
	return strm << "It is " << turn->getName() << "'s turn. " << m.turnsRemaining << " turns remaining in the game.";
}

void MainLoop::setState(State newState) {
	state = newState;
	Notify();
}

State MainLoop::getState(){
	return state;
}

vector<Player*> MainLoop::getPlayers(){
	return players;
}

//Check whose turn it is
Player* MainLoop::whoseTurn() const{
	//int turn = turnsRemaining%(this->players.size());
	return this->players.at(turnsRemaining%numPlayers);
}

void MainLoop::setTurnsRemaining(int t) {
	this->turnsRemaining = t;
}

void MainLoop::setTournamentMode(bool t) {
	this->tournamentMode = t;
}

bool MainLoop::getTournamentMode() {
	return this->tournamentMode;
}



//Display Map&Hand
void MainLoop::showBoard() {
	cout << "\n***************************************\n"; 
	map->printMap();
	
	cout << *deck;
	
}

//Determine the action from a card and have the player execute the action
void MainLoop::takeAction(Player* p, Card *c) {
	
	bool andAction = false;
	bool orAction = false;
	int bonus = 0;
	int num = 0;
	int len = 0;
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;
	string split = "";
	string ret = "";
	int looper = 1;
	int tempAction = c->getAction();
	if (tempAction < 0) {
		orAction = true;
		tempAction*=-1;
	}
	
	for (int i = tempAction; i > 0; i = i/10) {
		len++;
	}
	
	if (len == 4) {
		if (!orAction) {
			andAction = true;
			looper = 2;
		}
		
		first = tempAction/1000;
		second = (tempAction/100)%10;
		third = (tempAction/10)%10;
		fourth = tempAction%10;
	}
	else if (len == 2) {
		first = tempAction/10;
		second = tempAction%10;
	}
	else {
		first = tempAction;
	}
	
	for (int i = 0; i < looper; i++) {

		if (orAction) {
			if (p->getStrat() == "HUMAN") {
				int choice = 0;
				cout << *c << endl;
				cout << "\n***************************************\nWhich action would you like to take? (0 or 1, anything else for skip.) ->";
				cin >> choice;
				
				if (choice == 1) {
					first = third;
					second = fourth;
				}
			}
			else if (p->getStrat() == "AGRO") {
				if ((third == 3)||(third == 2)) {
					first = third;
					second = fourth;
				}
				
			}
			
		}
		
		
		if (i == 1) {
			if (p->getStrat() == "HUMAN") {
				int choice = 0;
				cout << *c <<endl;
				cout << "\n***************************************\nWould you like to take the second action? (0 for No, 1 for Yes) ->";
				cin >> choice;
				if (choice == 1) {
					first = third;
					second = fourth;
				}
				else
					break;
			}
			else {
				first = third;
				second = fourth;
			}
		}
		map->printMap();
		switch (first) {
			case 1:
				bonus = p->checkPlacementBonus();
				num = second + bonus;
				cout << "\n***************************************\nPlacing " << second << " armies with a bonus of " << bonus << " for a total of " << num;
				
				p->PlaceNewArmies(num, map);
				
				//subject state elements
				currAction = "place";
				actionNbArmiesPlaced = num;
				
				break;
			case 2:
				bonus = p->checkMovementBonus();
				num = second + bonus;
				cout << "\n***************************************\nMoving " << second << " armies with a bonus of " << bonus << " for a total of " << num << ".\nMoving over water costs " << p->checkFlying() << " per Army.";
				
				p->MoveArmies(num, map);
				
				//subject state elements
				currAction = "move";
				actionNbArmiesMoved = num;
				break;
			case 3:
				cout << "\n***************************************\nDestroying an army...";
				p->DestroyArmy(map);
				
				//subject state elements
				currAction = "destroy";
				
				break;
			case 4:
				cout << "\n***************************************\nBuilding a city...";
				
				p->BuildCity(map);
				
				//subject state elements
				currAction = "build";
				
				break;
			default:
				ret+= "\n***************************************\nInvalid...";
		}
//		Notify();
	}
	
}

//A single turn
void MainLoop::singleTurn(Player *p) {
	
	//Display the Map & Hand
	showBoard();
	//Show the player all their cards, end turn
	cout << "\n\n**************************\nHere are all your cards: \n";
	for (Card* c : p->getPlayerCards()) {
		cout << *c;
	}
	
	cout << *deck;
	
	if (!tournamentMode) {
		int St;
		cout << "\n\n" << p->getName() << ". Your current Strategy is " << p->getStrat() << ".\nEnter 0 to change the strategy, anything else to skip->";
		cin >> St;

		if (St == 0) {
			while (true) {
				int s;
				cout << "\nEnter 0 for Human, 1 for AgroCPU, 2 for ChillCPU ->";
				cin >> s;
				if ((s < 0)||(s > 2))
					cout << "\nInvalid...." << endl;
				else {
					p->setStrat(s);
					break;
				}
			}
		}

	}	
	
	
	
	//Player chooses the card they want from the hand
	Card* theCard = p->selectCard(this->map, this->deck);
	currentCard = theCard;
	//check Immune card
	if (theCard->getGood() == 9)
		map->setImmunePlayer(p);
	
	//Player takes the action of the Card
	takeAction(p, theCard);
//	Notify();
//		cout << "\n***************************************\n...Turn Over...\n***************************************\n\n";
}

Player* MainLoop::playGame() {
	
	//Welcome message
	cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n*~*~Welcome to Eight-Minute Empire: Legends!~*~*\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
	setState(playing);
	//cout << "\nPast setState" << endl;
	//Fixed # of turns per game to manage the mainloop
	while (turnsRemaining > 0) {
		//cout << "\nIn the Loop" << endl;
		//determine whose turn
		Player* thePlayer = whoseTurn();
		//cout << "\nDetermined WhoseTurn" << endl;
		//Run turn for the player
		singleTurn(thePlayer);
		
		//Decrement turns
		turnsRemaining--;
	}
	
	setState(marking);
	
	cout << "\nCard limit reached! Time to tally the score...\n";
	Player* theWinner = determineWinner();
	
	cout << "\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n*~*~*!Congratulations to " << theWinner->getName() << " for their victory!*~*~*\n*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n";
	
	setState(done);
	cout << "\n\n...............\n.......Goodbye for now.......\n...............";
	
	return theWinner;
}

Player* MainLoop::determineWinner() {
	Player* winner = players.at(0);
	
	vector<pair<string, vector<int>>> allScores;
	
	allScores.push_back(players.at(0)->computeScore(this->map));
	int winningScore = allScores.at(0).second.at(3);
	
	for (int i = 1; i < numPlayers; i++) {
		allScores.push_back(players.at(i)->computeScore(this->map));
		int compareScore = allScores.at(i).second.at(3);
		if (compareScore > winningScore) {
			winningScore = compareScore;
			winner = players.at(i);
		}
		else if (compareScore == winningScore) {
			if (winner->getCoins() < players.at(i)->getCoins()) {
				winner = players.at(i);
				cout << "\nTIE! But " << winner->getName() << " has more coins, so they are the winner!\n";
			}
			else if (winner->getCoins() > players.at(i)->getCoins()) {
				cout << "\nTIE! But " << winner->getName() << " has more coins, so they are the winner!\n";
			}
			else if (winner->getOwned() < players.at(i)->getOwned()) {
				winner = players.at(i);
				cout << "\nTIE! Even with coins! But " << winner->getName() << " has more regions, so they are the winner!\n";
			}
			else
				cout << "\nTIE! Even with coins! But " << winner->getName() << " has more regions, so they are the winner!\n";
		}
	}
	cout.ios_base::clear();
	
	cout << fixed << setprecision(2);
	
	cout << "*--------*-----------*-------*-------*-----------*\n| PLAYER | TERRITORY | CARDS | COINS | TOTAL VPs |\n";
	
	for (int i = 0; i < numPlayers; i++) {
		cout << left << "*--------*-----------*-------*-------*-----------*\n" 
		<< "| " << setw(7) << allScores.at(i).first 
		<< "| " << setw(10) << allScores.at(i).second.at(0) 
		<< "| " << setw(6) << allScores.at(i).second.at(1)  
		<< "| " << setw(6) << allScores.at(i).second.at(2)  
		<< "| " << setw(10) << allScores.at(i).second.at(3)  
		<< "|" << endl;
		
	}
	cout << "*--------*-----------*-------*-------*-----------*\n";
	
	return winner;
}

void MainLoop::autoSetup(){
	map = GameStart::selectMap("./maps/BirdsL.map");
	
	vector<Player*> pl;
	pl.push_back(new Player("anna"));
	pl.push_back(new Player("paul"));
	pl = GameStart::setPlayers(pl);
	
	players = pl;
	
	GameStartUp::setPlayerPieces(pl, map);
	deck = GameStart::setDeck();
	GameStartUp::setPlayerPieces(pl, map);
	GameStartUp::shuffleDeck(deck);
	GameStartUp::setCardCost(deck);
	
	int index[10] = {13,9,4,8,8,7,3,15,14,11};
	GameStartUp::placeInitialPieces(players, map, index);
	pl.erase(pl.begin()+2);
	
	//too lay to make this fully manual
	Player* startingPlayer = GameStartUp::makeBids(players);
	
//	if (players.at(0) != startingPlayer){
	for (int i = 0; i < players.size(); i++){
		if (players.at(i) == startingPlayer){
			cout << "***" << startingPlayer->getName() << endl;
			players.erase(players.begin() + i);
			players.insert(players.begin(), startingPlayer);
		}
	}
//	}
	
	setState(bidding);

	//setting game state for the observer
	setState(ready);
}

void MainLoop::manualSetup(){
	this->map = GameStart::selectMap();
	
	this->players = GameStart::setPlayers();
	
	
	
	GameStartUp::setPlayerPieces(players, map);
	this->deck = GameStart::setDeck();
	GameStartUp::setPlayerPieces(players, map);
	GameStartUp::shuffleDeck(deck);
	GameStartUp::setCardCost(deck);
	
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
	
	Player* startingPlayer = GameStartUp::makeBids(players);
	
	if (players.size() == 2) {
		this->turnsRemaining = 26;
		this->numPlayers = 2;
	}
		
	
	//	if (players.at(0) != startingPlayer){
	for (int i = 0; i < players.size(); i++){
		if (players.at(i) == startingPlayer){
			cout << "***" << startingPlayer->getName() << endl;
			players.erase(players.begin() + i);
			players.insert(players.begin(), startingPlayer);
		}
	}
	
	
	//setting game state for the observer
	//setState(ready);
}

void MainLoop::tourneySetup(string p1Name, int p1Strat, string p2Name, int p2Strat, Map* m) {
	players.clear();
	cout << "\nSetting map..." << endl;
	this->map = m;
	

	cout << "\nPushing Players..." << endl;	
	players.push_back(new Player(14, p1Name));
	players.push_back(new Player(14, p2Name));
	
	cout << "\nSetting Strats " << p1Strat << " and " << p2Strat << "..." << endl;
	players.at(0)->setStrat(p1Strat);
	players.at(1)->setStrat(p2Strat);
	

	
	cout.ios_base::setstate(ios_base::failbit);
	cout << "\nSetting Players..." << endl;
	this->players = GameStart::setPlayers(players);
	
	
	cout << "\nSetting Pieces..." << endl;
	GameStartUp::setPlayerPieces(players, map);
	cout << "\nSetting Deck..." << endl;
	this->deck = GameStart::setDeck();
	//GameStartUp::setPlayerPieces(players, map);
	GameStartUp::shuffleDeck(deck);
	GameStartUp::setCardCost(deck);
	
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1, 20);
	
	int index[10];
	for (int i = 0; i < 10; i++) {
		index[i] = distr(gen);
		cout << index[i] << endl;
	}
	cout << "\nPlacing Initial Pieces..." << endl;
	GameStartUp::placeInitialPieces(players, map, index);
	players.erase(players.begin()+2);
	cout << "\nMaking Bids..." << endl;
	Player* startingPlayer = GameStartUp::makeBids(players);
	
	if (players.size() == 2) {
		this->turnsRemaining = 26;
		this->numPlayers = 2;
	}
	
	
	//	if (players.at(0) != startingPlayer){
	for (int i = 0; i < players.size(); i++){
		if (players.at(i) == startingPlayer){
			cout << "***" << startingPlayer->getName() << endl;
			players.erase(players.begin() + i);
			players.insert(players.begin(), startingPlayer);
		}
	}
	
	
	//setting game state for the observer
	//setState(ready);
}



