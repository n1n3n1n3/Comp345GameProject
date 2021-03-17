#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

int Player::nextID = 0;
//Constructor sets starting coins, consistent # of army and city tokens
//default constructor
Player::Player(){
	army = 0;
	city = 0;
	coin = ' ';
	this->id = ++nextID;
}

Player::Player(int c) {
	army = 18;
	city = 3;
	coin = c;
	cout << "\nNew Player created, parameter of coins passed. Uninitialized void pointers for Territory, cardHand, and Bidding objects yet to be initialized."; 
	this->id = ++nextID;
}

//Copy constructor
Player::Player(const Player &p) {
	army = p.army;
	city = p.city;
	coin = p.coin;
	name = p.name;
	this->id = p.id;
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

std::string Player::getName(){
	return this->name;
}


int Player::getId(){
	return this->id;
}

//Functions that will be defined later
void Player::PayCoin() {
	cout << "\nPayCoin() will subtract a coin from a Player.";
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

