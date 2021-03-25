#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>
#include "Player.h"
/*
For actions and goods:

array of two integers [x,y] where x = action type, y = # of times.

If card contains 2 actions, array will be passed as:
[-x1y1, x2y2] for OR
[x1y1, x2y2] for AND


Actions:

1 - Place Armies
2 - Move Armies
3 - Destroy Army
4 - Build City

Goods:
1 - Placement
2 - Movement
3 - Flying
4 - Elixer
5 - Coins
6 - VP/Name (y = Card type)
7 - VP/Set (x1y1, x2y2, - y1 = VPs, x2 = Set Size, y2 = Card Type)
8 - 1VP/ (y = 1 -> 3coins, y = 2 -> flying).
9 - Immune to Attack

*/

class Card {
	
private:
	
	//Card has a name, type, codes of actions and goods
	std::string name;
	char type;
	int action;
	int good;
	
	//Output
	friend std::ostream& operator<<(std::ostream&, const Card&);
	
public:
	
	//Constructors, copy, assignment
	Card();
	Card(std::string n, char t, int a, int g);
	Card(const Card &c);
	Card& operator = (const Card &c);
	
	//Mutators
	void setName(std::string n);
	void setType(char t);
	void setAction(int a);
	void setgood(int g);
	
	//Accessors
	std::string getName();
	char getType();
	int getAction();
	int getGood();
};


class Hand {
	
	//The hand of the deck is an array of 6 Cards
private:
	Card *hand[6];
	int cost[6] = {0, 1, 1, 2, 2, 3};
	//Output
	friend std::ostream& operator<<(std::ostream&, const Hand&);
public:
	
	//Constructors, copy, assignment
	Hand();
	Hand(const Hand &h);
	Hand& operator = (const Hand &h);
	void setHand(Card a, Card b, Card c, Card d, Card e, Card f);
	void addCard(Card c);
	void exchange(Player* p, int index);
};

class Deck {
	
private:
	
	//A deck has a max of 34 cards, a hand, and a size
	Card *cardDeck[34];
	Hand hand;
	int size;
	
	//Output
	friend std::ostream& operator<<(std::ostream&, const Deck&);
public:
	
	//Constructor with num of players, copy, assignment
	Deck(int numPlayers);
	Deck(const Deck &d);
	Deck& operator = (const Deck &d);
	
	//Draw method that returns a card
	Card draw();
	
	//setters and getters
	Hand getHand();
};



#endif