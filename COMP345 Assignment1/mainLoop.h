#ifndef MAIN_LOOP
#define MAIN_LOOP
#include "map.h"
#include "gameStart.h"
#include "GameStartUp.h"
#include "Subject.h"



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
	string currSubjectState;
	Card* currSubjectCard;
	int currSubjectNbArmiesAdded;
	int currSubjectNbArmiesMoved;
	pair<Player*, Region*> currSubjectDestroyedArmies;
	Region* currCityBuild;
	int currSubjectCost;
	
public:
	MainLoop();
	MainLoop(vector<Player*> players, Deck* deck, Map* map);
	MainLoop& operator = (const MainLoop &m);
	
	//Check whose turn it is
	Player* whoseTurn() const;
	
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
};





#endif