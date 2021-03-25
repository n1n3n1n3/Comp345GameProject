#include <iostream>
#include <vector>
#include "Player.h"
//#include "Bid.h"

using namespace std;

int main() {
	int nbPlayers = 2;
	//Creates player, uses Copy constructor and Assignment operator
	Player* p1 = new Player(14, "anna");
	Player* p2 = new Player(10, "paul");

	vector<Player*> listOfPlayers = vector<Player*>();
	listOfPlayers.push_back(p1);
	listOfPlayers.push_back(p2);
	
	p1->makeBid(3);
	p2->makeBid(4);
	Bid::compareBids();
}