#pragma once
#include <iostream>
#include <string>




#ifndef PLAYER_H
#define PLAYER_H


#include "Bid.h"
#include "Cards.h"


using namespace std;

class Map;
class Continent;
class Region;
class Strategy;


class Player {

protected:
	static int nextID;

private:
	//give a name and an id to the player
	//Pointers to objects of territory on Map, hand of Cards, and Bid object
	
	vector<Card*> playerCards;
	vector<pair<Card*, int>> scoringCards;
	void* bidding;
	
	//Attributes
	int regionsOwned;
	int coin;
	int elixir;
	int army;
	int city;
	string name;
	int id;
	Bid* bid;
	Strategy* strat;
	

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
	
	void setArmy(int a);
	void setCity(int c);
	int getArmy();
	int getCity();
	void setOwned(int o);
	int getOwned();
	
	
	//setters and getters
	void setName(std::string name);
	void addCoin(int c);
	void addElixir(int e);
	void setCoin(int c);
	std::string getName();
	int getId();
	int getCoins();
	vector<Card*> getPlayerCards();
	int getElixir();
	void setStrat(int s);
	string getStrat();
	
	Bid* getBid();
	
	int checkPlacementBonus();
	int checkMovementBonus();
	int checkFlying();
	
	//Action helpers
	bool checkPlacementValidity(Map* m, Region* r);
	
	//All possible actions
	void payCoin(int amount);
	void PlaceNewArmies(int a, Map* m);
	void MoveArmies(int a, Map* m);
	int MoveOverLand(int a, Region* start, Region* move);
	int MoveOverWater(int a, Region* start, Region* move);
	void BuildCity(Map* m);
	void DestroyArmy(Map* m);
	void AndOrAction();
	void makeBid(int bid);
	bool exchange(Deck* d, Card* c);
	
	Card* selectCard(Map* m, Deck* d);
	
//<<<<<<< HEAD
	pair<string, vector<int>> computeScore(Map* m);
//=======
	//int computeScore(Map* m);
	int getScore(Map* m);
//>>>>>>> f7e30149c02f5dc6992803337df4717084231ff3
	int cardScore(Card* c, int q);
	
};

Player* getPlayerById(int id, vector<Player*> playerList);
Player* getPlayerByName(string name, vector<Player*> playerList);

#endif