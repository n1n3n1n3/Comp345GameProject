#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	
	//Variables to get # of players to determine which cards are in the deck
	int x;
	bool valid = false;
	
	//Determining...
	while (!valid) {
		cout << "Enter number of players: ";
		cin >> x;
		if (x > 4 || x < 2) {
			cout << "Invalid input. Try again.\n";
		}
		else {
			valid = true;
		}
	}
	
	//Make & display the deck + open hand
	Deck d(x);
	cout << d;
	return 0;
}