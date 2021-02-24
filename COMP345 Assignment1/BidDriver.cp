/*



*/
#include <iostream>
#include <string>
#include "Bid.h"

using namespace std;
int main() {
	
	//Creating 4 bidding objects with set names + bids
	Bid b1("John Jacob", 1);
	Bid b2("Sam Ham", 2);
	Bid b3("Felicia Frostberry", 4);
	Bid b4("Xeno Xenegrade", 3);
	
	//If we want to manually set the bids instead
	//Bid::makeBids();
	
	cout << "\nShowing a clear winner:\n";
	Bid winner = Bid::compareBids();
	cout << "\nWinner of this bid is " << winner <<"\n\nShowing a tie:\n";
	
	//Updating bids to test ties
	b1.betCoins(1);
	b2.betCoins(3);
	b3.betCoins(2);
	b4.betCoins(3);
	Bid winner1 = Bid::compareBids();
	cout << "\nWinner of this bid is " << winner1 <<"\n\nShowing all 0:\n";
	
	b1.betCoins(0);
	b2.betCoins(0);
	b3.betCoins(0);
	b4.betCoins(0);
	Bid winner2 = Bid::compareBids();
	cout << "\nWinner of this bid is " << winner2;
	
}