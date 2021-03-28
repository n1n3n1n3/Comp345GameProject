#ifndef MAIN_LOOP
#define MAIN_LOOP
#include "map.h"



class MainLoop {
	
private:
	
	//Core components of game
	vector<Player*> players; 
	Deck* deck;
	Map* map;
	
	//Used to manage game loop & rules
	static int numPlayers;
	static int turnsRemaining;
	
	friend std::ostream& operator<<(std::ostream&, const MainLoop&);
	
public:
	
	MainLoop(vector<Player*> players, Deck* deck, Map* map);
	MainLoop& operator = (const MainLoop &m);
	
	//Check whose turn it is
	Player* whoseTurn() const;
	
	//Display Map & Hand
	void showBoard();
	
	//Player takes action of Card just drawn
	void takeAction(Player* p, Card* c);
	
	void singleTurn(Player* p);
	
	void playGame();
	
	Player* determineWinner();
	
	
};





#endif