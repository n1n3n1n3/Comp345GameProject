#ifndef BID_H
#define BID_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bid {
private:
	//class variables
	static int maxBid;
	static int nbBids;
	static vector<Bid*> allBids;
	//instance variables
	string name;
	int coinsBet;
	//friend functions
	friend std::ostream& operator<<(std::ostream&, const Bid&);

public:
//	constructors
	Bid();
	Bid(int c);
	Bid(string n);
	Bid(string n, int c);
	Bid(const Bid &b);
	Bid& operator = (const Bid &b);
	
//	setters
	void setName(string n);
	void betCoins(int c);
	
//	getters
	string getName();
	int getBid();
	
// static functions
	static int getNbBidders();
	static vector<Bid*> getAllBidders();
	static vector<int> getAllBids();
	static void makeBids();
	static Bid* compareBids();
};



#endif