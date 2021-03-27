#ifndef GAMESTARTUP_H
#define GAMESTARTUP_H

#include <iostream>

#include "map.h"
#include "mapLoader.h"
#include "Cards.h"
#include "gameStart.h"

using namespace std;

class GameStartUp {
public:
	static void setCardCost();
	static void shuffleDeck();
	static void setPlayerPieces();
	static void setPlayerTokens();
	static void makeBids();
};

#endif