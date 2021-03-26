#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
//#include "Cards.h"

using namespace std;

int Player::nextID = 0;
//Constructor sets starting coins, consistent # of army and city tokens
//default constructor
Player::Player(){
	this->army = 0;
	this->city = 0;
	this->coin = 0;
	this->id = ++nextID;
	this->bid = new Bid();
}

Player::Player(string name){
	this->army = 18;
	this->city = 3;
	this->id = ++nextID;
	this->name = name;
	this->bid = new Bid(name);
}

Player::Player(int c, string name){
	this->army = 18;
	this->city = 3;
	this->coin = c;
	this->id = ++nextID;
	this->name = name;
	this->bid = new Bid(name);
}

Player::Player(int c) {
	this->army = 18;
	this->city = 3;
	this->coin = c;
	this->bid = new Bid();
	cout << "\nNew Player created, parameter of coins passed. Uninitialized void pointers for Territory, cardHand, and Bidding objects yet to be initialized."; 
	this->id = ++nextID;
}

//Copy constructor
Player::Player(const Player &p) {
	this->army = p.army;
	this->city = p.city;
	this->coin = p.coin;
	this->name = p.name;
	this->id = p.id;
	this->bid = new Bid(*p.bid);
	cout << "\nCopy Constructor used.";
}

//Assignment operator
Player& Player::operator = (const Player &p) {
//	cout << "\nAssignment operator used.";
	return *this;
}

//Output
std::ostream& operator<<(std::ostream &strm, const Player &p) {
	return strm << "Player has...\n" << p.coin << " coins.\n" << p.city <<" cities.\n" << p.army << " armies.";
}

void Player::setName(std::string name){
	this->name = name;
}

void Player::setCoin(int c){
	this->coin = c;
}

int Player::getCoins(){
	return this->coin;
}

std::string Player::getName(){
	return this->name;
}


int Player::getId(){
	return this->id;
}


vector<Card*> Player::getPlayerCards() {
	return this->playerCards;
}


Bid* Player::getBid(){
	return this->bid;
}

//Functions that will be defined later
void Player::payCoin(int amount) {
	if (this->coin -= amount < 0){
		cout << "player has insufficient funds" << endl;
	}
	else {
		this->coin -= amount;
		cout << "player:" << this->name << " paid " << amount << "and now has " << this->coin << " coins";
	}
}

void Player::PlaceNewArmies() {
	cout << "\nPlaceNewArmies() will let a Player place an army somewhere on the board.";
}
void Player::MoveArmies() {
	cout << "\nMoveArmies() will move an army to any space, over land or water.";
}
void Player::MoveOverLand() {
	cout << "\nThis function will move an army to only adjacent land spaces, not over water.";
}
void Player::BuildCity() {
	cout << "\nBuildCity() will let a Player place a city somewhere on the board.";
}
void Player::DestroyArmy() {
	cout << "\nDestroyArmy() will let a Player choose an army on the board to remove.";
}

void Player::makeBid(int bid){
	if (bid > this->coin){
		cout << "cannot make bid greater than the number of coins" << endl;
	}
	else {
		this->bid->betCoins(bid);
	}
}

void Player::exchange(Deck* d, Card* c){
	if (this->getCoins() < c->getCost()){
			cout << "player has insufficient funds";
			return;
	}
	else {
		// pay the cost
		this->coin = this->coin - c->getCost();
		// add card to the players list
		playerCards.push_back(c);
		
		d->slideCardInHand(c);
	}
}

Player* getPlayerById(int id, vector<Player*> playerList){
	cout << "getting player by ID" << endl;
	for(Player* p: playerList){
			if(p->getId() == id){
				return p;
			}
		}
	//return empty player
	cout << "no player with id " << id << endl;
	return new Player();
}

Player* getPlayerByName(string name, vector<Player*> playerList){
	cout << "getting player by Name" << endl;
	for(Player* p: playerList){
		if((p->getName()).compare(name) == 0){
			return p;
		}
	}
	cout << "no player with name " << name << endl;
	//return empty player
	return new Player();
}
