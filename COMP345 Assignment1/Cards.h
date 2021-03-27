#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Card {
private:
	string name;
	char type;
	int action;
	int good;
	int cost;
	
	friend std::ostream& operator<<(std::ostream&, const Card&);
	
public:
	Card();
	Card(std::string n, char t, int a, int g);
	Card(const Card &c);
//	Card(Card* c);
	Card& operator = (const Card &c);
	
	//Mutators
	void setName(std::string n);
	void setType(char t);
	void setAction(int a);
	void setGood(int g);
	void setCost(int c);
	
	//Accessors
	std::string getName();
	char getType();
	int getAction();
	int getGood();
	int getCost();
	
	std::string getTypeString(int t) const;
	std::string getGoodString() const;
	std::string getActionString() const;
};

class Hand {
private:
	vector<Card*> cards;
	friend std::ostream& operator<<(std::ostream&, const Hand&);
public:
	Hand();
	Hand(const Hand &h);
	Hand(vector<Card*> cardList);
	Hand& operator = (const Hand &h);
	void setHand(Card a, Card b, Card c, Card d, Card e, Card f);
	
	vector<Card*> getCards();
	Card* getCardByIndex(int index);
	void setHand(Card* a, Card* b, Card* c, Card* d, Card* e, Card* f);
	void setHand(vector<Card*> cardList);
	void addCard(Card* c);
	//draws a card and shifts hand
	void placeCardAtIndex(Card* c, int index);
	void setCardsCosts();
	const string handToString() const;
	void slideCards(Card* c);
	
	//print functions
	void printCardNames();
};


class Deck {
private:	
	int nbPlayers;
	int deckSize;
	vector<Card*> cardDeck;
	Hand* deckHand;
	
	friend std::ostream& operator<<(std::ostream&, const Deck&);

public:
//	constructors
	Deck();
	Deck(int nbPlayers);
	Deck(const Deck &d);
	Deck& operator = (const Deck &d);
	
	int getNbPlayers();
	int getDeckSize();
	vector<Card*> getCardDeck();
	Hand* getHand();
	
	Card* draw();
	void shuffle();
	void slideCardInHand(Card* c);
	const string deckToString() const;
};

#endif