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
//	observer->Update();
	vector<Player*> pl = ml->getPlayers();
	
	for (Player* p : pl){
		cout << p->getName() << endl;
	}
}