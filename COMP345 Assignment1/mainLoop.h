#ifndef MAIN_LOOP
#define MAIN_LOOP
#include "map.h"
#include "gameStart.h"
#include "GameStartUp.h"
#include "Subject.h"


enum State {initiated, bidding, ready, playing, marking, done};

class MainLoop : public Subject{
	
private:
	
	//Core components of game
	vector<Player*> players; 
	Deck* deck;
	Map* map;
	
	//Used to manage game loop & rules
	static int numPlayers;
	static int turnsRemaining;
	
	friend std::ostream& operator<<(std::ostream&, const MainLoop&);
	
	//subject stuff
	State state;
	string currAction;
	Card* currentCard;
	int actionNbArmiesPlaced;
	int actionNbArmiesMoved;
	int action;
	pair<Player*, Region*> currSubjectDestroyedArmies;
	Region* currCityBuild;
	int currSubjectCost;
	
	bool tournamentMode;
	
public:
	MainLoop();
	MainLoop(vector<Player*> players, Deck* deck, Map* map);
	MainLoop& operator = (const MainLoop &m);
	
	//Check whose turn it is
	Player* whoseTurn() const;
	vector<Player*> getPlayers();
	
	//Display Map & Hand
	void showBoard();
	
	//Player takes action of Card just drawn
	void takeAction(Player* p, Card* c);
	
	void singleTurn(Player* p);
	
	Player* playGame();
	
	Player* determineWinner();
	
	//creating two functions to set the game up without calling assignment 2 stuff (cleaner)
	void autoSetup();
	
	void manualSetup();
	
	void tourneySetup(string p1Name, int p1Strat, string p2Name, int p2Strat, Map* m);
	
	//Mutation tings
	void setTurnsRemaining(int t);
	void setTournamentMode(bool t);
	bool getTournamentMode();
	
	
	//Observer stuff
	State getState();
	void setState(State newState);
	
	string getCurrAction();
};





#endif