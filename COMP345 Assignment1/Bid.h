#ifndef BID_H
#define BID_H

#include <iostream>
#include <string>


class Bid {
	
//Bid objects have a name and the coins that were bid
private:
	std::string name;
	int coinsBet;
	
	//Static variables to compare all created Bid objects
	static int totalBidders;
	static int maxCoins;
	static Bid *allBidders[4];
	
	//for custom output
	friend std::ostream& operator<<(std::ostream&, const Bid&);
	
public:
	
	//Constructors, copy, assignment
	Bid(std::string n, int c);
	Bid(std::string n);
	Bid();
	Bid(const Bid &b);
	Bid& operator = (const Bid &b);
	
	//Mutators
	void setName(std::string n);
	void betCoins(int c);
	
	//Manually set bids for allBidders
	static void makeBids();
	
	//Compare bids of allBidders
	static Bid compareBids();


};


#endif