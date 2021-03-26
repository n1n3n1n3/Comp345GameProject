#ifndef MAIN_LOOP
#define MAIN_LOOP
#include "map.h"



class MainLoop {
	
private:
	vector<Player*> players; 
	Deck* deck;
	Map* map;
	
	
	static int numPlayers;
	static int turnsRemaining;
	
	friend std::ostream& operator<<(std::ostream&, const MainLoop&);
	
public:
	
	MainLoop(vector<Player*> players, Deck* deck, Map* map);
	MainLoop& operator = (const MainLoop &m);
	Player* whoseTurn() const;
	
	void showBoard();
	
	void takeAction(Card* c);
	
	void singleTurn(Player* p);
	
	void playGame();
	
	
	
};





#endif