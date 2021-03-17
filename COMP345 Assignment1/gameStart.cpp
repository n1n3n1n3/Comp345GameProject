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

void GameStart::enterNbPlayers(){
	int nbPlayers;
	
	cout << "Enter number of players (2-4): ";
	cin >> nbPlayers;
	
	//prompt the user to enter a correct amount
	while (nbPlayers < 2 || nbPlayers > 4){
		cout << "enter a number of players between 2 and 4" << endl;
		cin >> nbPlayers;
	}
	
	for(int i = 0; i < nbPlayers; i++){
		players.push_back(new Player());
	}
	
}