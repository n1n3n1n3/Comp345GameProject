#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

int main() {
	
	//Creates player, uses Copy constructor and Assignment operator
	Player p1(14, "anna");
	Player p2 = p1;
	Player p3(10, "paul");
	p2 = p3;
	vector<Player*> listOfPlayers = vector<Player*>();
	listOfPlayers.push_back(&p1);
	listOfPlayers.push_back(&p2);
	cout << "\nOverride of stream insertion operator, displaying of Player object:\n" << p1;
	
	//run of methods
	p1.PayCoin();
	p1.PlaceNewArmies();
	p1.MoveArmies();
	p1.MoveOverLand();
	p1.BuildCity();
	p1.DestroyArmy();

	cout << "\nEnd of demonstration of Player methods.";
	getPlayerById(1, listOfPlayers);
	getPlayerByName("anna", listOfPlayers);
}