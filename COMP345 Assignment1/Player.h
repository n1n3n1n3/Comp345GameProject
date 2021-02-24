
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player {
private:
	
	//Pointers to bjects of territory on Map, hand of Cards, and Bid obkject
	void* ownedTerritory;
	void* cardHand;
	void* bidding;
	
	//Attributes
	int coin;
	int army;
	int city;
	std::string name;

	//Output
	friend std::ostream& operator<<(std::ostream&, const Player&);
	
public:
	
	//Constructor that sets starting coins, copy, assignment
	Player(int c);
	Player(const Player &p);
	Player& operator = (const Player &p);
	
	//All possible actions
	void PayCoin();
	void PlaceNewArmies();
	void MoveArmies();
	void MoveOverLand();
	void BuildCity();
	void DestroyArmy();
	
};




#endif