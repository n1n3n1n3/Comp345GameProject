#include <iostream>
#include <string>
#include "Cards.h"
#include "Player.h"

using namespace std;


//Default constructor for Card
Card::Card() {
	this->name = "";
	this->type = ' ';
	this->good = 0;
	this->action = 0;
	this->cost = 0;
}

//Constructor
Card::Card(string n, char t, int g, int a) {
	this->name = n;
	this->type = t;
	this->good = g;
	this->action = a;
	this->cost = 0;
}

//Copy
Card::Card(const Card &c) {
	this->name = c.name;
	this->type = c.type;
	this->good = c.good;
	this->action = c.action;
}

//Assignment operator
Card& Card::operator = (const Card &c) {
	cout << "\nCard Assignment operator used.";
	return *this;
}

//Output
std::ostream& operator<<(std::ostream &strm, const Card &c) {
	return strm << "\n--------------------\n" << c.name << "\n~~~~~~~~~~~~~~~~~~~~\nGood: " << c.good << "\n~~~~~~~~~~~~~~~~~~~~\nAction: " << c.action << "\n--------------------\n";
}

//mutators
void Card::setCost(int c){
	this->cost = c;
}

//Accessor
string Card::getName() {
	return this->name;
}

int Card::getCost() {
	return this->cost;
}
/*
For actions and goods:

integers xy where x = action type, y = # of times.

If card contains 2 actions, array will be passed as:
-wxyz for OR
wxyz for AND


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
7 - VP/Set (wxyz, - x = VPs, y = Set Size, z = Card Type) (a = 1, r = 2, c = 3, d = 4, f = 5, m = 6, n = 7,, o = 8)
8 - 1VP/ (y = 1 -> 3coins, y = 2 -> flying).
9 - Immune to Attack

*/

//Constructing the deck
Deck::Deck(int numPlayers) {
	
	//27 cards if 2 players
	if (numPlayers >= 2) {
		size = 27;
		cardDeck[0] = new Card("Ancient Phoenix", 'a', 25, 3);
		cardDeck[1] = new Card("Ancient Sage", 'a', 23, 61);
		cardDeck[2] = new Card("Ancient Tree Spirit", 'a', 14, 43);
		cardDeck[3] = new Card("Ancient Woods", 'a', 4011, 1);
		cardDeck[4] = new Card("Cursed Banshee", 'c', 26, 42);
		cardDeck[5] = new Card("Cursed Gargoyles", 'c', 25, 3);
		cardDeck[6] = new Card("Cursed King", 'c', -1324, 41);
		cardDeck[7] = new Card("Cursed Mausoleum", 'c', 4, 2);
		cardDeck[8] = new Card("Cursed Tower", 'c', 4, 82);
		cardDeck[9] = new Card("Dire Dragon", 'd', 1330, 3);
		cardDeck[10] = new Card("Dire Eye",'d', 14, 3);
		cardDeck[11] = new Card("Dire Giant", 'd', 1330, 9);
		cardDeck[12] = new Card("Dire Goblin", 'd', 25, 41);
		cardDeck[13] = new Card("Dire Ogre", 'd', 22, 81);
		cardDeck[14] = new Card("Forest Elf", 'f', -1322, 1);
		cardDeck[15] = new Card("Forest Gnome", 'f', 22, 43);
		cardDeck[16] = new Card("Forest Pixie",'f', 24, 1);
		cardDeck[17] = new Card("Forest Tree Town", 'f', 4, 2);
		cardDeck[18] = new Card("Graveyard", 'g', 12, 63);
		cardDeck[19] = new Card("Lake", 'l', -1223, 65);
		cardDeck[20] = new Card("Night Hydra", 'n', 2530, 1);
		cardDeck[21] = new Card("Night Village", 'n', 4, 1);
		cardDeck[22] = new Card("Night Wizard", 'n', 1330, 67);
		cardDeck[23] = new Card("Noble Hills", 'o', 13, 7438);
		cardDeck[24] = new Card("Noble Knight", 'o', 1430, 2);
		cardDeck[25] = new Card("Noble Unicorn", 'o', 2411, 2);
		cardDeck[26] = new Card("Stronghold", 's', 4, 64);
		
	}
	
	//32 cards if 3 players
	if (numPlayers >= 3) {
		size = 32;
	
	
		cardDeck[27] = new Card("Arcane Manticore", 'r', 1430, 2);
		cardDeck[28] = new Card("Arcane Sphinx", 'r', 1324, 3);
		cardDeck[29] = new Card("Arcane Temple", 'r', 23, 62);
		cardDeck[30] = new Card("Mountain Dwarf", 'm', 1230, 7326);
		cardDeck[31] = new Card("Mountain Treasury", 'm', 23, 4152);
		
	}
	
	//34 cards if 4 players
	if (numPlayers == 4) {
		size = 34;

		cardDeck[32] = new Card("Castle", 'q', 1340, 41);
		cardDeck[33] = new Card("Castle 2", 'q', 2340, 41);
	
	}

	//Set the initial Hand by drawing 6 cards
	hand.setHand(draw(0), draw(1), draw(1), draw(2), draw(2), draw(3));
	
}

