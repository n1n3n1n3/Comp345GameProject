#include <iostream>
#include "gameStart.h"
#include "GameStartUp.h"
#include "mainLoop.h"
#include "GameObserver.h"

using namespace std;

int main(int argc, char *argv[]) {
	MainLoop* ml = new MainLoop();
	ml->autoSetup();
	
	GameObserver* observer = new GameObserver(ml);
	ml->Attach(observer);
}