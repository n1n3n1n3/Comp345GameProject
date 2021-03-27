
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include "Bid.h"
#include "Cards.h"

using namespace std;

class Player {

protected:
	static int nextID;

private:
	//give a name and an id to the player
	//Pointers to bjects of territory on Map, hand of Cards, and Bid obkject
	void* ownedTerritory;
	vector<Card*> playerCards;
	void* bidding;
	
	//Attributes
	int coin;
	int army;
	int city;
	string name;
	int id;
	Bid* bid;

	//Output
	friend std::ostream& operator<<(std::ostream&, const Player&);
	
public:
	//Constructor that sets starting coins, copy, assignment
	Player();
	Player(int c);
	Player(string name);
	Player(int c, string name);
	Player(const Player &p);
	Player& operator = (const Player &p);
	
	//setters and getters
	void setName(std::string name);
	void setCoin(int c);
	std::string getName();
	int getId();
	int getCoins();
	vector<Card*> getPlayerCards();
	
	Bid* getBid();
	
	int checkPlacementBonus();
	int checkMovementBonus();
	int checkFlying();
	
	//All possible actions
	void payCoin(int amount);
	void PlaceNewArmies(int a);
	void MoveArmies(int a);
	void MoveOverLand(int a);
	void BuildCity();
	void DestroyArmy();
	void makeBid(int bid);
	void exchange(Deck* d, Card* c);
};

Player* getPlayerById(int id, vector<Player*> playerList);
Player* getPlayerByName(string name, vector<Player*> playerList);

#endif