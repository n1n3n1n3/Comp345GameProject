#include <iostream>
#include "gameStart.h"
#include "GameStartUp.h"
#include "mainLoop.h"
#include "GameObserver.h"
#include "GameStartUp.h"	


using namespace std;

int main(int argc, char *argv[]) {
	MainLoop* ml = new MainLoop();
	ml->autoSetup();
	
	GameObserver* observer = new GameObserver();
	ml->Attach(observer);
}