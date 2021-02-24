#include <iostream>
#include "Player.h"
#include <string>
#include "Bid.h"
#include "Cards.h"
#include "map.h"
#include "mapLoader.h"
#include "mapLoader.h"


using namespace std;
int main(int argc, char *argv[]) {
	
//Bid Section
//	Bid b1("John Jacob");
//	Bid b2("Sam Ham");
//	Bid b3("Felicia Frostberry");
//	Bid b4("Xeno Xenegrade");
//	
//	Bid::makeBids();
//	Bid winner = Bid::compareBids();
//	
//	cout << "Winner of this bid is " << winner;
	
////Player Section
//	Player p1(14);
//	Player p2 = p1;
//	Player p3(10);
//	p2 = p3;
//	
//	cout << "\nOverride of stream insertion operator, displaying of Player object:\n" << p1;
//	
//	p1.PayCoin();
//	p1.PlaceNewArmies();
//	p1.MoveArmies();
//	p1.MoveOverLand();
//	p1.BuildCity();
//	p1.DestroyArmy();
//	
//	cout << "\nEnd of demonstration of Player methods.";
	
	// cards driver
//	int x;
//	bool valid = false;
//	
//	while (!valid) {
//		cout << "Enter number of players: ";
//		cin >> x;
//		if (x > 4 || x < 2) {
//			cout << "Invalid input. Try again.\n";
//		}
//		else {
//			valid = true;
//		}
//	}
//	
//	Deck d(x);
//	cout << d;
//	return 0;


//Map driver
//		cout << "Map driver" << endl;
		
		//	examples of each class
		
		////	region
		//	Region *r = new Region(1, "Pelican", "Albratros", 1);
		//	cout << *r << endl;
		////	continent
		//	Continent *c = new Continent(1, "Albatros");	
		//	cout << *c << endl;
		//	c->addRegion(*r);
		//
		////	map
//		Map *m = new Map("Birds");
//		//	cout << *m << endl;
//		
//		//	//Albatros
//		Continent *c1 = new Continent(1, "Albatros");
//		Region *r1 = new Region(1, "Pelican", "Albratros", 1);
//		c1->addRegion(*r1);
//		c1->addRegion(2, "Plover");
//		c1->addRegion(3, "Swallow");
//		c1->addRegion(4, "Magpie");
//		//	//Duck
//		Continent *c2 = new Continent(2, "Duck");
//		c2->addRegion(8, "Pheasant");
//		c2->addRegion(9, "Pigeon");
//		c2->addRegion(10, "Wren");
//		c2->addRegion(11, "Sparrow");
//		//	
//		Continent *c3 = new Continent(3, "Crow");
//		c3->addRegion(14, "Woodpecker");
//		c3->addRegion(15, "Dove");
//		c3->addRegion(16, "Heron");
//		//	
//		
//		//Adding the continents to the map
//		m->addContinent(*c1);
//		m->addContinent(*c2);
//		m->addContinent(*c3);
//		
//		//Adding the edges to the map
//		m->addBorder({1,2});
//		m->addBorder({2,3});
//		m->addBorder({3,4});
//		m->addBorder({4,14});
//		m->addBorder({8,9,11});
//		m->addBorder({8, 10, 11});
//		//	remove this one to invalidate map by edge connections
//		m->addBorder({11, 14});
//		m->addBorder({14,15,16});
//		
//		//validate
//		cout << m->validate() << endl;
//	}

//Map loader main	
//		MapLoader *ml = new MapLoader("Birds.map");
}