//Copy constructor of Deck
Deck::Deck(const Deck &d) {
	size = d.size;
	for (int i = 0; i < size; i++) {
		cardDeck[i] = d.cardDeck[i];
	}
	hand = d.hand;
	
}

//Assignment Operator
Deck& Deck::operator = (const Deck &d) {
	cout << "\nDeck Assignment operator used.";
	return *this;
}

//Output
std::ostream& operator<<(std::ostream &strm, const Deck &d) {
	return strm << "\nThis deck has a current size of " << d.size << " (excluding the hand of 6), \nwith the following hand:\n" << d.hand;
}


//Draw method that returns a Card
Card Deck::draw(int cost) {
	//Select a random number within the bounds of the array
	srand(time(0));
	int select = rand() % size;
	Card c = *cardDeck[select];
	//set the cost of the card
	c.setCost(cost);
	//Reorder the deck to fill in the drawn card
	for (int i = select; i < size; i++) {
		cardDeck[i] = cardDeck[i+1];
	}
	
	//Restructure deck
	cardDeck[size-1] = new Card;
	size--;
	
	//Return drawn card
	return c;
}

Hand Deck::getHand(){
	return this->hand;
}

void Deck::drawCardToHand(){
	hand.shiftHand();
	hand.getHand() = draw(3);
}

//Hand defaut constructor of blank Cards
Hand::Hand() {
	for (int i = 0; i < 6; i++) {
		hand[i] = new Card;
	}
}

//Hand Copy
Hand::Hand(const Hand &h) {
	for (int i = 0; i < 6; i++) {
		hand[i] = h.hand[i];
	}
}

//Assignment Operator
Hand& Hand::operator = (const Hand &h) {
	cout << "\nHand Assignment operator used.";
	return *this;
}

//Output
std::ostream& operator<<(std::ostream &strm, const Hand &h) {
	return strm << "Coin Cost 0: " << *h.hand[0] << "\n\nCoin Cost 1: " << *h.hand[1] << "\n\nCoin Cost 1: " << *h.hand[2] << "\n\nCoin Cost 2: " << *h.hand[3] << "\n\nCoin Cost2: " << *h.hand[4] << "\n\nCoin Cost 3: " << *h.hand[5];
}


//void Hand::addCard(int index) {
//	hand[index] =
//}

//Initially set hands
void Hand::setHand(Card a, Card b, Card c, Card d, Card e, Card f) {
	hand[0] = new Card(a);
	hand[1] = new Card(b);
	hand[2] = new Card(c);
	hand[3] = new Card(d);
	hand[4] = new Card(e);
	hand[5] = new Card(f);
}

void Hand::shiftHand(){
	for (int i = 1; i < 6; i++){
		//set the cost to the new cost
		hand[i]->setCost(hand[i - 1]->getCost());
		//swap the elements
		hand[i - 1] = hand[i];
	}
}

Card*[6] Hand::getHand(){
	return this->hand;
}

//This will allow players to exchange coins for a card
//void Hand::exchange(Player* p, int index) {
////	check if player has enough coins
//	if (p->getCoins() < cost[index]){
//		cout << "player has insufficient funds";
//		return;
//	}
//	
//	else {
//		p->payCoin(cost[index]);
//		
//	}
//}