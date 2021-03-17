
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

class Player {

protected:
	static int nextID;

private:
	//give a name and an id to the player
	//Pointers to bjects of territory on Map, hand of Cards, and Bid obkject
	void* ownedTerritory;
	void* cardHand;
	void* bidding;
	
	//Attributes
	int coin;
	int army;
	int city;
	string name;
	int id;

	//Output
	friend std::ostream& operator<<(std::ostream&, const Player&);
	
public:
	//Constructor that sets starting coins, copy, assignment
	Player();
	Player(int c);
	Player(int c, string name);
	Player(const Player &p);
	Player& operator = (const Player &p);
	
	//setters and getters
	void setName(std::string name);
	std::string getName();
	int getId();
	
	//All possible actions
	void PayCoin();
	void PlaceNewArmies();
	void MoveArmies();
	void MoveOverLand();
	void BuildCity();
	void DestroyArmy();
	
};

Player* getPlayerById(int id, vector<Player*> playerList);
Player* getPlayerByName(string name, vector<Player*> playerList);

#endif