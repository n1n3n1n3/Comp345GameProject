#include <iostream>
#include "AfterAction.h"
#include "gameStart.h"

using namespace std;
//no actual code in this section because it was directly implemented in the card files but this showcases the exchange and slideCardsInHand function
int main(int argc, char *argv[]) {	
	vector<Player*> players;
	players.push_back(new Player("anna"));
	players.push_back(new Player("paul"));
	players = GameStart::setPlayers(players);
	
	Deck* deck = GameStart::setDeck();
	
	cout << *(deck->getHand()) << endl;
	
	players.at(0)->exchange(deck, deck->getHand()->getCards().at(5));
//	players.at(1)->exchange(deck, deck->getHand()->getCards().at(5));
//	players.at(0)->exchange(deck, deck->getHand()->getCards().at(3));
//	players.at(1)->exchange(deck, deck->getHand()->getCards().at(1));
	
	cout << *(deck->getHand()) << endl;

}