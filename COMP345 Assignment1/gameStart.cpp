#include "gameStart.h"
#include <dirent.h>
#include <sys/types.h>
#include <filesystem>
namespace fs = std::filesystem;

//default constructor
GameStart::GameStart(){
	this->path = "";
	this->mapFiles = vector<string>();
	loadMapFilePaths();
	
}

void GameStart::selectMap(){
	cout << "+++		Available Maps		+++" << endl;
	for (int i = 0; i < mapFiles.size(); i++){
		cout << "(" << i << ") " << this->mapFiles.at(i).substr(0, this->mapFiles.at(i).size() - 4) << endl;
	}
	int entry;
	cout << "choose map file: ";
	cin >> entry;
	
	//mildly manage bad entries
	while(entry < 0 || entry > mapFiles.size()){
		cout << "please enter valid number within options" << endl;
		cin >> entry;
	}
	
	this->path = "./maps/" + mapFiles.at(entry);
	//load the map fromt the path
	cout << "...loading file from path" << endl;
	//load the map from file with the map loader
	this->mapLoader = new MapLoader(this->path);
	//use the pointer constructor to make game map
	this->map = mapLoader->getMap();
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
			this->mapFiles.push_back(temp);
		}
	}
	closedir(dir);
}

void GameStart::setPlayers(){
//	int nbPlayers;
	
	cout << "Enter number of players (2-4): ";
	cin >> this->nbPlayers;
	
	//prompt the user to enter a correct amount
	while (this->nbPlayers < 2 || this->nbPlayers > 4){
		cout << "enter a number of players between 2 and 4" << endl;
		cin >> this->nbPlayers;
	}
	
	int startCoins;
	switch(this->nbPlayers){
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
		
	//generate a deck
}

void GameStart::setPlayers(vector<Player*> playerList){
	//	int nbPlayers;
	this->nbPlayers = playerList.size();	
	int startCoins;
	switch(this->nbPlayers){
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
	for (Player* p: playerList){
		p->setCoin(startCoins);
	}
	this->players = playerList;
}

void GameStart::setDeck(){
	cout << "setting deck" << endl;
	this->deck = new Deck(this->nbPlayers);
}

vector<Player*> GameStart::getPlayers(){
	return this->players;
}

Map* GameStart::getMap(){
	return this->map;
}

Deck* GameStart::getDeck(){
	return this->deck;
}

Hand* GameStart::getHand(){
	return this->deck->getHand();
}
