#include <iostream>
#include "Player.h"

using namespace std;

int main() {
	
	//Creates player, uses Copy constructor and Assignment operator
	Player p1(14);
	Player p2 = p1;
	Player p3(10);
	p2 = p3;
	
	cout << "\nOverride of stream insertion operator, displaying of Player object:\n" << p1;
	
	//run of methods
	p1.PayCoin();
	p1.PlaceNewArmies();
	p1.MoveArmies();
	p1.MoveOverLand();
	p1.BuildCity();
	p1.DestroyArmy();

	cout << "\nEnd of demonstration of Player methods.";
	
}