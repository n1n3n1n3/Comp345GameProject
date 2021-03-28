#include "gameStart.h"
#include "mapLoader.h"
#include <dirent.h>
#include <sys/types.h>
#include <filesystem>
namespace fs = std::filesystem;


//instantiate static variables
string GameStart::path = "";
int GameStart::nbPlayers = 0;
MapLoader* GameStart::mapLoader = new MapLoader();
Deck* GameStart::deck = new Deck();
vector<string> GameStart::mapFiles = vector<string>();
vector<Player*> GameStart::players = vector<Player*>();


//default constructor
GameStart::GameStart(){
}

Map* GameStart::selectMap(){
	//load the files in path
	loadMapFilePaths();
	//display available maps
	cout << "+++		Available Maps		+++" << endl;
	for (int i = 0; i < mapFiles.size(); i++){
		cout << "(" << i << ") " << mapFiles.at(i).substr(0, mapFiles.at(i).size() - 4) << endl;
	}
	//let player choose map
	int entry;
	cout << "choose map file: ";
	cin >> entry;
	
	//mildly manage bad entries
	while(entry < 0 || entry > mapFiles.size()){
		cout << "please enter valid number within options" << endl;
		cin >> entry;
	}
	
	path = "./maps/" + mapFiles.at(entry);
	//load the map fromt the path
	cout << "...loading file from path: " << path << endl;
	//load the map from file with the map loader
	
	//set the path, load the map and validate (already does it in the mapload constructor
	mapLoader = new MapLoader(path);
	//determine starting region
	//return generated map
	return mapLoader->getMap();
}


Map* GameStart::selectMap(string path){
	//load the map fromt the path
	cout << "...loading file from path: " << path << endl;
	//load the map from file with the map loader
	
	//set the path, load the map and validate (already does it in the mapload constructor
	mapLoader = new MapLoader(path);
	
	//return generated map
	return mapLoader->getMap();
}


//function that loads all available maps in the maps directory
void GameStart::loadMapFilePaths(){
	struct dirent *entry;
	DIR *dir = opendir("./maps");
	string temp;
	
	if (dir == NULL) {
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		temp = entry->d_name;
		if (temp.find(".map") != -1){
			mapFiles.push_back(temp);
		}
	}
	closedir(dir);
}

vector<Player*> GameStart::setPlayers(){
//	int nbPlayers;
	
	cout << "Enter number of players (2-4): ";
	cin >> nbPlayers;
	
	//prompt the user to enter a correct amount
	while (nbPlayers < 2 || nbPlayers > 4){
		cout << "enter a number of players between 2 and 4" << endl;
		cin >> nbPlayers;
	}
	
	int startCoins;
	switch(nbPlayers){
		case 2:
			startCoins = 12;
			break;
		case 3:
			startCoins = 11;
			break;
		case 4:
			startCoins = 9;
			break;
	}
	
	for(int i = 0; i < nbPlayers; i++){
		cout << "enter player " << i << " name: ";
		string playerName;
		cin >> playerName;
		players.push_back(new Player(startCoins, playerName));
	}
	
	//add neutral player if there are only two players
	if (nbPlayers == 2){
		cout << "+++ A neutral player is participating in the game!" << endl;
		players.push_back(new Player(0, "neutral"));
	}
	
	return players;
}

void GameStart::setPlayers(vector<Player*> playerList){
	//	int nbPlayers;
	nbPlayers = playerList.size();	
	int startCoins;
	switch(nbPlayers){
		case 2:
			startCoins = 12;
			break;
		case 3:
			startCoins = 11;
			break;
		case 4:
			startCoins = 9;
			break;
	}
	//assign the list of players to the class variable
	cout << "-------------------------------------------------" << endl;
	for (Player* p: playerList){
		cout << "+++ Player " << p->getName() << " is participating in the game!" << endl;
		p->setCoin(startCoins);
	}
	
	//add neutral player if there are only two players
	if (nbPlayers == 2){
		cout << "+++ A neutral player is participating in the game!" << endl;
		players.push_back(new Player(0, "neutral"));
	}
	
	cout << "-------------------------------------------------\n" << endl;
	players = playerList;
	
}

Deck* GameStart::setDeck(){
	cout << "\n +++++++++++++ setting deck +++++++++++++\n" << endl;
	deck = new Deck(nbPlayers);
	cout << "\n ++++++++++++++++++++++++++++++++++++++++\n" << endl;
	return deck;
}

int GameStart::getNbPlayers(){
	return nbPlayers;
}

//vector<Player*> GameStart::getPlayers(){
//	return players;
//}
//
//Map* GameStart::getMap(){
//	return map;
//}
//
//Deck* GameStart::getDeck(){
//	return deck;
//}
//
//Hand* GameStart::getHand(){
//	return deck->getHand();
//}
