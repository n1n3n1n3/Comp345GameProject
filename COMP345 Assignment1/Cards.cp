#include <iostream>
#include <string>
#include <algorithm>
#include <random> 
#include "Cards.h"

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
Card::Card(string n, char t, int a, int g) {
	this->name = n;
	this->type = t;
	this->good = g;
	this->action = a;
	this->cost = 0;
}

////Copy
Card::Card(const Card &c) {
	name = c.name;
	type = c.type;
	good = c.good;
	action = c.action;
}


//Assignment operator
Card& Card::operator = (const Card &c) {
	cout << "\nCard Assignment operator used.";
	return *this;
}

//Output
std::ostream& operator<<(std::ostream &strm, const Card &c) {
	return strm << "\n--------------------\n" << c.name << "\n~~~~~~~~~~~~~~~~~~~~\nGood: " << c.getGoodString() << "\n~~~~~~~~~~~~~~~~~~~~\nAction: " << c.getActionString() << "\n--------------------\n";
}

void Card::setName(string n){
	this->name = n;
}

void Card::setType(char t){
	this->type = t;
}

void Card::setAction(int a){
	this->action = a;
}

void Card::setGood(int g){
	this->good = g;
}

void Card::setCost(int c){
	this->cost = c;
}

string Card::getName() {
	return this->name;
}

char Card::getType(){
	return this->type;
}

int Card::getGood(){
	return this->good;
}

int Card::getAction(){
	return this->action;
}

int Card::getCost() {
	return this->cost;
}

