#include <iostream>
#include "gameStart.h"


using namespace std;
int main(int argc, char *argv[]) {

/* select and load map ::
	uses selected map path and generates a map through map loader */

//	Map* map = GameStart::selectMap();
	Map* map = GameStart::selectMap("./maps/BirdsPyramid.map");
	
/* sets game for 2 players
// loads all game pieces
// exchange is implemented in player
// each player has a bidding facility
*/
	//	vector<Player*> players= GameStart::setPlayers();
	vector<Player*> players;
	players.push_back(new Player("anna"));
	players.push_back(new Player("paul"));
	GameStart::setPlayers(players);
	
// PART 1.2.E:: Create a deck of cards for the number of players (2)
	Deck* deck = GameStart::setDeck();

}