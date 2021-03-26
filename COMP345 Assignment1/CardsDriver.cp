#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	Deck* d1 = new Deck(2);
	
	Deck* d2 = new Deck(3);
	
	Deck* d3 = new Deck(4);
	
	Card * c = new Card ("Ancient Phoenix", 'a', 25, 3);
	
//	testing friend functions
	cout << *d1 << endl;
}