/*
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
char Card::getType(int t) const{ 
	switch (t) {
		case 1:
			return 'a';
		break;
		case 2:
			return 'r';
		break;
		case 3:
			return 'c';
		break;
		case 4:
			return 'd';
		break;
		case 5:
			return 'f';
		break;
		case 6:
			return 'm';
		break;
		case 7:
			return 'n';
		break;
		case 8:
			return 'o';
		break;
		default:
			return ' ';
	}
	
}

string Card::getTypeString(int t) const{
	switch (t) {
		case 1:
			return "Ancient";
			break;
		case 2:
			return "Arcane";
			break;
		case 3:
			return "Cursed";
			break;
		case 4:
			return "Dire";
			break;
		case 5:
			return "Forest";
			break;
		case 6:
			return "Mountain";
			break;
		case 7:
			return "Night";
			break;
		case 8:
			return "Noble";
			break;
		default:
			return "invalid";
	}

}

string Card::getGoodString() const{
	if (good == 4152)
		return "1 Elixir AND 2 Coins";
	int len = 0;
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;
	for (int i = good; i > 0; i = i/10) {
		len++;
	}
	if (len == 4) {
		first = good/1000;
		second = (good/100)%10;
		third = (good/10)%10;
		fourth = good%10;
	}
	else if (len == 2) {
		first = good/10;
		second = good%10;
	}
	else {
		first = good;
	}
	
	switch (first) {
		case 1:
			return "+1 Placement";
			break;
		case 2:
			return "+1 Movement";
			break;
		case 3:
			return "+1 Flying";
			break;
		case 4:
			return "+" + to_string(second) + " Elixir";
			break;
		case 5:
			return "+" + to_string(second) + " Coins";
			break;
		case 6:
			return "+1 VP per " + getTypeString(second);
			break;
		case 7:
			return to_string(second) + "VPs for " + to_string(third) + "of type " + getTypeString(fourth);
			break;
		case 8:
			switch(second) {
				case 1:
					return "1 VP per 3 Coins";
					break;
				case 2:
					return "1 VP per Flying";
					break;
				default:
					return "Invalid";
					break;
			}
		case 9:
			return "Immune to attack.";
			break;
		default:
			return "Invalid: must be a single length int.";
	}
	
}


string Card::getActionString() const{
	int len = 0;
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;
	string split = "";
	string ret = "";
	int looper = 1;
	int tempAction = action;
	if (tempAction > 0)
		split = "AND";
	else {
		tempAction*=-1;
		split = "OR";
	}

	for (int i = tempAction; i > 0; i = i/10) {
		len++;
	}
	
	if (len == 4) {
		looper = 2;
				
		first = tempAction/1000;
		second = (tempAction/100)%10;
		third = (tempAction/10)%10;
		fourth = tempAction%10;
		
		
	}
	else if (len == 2) {
		first = tempAction/10;
		second = tempAction%10;
	}
	else {
		first = tempAction;
	}
	
	for (int i = 0; i < looper; i++) {
		if (i == 1) {
			ret+= " " + split + " ";
			first = third;
			second = fourth;
		}
		switch (first) {
			case 1:
				ret+= "Place " + to_string(second) + " Armies.";
				break;
			case 2:
				ret+= "Move " + to_string(second) + " Armies.";
				break;
			case 3:
				ret+= "Destroy an Army.";
				break;
			case 4:
				ret+= "Build a City.";
				break;
			default:
				ret+= "Invalid...";
		}
	}
	return ret;
}


Hand::Hand() {
	//add six new empty cards
	for (int i = 0; i < 6; i++) {
		cards.push_back(new Card);
	}
}

Hand::Hand(const Hand &h){
	for (Card* c: h.cards){
		cards.push_back(c);
	}
}

Hand::Hand(vector<Card*> cardList){
	this->cards = cardList;
}

//Assignment Operator
Hand& Hand::operator = (const Hand &h) {
	cout << "\nHand Assignment operator used.";
	return *this;
}

////Output
std::ostream& operator<<(std::ostream &strm, const Hand &h) {
	return strm << "++++++++++++ H A N D +++++++++++++\n" << h.handToString() << "++++++++++++++++++++++++++++++++\n" << endl;
}

vector<Card*> Hand::getCards(){
	return this->cards;
}

Card* Hand::getCardByIndex(int index){
	return this->cards.at(index);
}

void Hand::slideCards(Card* c){
	int index = -1;
	for (int i = 0; i < 6; i++){
		if (c == this->cards.at(i)){
			index = i;
		}
	}
	
	if (index == -1){
		cout << "such card does not exist in hand" << endl;
	}
	//shift the cards and draw a new one
	
	if (index != 5){
		cout << "\n***************************************\nPART 5: Sliding Cards in the Hand...\n***************************************\n" << endl;
		for (int i = index + 1; i < 6; i++){
				cards.at(i - 1) = cards.at(i);
		}
//		cards.at(5) 
	}
}



void Hand::setHand(Card* a, Card* b, Card* c, Card* d, Card* e, Card* f){
	cout << "x" << endl;
	cards.push_back(a);
	cards.push_back(b);
	cards.push_back(c);
	cards.push_back(d);
	cards.push_back(e);
	cards.push_back(f);
}

void Hand::addCard(Card* c){
	//adds new card at the end of the hand
	cards.push_back(c);
}

void Hand::placeCardAtIndex(Card* c, int index){
	this->cards.at(index) = c;
}

void Hand::setCardsCosts(int cardCostCard[6]){
	for (int i = 0; i < this->cards.size(); i++){
		this->cards.at(i)->setCost(cardCostCard[i]);
	}
}


const string Hand::handToString() const{
	string handString = "";
	int i = 0;
	for (Card* c : cards){
		handString += "\n--------------------\n" + c->getName();
		handString += "\n~~~~~~~~~~~~~~~~~~~~\nGood: " + c->getGoodString();
		handString += "\n~~~~~~~~~~~~~~~~~~~~\nAction: " + c->getActionString();
		handString += "\n~~~~~~~~~~~~~~~~~~~~\nCost: " + to_string(c->getCost());
		handString += "\n--------------------\nSelection #" + to_string(i) + "\n";
		i++;
	}
	
	return handString;
}


void Hand::printCardNames() {
	cout << "\n***************************************\n+++  cards in deck  +++\n***************************************" << endl;
	for (Card* c : cards){
		cout << c->getName() << endl;
	}
	cout << "\n" << endl;
}

//empty constructor
Deck::Deck(){
}

int Hand::getSize() {
	return cards.size();
}


Deck::Deck(int nbPlayers){
	cout << "generating deck for " << nbPlayers << " players." << endl;
	this->nbPlayers = nbPlayers;
	//27 cards if 2 players
	if (nbPlayers >= 2) {
		this->deckSize = 27;
		cardDeck.push_back(new Card ("Ancient Phoenix", 'a', 25, 3));
		cardDeck.push_back(new Card("Ancient Sage", 'a', 23, 61));
		cardDeck.push_back(new Card("Ancient Tree Spirit", 'a', 14, 43));
		cardDeck.push_back(new Card("Ancient Woods", 'a', 4011, 1));
		cardDeck.push_back(new Card("Cursed Banshee", 'c', 26, 42));
		cardDeck.push_back(new Card("Cursed Gargoyles", 'c', 25, 3));
		cardDeck.push_back(new Card("Cursed King", 'c', -1324, 41));
		cardDeck.push_back(new Card("Cursed Mausoleum", 'c', 4, 2));
		cardDeck.push_back(new Card("Cursed Tower", 'c', 4, 82));
		cardDeck.push_back(new Card("Dire Dragon", 'd', 1330, 3));
		cardDeck.push_back(new Card("Dire Eye",'d', 14, 3));
		cardDeck.push_back(new Card("Dire Giant", 'd', 1330, 9));
		cardDeck.push_back(new Card("Dire Goblin", 'd', 25, 41));
		cardDeck.push_back(new Card("Dire Ogre", 'd', 22, 81));
		cardDeck.push_back(new Card("Forest Elf", 'f', -1322, 1));
		cardDeck.push_back(new Card("Forest Gnome", 'f', 22, 43));
		cardDeck.push_back(new Card("Forest Pixie",'f', 24, 1));
		cardDeck.push_back(new Card("Forest Tree Town", 'f', 4, 2));
		cardDeck.push_back(new Card("Graveyard", 'g', 12, 63));
		cardDeck.push_back(new Card("Lake", 'l', -1223, 65));
		cardDeck.push_back(new Card("Night Hydra", 'n', 2530, 1));
		cardDeck.push_back(new Card("Night Village", 'n', 4, 1));
		cardDeck.push_back(new Card("Night Wizard", 'n', 1330, 67));
		cardDeck.push_back(new Card("Noble Hills", 'o', 13, 7438));
		cardDeck.push_back(new Card("Noble Knight", 'o', 1430, 2));
		cardDeck.push_back(new Card("Noble Unicorn", 'o', 2411, 2));
		cardDeck.push_back(new Card("Stronghold", 's', 4, 64));
	}

	if (nbPlayers >= 3) {
		this->deckSize = 32;
		cardDeck.push_back(new Card("Arcane Manticore", 'r', 1430, 2));
		cardDeck.push_back(new Card("Arcane Sphinx", 'r', 1324, 3));
		cardDeck.push_back(new Card("Arcane Temple", 'r', 23, 62));
		cardDeck.push_back(new Card("Mountain Dwarf", 'm', 1230, 7326));
		cardDeck.push_back(new Card("Mountain Treasury", 'm', 23, 4152));
	}
	
	if (nbPlayers == 4) {
		this->deckSize = 34;
		cardDeck.push_back(new Card("Castle", 'q', 1340, 41));
		cardDeck.push_back(new Card("Castle 2", 'q', 2340, 41));
	}
	
	cout << "added " << this->deckSize << " cards to the deck" << endl;

	
	cout << "placing card cost card aside & drawing hand" << endl;
	//draw six cards to the hand
	vector<Card*> tempHand;
	for (int i = 0; i < 6; i++){
		tempHand.push_back(draw());
	}
	
	cardCostCard[0] = 0;
	cardCostCard[1] = 1;
	cardCostCard[2] = 1;
	cardCostCard[3] = 2;
	cardCostCard[4] = 2;
	cardCostCard[5] = 3;
	//generate hand based on cards drawn
	deckHand = new Hand(tempHand);
	//set the cost of card
	deckHand->setCardsCosts(cardCostCard);
}

Deck::Deck(const Deck &d){
	this->deckSize = d.deckSize;
	this->nbPlayers = d.nbPlayers;
	this->cardDeck = d.cardDeck;
	this->deckHand = d.deckHand;
	
	for (int i = 0; i < 6; i++){
		this->cardCostCard[i] = d.cardCostCard[i];
	}
}



////Output
std::ostream& operator<<(std::ostream &strm, const Deck &d) {
	return strm << "\n***************************************\n++++++++++++ D E C K +++++++++++++\n" << d.deckToString() << "++++++++++++++++++++++++++++++++\n***************************************\n" << endl;
}

Card* Deck::draw(){
	srand(time(0));
	int select = rand() % this->deckSize;
	//create a copy of the card inside the deck
	Card* c = new Card(*cardDeck.at(select));
	//remove the card from the deck
	this->cardDeck.erase(this->cardDeck.begin() + select);
	this->deckSize--;
	//Return drawn card
	return c;
}

int Deck::getDeckSize(){
	return this->deckSize;
}

int Deck::getNbPlayers(){
	return this->nbPlayers;
}

vector<Card*> Deck::getCardDeck(){
	return this->cardDeck;
}

Hand* Deck::getHand(){
	return this->deckHand;
}

void Deck::slideCardInHand(Card* c){
	
	deckHand->slideCards(c);
	
	if (this->deckSize > 0)
		deckHand->placeCardAtIndex(draw(), 5);
	else {
		deckHand->getCards().pop_back();
	}
	//adjust card costs
	this->setCardCosts();
	//if (this->deckSize == 0)
	//	deckHand->getCards().pop_back();
}

void Deck::setCardCosts(){
	cout << "\n***************************************\n++++++++++++ setting cards cost ++++++++++++\n***************************************\n" << endl;
	deckHand->setCardsCosts(this->cardCostCard);
}

void Deck::shuffle(){
	cout << "\n***************************************\n++++++++++++ shuffling deck ++++++++++++\n***************************************\n" << endl;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cardDeck.begin(), cardDeck.end(), g);
}

const string Deck::deckToString() const{
	string temp = "\n+++++++ H A N D +++++++";
	temp += deckHand->handToString();
	temp += "\n***************************************\ndeck has " + to_string(deckSize) + " remaining cards\n***************************************\n***************************************\n";
	return temp;
}