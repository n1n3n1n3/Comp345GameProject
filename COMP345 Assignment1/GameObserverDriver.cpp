#include <iostream>
#include "gameStart.h"
#include "GameStartUp.h"
#include "mainLoop.h"
#include "GameObserver.h"

using namespace std;

int main(int argc, char *argv[]) {
	//subject
	MainLoop* ml = new MainLoop();
	//observer
	GameObserver* observer = new GameObserver(ml);
	//attaching observer
	ml->Attach(observer);
	//setting up game
	ml->autoSetup();
	
	ml->singleTurn(ml->getPlayers().at(0));	
	ml->singleTurn(ml->getPlayers().at(1));	
	ml->singleTurn(ml->getPlayers().at(0));	
	ml->singleTurn(ml->getPlayers().at(1));	
}