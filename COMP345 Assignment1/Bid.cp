#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include "Bid.h"

using namespace std;

int Bid::nbBids = 0;
int Bid::maxBid = 0;
vector<Bid*> Bid::allBids;

Bid::Bid() {
	this->name = "";
	this->coinsBet = 0;
	nbBids++;
	allBids.push_back(this);
}

Bid::Bid(string n){
	this->name = n;
	this->coinsBet = 0;
	nbBids++;
	allBids.push_back(this);
}

Bid::Bid(int c){
	this->name = "";
	this->coinsBet = c;
	nbBids++;
	allBids.push_back(this);
}

Bid::Bid(string n, int c) {
	this->name = n;
	this->coinsBet = c;
	nbBids++;
	allBids.push_back(this);
}

Bid::Bid(const Bid &b) {
	this->name = b.name;
	this->coinsBet = b.coinsBet;
	nbBids++;
	allBids.push_back(this);
}

Bid& Bid::operator = (const Bid &b) {
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Bid &b) {
	return strm << "Player " << b.name << " who bet " << b.coinsBet << " coins.";
}

void Bid::setName(string n){
	this->name = n;
}

void Bid::betCoins(int c){
	this->coinsBet = c;
}

string Bid::getName(){
	return this->name;
}

int Bid::getBid(){
	return this->coinsBet;
}

int Bid::getNbBidders(){
	return allBids.size();
}

vector<Bid*> Bid::getAllBidders(){
	return allBids;
}

vector<int> Bid::getAllBids(){
	vector<int> bids;
	
	for (Bid* b : allBids){
		bids.push_back(b->getBid());
	}
	
	return bids;
}

void Bid::makeBids(){
	//dont make bids if there are no bidders
	if (nbBids <= 0){
		cout << "There are no bidders...can't make bids" << endl;
		return;
	}
	
	cout << "++  Time to BID X_X  ++\nIf it is not your turn, do not peak at your opponents bid!\n";
	
	//adapt max bid to nb of players
	switch (nbBids) {
		case 2:
			cout << "max coin bid is 14\n";
			maxBid = 14;
			break;
		case 3:
			cout << "max coin bid is 11\n";
			maxBid = 11;
			break;
		case 4:
			cout << "max coin bid is 9\n";
			maxBid = 9;
			break;
	}
	
	for (int i = 0; i <nbBids; i++){
		Bid* bidder = allBids.at(i);
		cout << bidder->getName() << endl;
		
		int bid = 0;
		bool valid = false;
		
		while (!valid) {
			cout << bidder->getName() << ", enter your bid (maximum of " << Bid::maxBid << ") -> ";
			cin >> bid;
			if ((bid > Bid::maxBid)||(bid < 0)) {
				cout << "\nInvalid input.\n\n";
			}
			else {
				valid = true;
			}
		}
		bidder->betCoins(bid);
		
		//space between bids so peekers dont peek
		for (int j = 0; j < 100; j++) {
			cout << "\n*";
		}
		
		if (i == nbBids-1) {
			cout << "\n\nBidding done, determining winner...\n";
		}
		
		else {
			cout << "\n\nDon't scroll up or you're a cheater!\n\n";
		}
	}
}

Bid* Bid::compareBids(){
//	Bid* highestBid = new Bid();
//	for (int i = 0; i <= nbBids; i++) {
//		cout << "\n" << *allBids.at(i);
//	}
	vector<int> bids = getAllBids();
	//input
//	for(int b : bids){
//		cout << b << endl;
//	}
	int maxBidIndex = std::max_element(bids.begin(),bids.end()) - bids.begin();
	
	vector<Bid*> maxBidders;
	maxBidders.push_back(allBids.at(maxBidIndex));
	//	check if there is a tie
	for (int i = 0; i < nbBids; i++){
		//add bidder index to the list
		if (i != maxBidIndex && bids.at(maxBidIndex) == bids.at(i)){
			maxBidders.push_back(allBids.at(maxBidIndex));
		}
	}
	
	//if there is a tie find the player with the first alphabetical last name
	if(maxBidders.size() > 1){
		int firstNameIndex = 0;
		//compare name strings
		for (int i = 0; i < maxBidders.size(); i++){
			if (allBids.at(firstNameIndex)->getName() > allBids.at(i)->getName()){
				firstNameIndex = i;
			}
		}
		maxBidIndex = firstNameIndex;
	}
	
	cout << allBids.at(maxBidIndex)->getName() << " won the bet" << endl;
	return allBids.at(maxBidIndex);
}