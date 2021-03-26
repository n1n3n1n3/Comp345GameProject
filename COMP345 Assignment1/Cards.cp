#include <iostream>
#include <string>
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
Card::Card(string n, char t, int g, int a) {
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
	return strm << "\n--------------------\n" << c.name << "\n~~~~~~~~~~~~~~~~~~~~\nGood: " << c.good << "\n~~~~~~~~~~~~~~~~~~~~\nAction: " << c.action << "\n--------------------\n";
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

void Hand::setCardsCosts(){
	//this function could be modified based on cost card values
	this->cards.at(0)->setCost(0);
	this->cards.at(1)->setCost(1);
	this->cards.at(2)->setCost(1);
	this->cards.at(3)->setCost(2);
	this->cards.at(4)->setCost(2);
	this->cards.at(5)->setCost(3);
}


const string Hand::handToString() const{
	string handString = "";
	int i = 0;
	for (Card* c : cards){
		handString += "\n--------------------\n" + c->getName();
		handString += "\n~~~~~~~~~~~~~~~~~~~~\nGood: " + to_string(c->getGood());
		handString += "\n~~~~~~~~~~~~~~~~~~~~\nAction: " + to_string(c->getAction());
		handString += "\n~~~~~~~~~~~~~~~~~~~~\nCost: " + to_string(c->getCost());
		handString += "\n--------------------\nSELECTION#: " + to_string(i) + "\n\n";
		i++;
	}
	return handString;
}

//empty constructor
Deck::Deck(){
}


Deck::Deck(int nbPlayers){
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
	
	//draw six cards to the hand
	vector<Card*> tempHand;
	for (int i = 0; i < 6; i++){
		tempHand.push_back(draw());
	}
	
	//generate hand based on cards drawn
	deckHand = new Hand(tempHand);
	//set the cost of card
	deckHand->setCardsCosts();
}

Deck::Deck(const Deck &d){
	this->deckSize = d.deckSize;
	this->nbPlayers = d.nbPlayers;
	this->cardDeck = d.cardDeck;
	this->deckHand = d.deckHand;
}

////Output
std::ostream& operator<<(std::ostream &strm, const Deck &d) {
	return strm << "++++++++++++ D E C K +++++++++++++\n" << d.deckToString() << "++++++++++++++++++++++++++++++++\n" << endl;
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
	int index = -1;
	for (int i = 0; i < 6; i++){
		if (c == this->deckHand->getCards().at(i)){
			index = i;
		}
	}
	
	if (index == -1){
		cout << "such card does not exist in hand" << endl;
	}
	
	//shift the cards and draw a new one
	else {
		for (int i = index; i < 5; i++){
			deckHand->getCards().at(i) = deckHand->getCards().at(i + 1);
		}
		deckHand->getCards().at(5) = draw();
		
		//adjust card costs
		deckHand->setCardsCosts();
	}
	
}

const string Deck::deckToString() const{
	string temp = "\n+++++++ H A N D +++++++";
	temp += deckHand->handToString();
	temp += "\ndeck has " + to_string(deckSize) + " remaining cards\n";
	return temp;
}