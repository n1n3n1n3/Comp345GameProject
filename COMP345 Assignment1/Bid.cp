#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include "Bid.h"

using namespace std;

int Bid::totalBidders = 0;
int Bid::maxCoins = 0;
Bid* Bid::allBidders[4];

Bid::Bid() {
	name = "";
	coinsBet = 0;
}

Bid::Bid(string n) {
	name = n;
	coinsBet = 0;
	allBidders[totalBidders] = this;
	totalBidders++;
}

Bid::Bid(string n, int c) {
	name = n;
	coinsBet = c;
	allBidders[totalBidders] = this;
	totalBidders++;
}

Bid::Bid(const Bid &b) {
	name = b.name;
	coinsBet = b.coinsBet;
}

Bid& Bid::operator = (const Bid &b) {
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Bid &b) {
	return strm << "Player " << b.name << " who bet " << b.coinsBet << " coins.";
}

void Bid::setName(string n) {
	name = n;
}

void Bid::betCoins(int c) {
	coinsBet = c;
}

void Bid::makeBids() {
	cout << "Time to BID X_X\n\nIf it is not your turn, do not peak at your opponents bid!\n";
	switch (totalBidders) {
	case 2:
		maxCoins = 14;
		break;
	case 3:
		maxCoins = 11;
		break;
	case 4:
		maxCoins = 9;
		break;
	}
	for (int i = 0; i < totalBidders; i++) {
		Bid bidder = *allBidders[i];
		int bid = 0;
		bool valid = false;
		while (!valid) {
			cout << bidder.name << ", enter your bid (maximum of " << maxCoins << ") ->";
			cin >> bid;
			if ((bid > maxCoins)||(bid < 0)) {
				cout << "\nInvalid input.\n\n";
			}
			else {
				valid = true;
			}
		}
		bidder.betCoins(bid);
		
		for (int j = 0; j < 100; j++) {
			cout << "\n*";
		}
		if (i == totalBidders-1) {
			cout << "\n\nBidding done, determining winner...\n";
		}
		else {
			cout << "\n\nDon't scroll up or you're a cheater!\n\n";
		}
	}
	
}

Bid Bid::compareBids() {
	for (int i = 0; i <= totalBidders; i++) {
		cout << "\n" << *allBidders[i];
	}
	Bid B  = *allBidders[0];
	return B;
	/*Bid *highestBidder[totalBidders];
	cout << "TOTAL BIDDERS: " << totalBidders;
	int numWinners = 1;
	highestBidder[0] = allBidders[0];
	Bid first = *highestBidder[0];
	cout << "\nFirst bidder: " << first.name << " who bid " << first.coinsBet;
	for (int i = 1; i <= totalBidders; i++) {
		int c0 = first.coinsBet;
		Bid comp = *allBidders[i];
		cout << "\nComparing: " << comp.name << " who bid " << comp.coinsBet;
		if (comp.coinsBet > c0) {
			*highestBidder[0] = comp;
			numWinners = 1;
		}
		else if (comp.coinsBet == c0) {
			*highestBidder[numWinners] = comp;
			numWinners++;
		}
	}
	
	if (numWinners == 1) {
		return *highestBidder[0];
	}
	
	else {
		int winner = 0;
		first = *highestBidder[0];
		string firstS = first.name;
		char str0[firstS.length() + 1];
		strcpy(str0, firstS.c_str());
		for (int i = 0; i < firstS.length(); i++) {
			putchar(tolower(str0[i]));
		}
		firstS = str0;
		
		for (int i = 1; i < numWinners; i++) {
			Bid comp = *highestBidder[i];
			string compS = comp.name;
			char str1[compS.length() + 1];
			strcpy(str1, compS.c_str());
			for (int j = 0; j < firstS.length(); j++) {
				putchar(tolower(str1[j]));
			}
			compS = str1;
			if (firstS.compare(compS) > 0) {
				firstS = compS;
				winner = i;
			} 
		}
		return highestBidder[winner];
	}
	*/
}