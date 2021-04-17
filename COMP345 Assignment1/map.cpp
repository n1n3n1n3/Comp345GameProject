#include "map.h"
#include <algorithm>


/* Begin Region*/

//Empty constructor
Region::Region() {
	this->id = 0;
	this->name = "";
//	this->continentId = 0;
	this->continent = "";
	this->owner = "none";
	
	//this->startingRegion = false;
	//create an empty pair list for players and number of armies
	this->playerArmies = vector<pair<Player*, int>>();
	this->playerCity = vector<pair<Player*, bool>>();
}


//Region default destructor
Region::~Region(){
	
}

//copy Constructor
Region::Region(const Region& region){
	this->id = region.id;
	this->name = region.name;
	this->owner = region.owner;
	this->playerArmies = region.playerArmies;
	this->playerCity = region.playerCity;
}

//parameter constructor
Region::Region(int id, string name, string continent, int continentId){
	this->id = id;
	this->name = name;
	this->continent = continent;
	this->continentId = continentId;
	this->owner = "none";
//	this->startingRegion = false;
	this->playerArmies = vector<pair<Player*, int>>();
	this->playerCity = vector<pair<Player*, bool>>();
}

//streaming friend
std::ostream& operator<<(std::ostream &strm, const Region &r) {
	return strm << "\n--------------------\nRegion #" << r.id << " " << r.name << "\nbelongs to: " << r.owner << "\nContinent: " << r.continent << "\n" << r.getPlayersAndArmiesString() << endl;
	
//	<< "\nnb of armies ++ \n" << r.player << "\n--------------------\n";
}

const string Region::getPlayersAndArmiesString() const{
	string temp = "\n";
	for (pair<Player*, int> p : playerArmies){
		temp += p.first->getName();
		temp += "       armies: " + to_string(p.second) + ". City? ";
		for (pair<Player*, bool> q : playerCity) {
			if (p.first == q.first) {
				if (q.second)
					temp += "YES.\n";
				else
					temp += "NO.\n";
			}
		}
	}
	
	return temp;
}


//setters and getters
void Region::setPlayers(vector<Player*> playerList){
	//assume that each player starts with 0 armies
	for(Player* p: playerList){
		playerArmies.push_back({p, 0});
		playerCity.push_back({p, false});
	}
}

void Region::setName(string name){
	this->name = name;
}
string Region::getName(){
	return this->name;
}

void Region::setOwner(Player* p){
	this->owner = p->getName();
}

string Region::getOwner(){
	return this->owner;
}


vector<pair<Player*, int>> Region::getPlayerArmies(){
	return this->playerArmies;
}

void Region::addArmies(Player* p, int nb){
	cout << p->getName() << " is adding " << nb << " armies to " << this->name << endl;
	
	for (int i = 0; i < playerArmies.size(); i++){
		if (playerArmies.at(i).first == p){
			playerArmies.at(i).second += nb;
		}
	}
	
	this->determineOwner();
}

bool Region::canDestroy(Player* p) {
	int x = 0;
	for (pair<Player*,int> o : this->getPlayerArmies()) {
		if (((o.second) > 0)&&(o.first != p))
			x++;
	}
	if (x > 0)
		return true;
	else
		return false;
}



bool Region::addCity(Player *p) {
	cout << p->getName() << " is adding a city to " << this->name << endl;
	for (int i = 0; i < playerCity.size(); i++){
		if (playerCity.at(i).first == p){
			if (playerCity.at(i).second == true) {
				cout << "\nCity is already there, choose another Region...\n";
				return false;
			}
			else {
				cout << "\nSuccess!\n";
				playerCity.at(i).second = true;
				return true;
			}
		}
	}
	cout << "\nUnexpected error.\n";
	return false;
}

bool Region::checkCity(Player *p) {
	
	for (int i = 0; i < playerCity.size(); i++){
		if (playerCity.at(i).first == p){
			if (playerCity.at(i).second == true) {
				return true;
			}
			else {
				//cout << "\nNo city for this player at this region" << endl;
				return false;
			}
		}
	}
	cout << "\nUnexpected error.\n";
	return false;
}

void Region::setArmies(Player *p, int nb){
	for (int i = 0; i < playerArmies.size(); i++){
		if (playerArmies.at(i).first == p){
			playerArmies.at(i).second = nb;
		}
	}
	this->determineOwner();
}

void Region::removeArmies(Player* p, int nb){
	//iterate through the list of players
	for (int i = 0; i < playerArmies.size(); i++){
		if(playerArmies.at(i).first == p){
			//can't have less than 0 armies
			if(playerArmies.at(i).second - nb < 0){
				playerArmies.at(i).second = 0;
			}
			else {
				playerArmies.at(i).second = playerArmies.at(i).second - nb;
				cout << "Removing " << nb << " armies from " << playerArmies.at(i).first->getName() << "..." << endl;
			}
		}
	}
	//check if the owner of the territory has changed
	this->determineOwner();
}

int Region::getNbArmiesByName(string name){
	for(pair<Player*, int> p: playerArmies){
		if((p.first->getName().compare(name)) == 0){
			return p.second;
		}
	}
	
	cout << "no such player" << endl;
	//return 0 if there is no such player
	return 0;
}


int Region::getId(){
	return this->id;
}

void Region::setContinent(string continent){
	this->continent = continent;
}

void Region::setContinentId(int id){
	this->continentId = id;
}

string Region::getContinent() const{
	return this->continent;
}

int Region::getContinentId(){
	return this->continentId;
}


void Region::determineOwner(){
	string currOwner = "";
	int currentMax = 0; 
	for(int i = 0; i < playerArmies.size(); i++){
		if (playerArmies.at(i).second > currentMax && playerArmies.at(i).second > 0) {
			currentMax = playerArmies.at(i).second;
			currOwner = playerArmies.at(i).first->getName();
		}
		
		//if two players have the same number of armies set owner to none
		if (playerArmies.at(i).second == currentMax && currOwner.compare(playerArmies.at(i).first->getName()) != 0){
			currOwner = "none";
		}
	}
	if ((this->owner).compare(currOwner) != 0){
		cout << "region " << this->name << " has gone from " << this->owner << " to " << currOwner << "." << endl;
		this->owner = currOwner;
	}
}

bool Region::checkStartingRegion(Map* m) {
	if (m->getStartingRegion() == this)
		return true;
	else
		return false;
}
/*end of region*/


/* Begin Continent*/


//default constructor
Continent::Continent(){
	this->name = "";
	this->id = 0;
	this->regions = vector<Region*>();
	this->connectedContinents = vector<int>();
}

//copy constructor
Continent::Continent(const Continent& continent){
	this->id = continent.id;
	this->name = continent.name;
	this->regions = continent.regions;
	this->connectedContinents = continent.connectedContinents;
}

//parameter constructor
Continent::Continent(int id, string name){
	this->id = id;
	this->name = name;
	//declare empty vector sets
	this->regions = vector<Region*>();
	this->connectedContinents = vector<int>();
}

//destructor
Continent::~Continent(){
}

//cout overwrite
std::ostream& operator<<(std::ostream &strm, const Continent &c) {
	return strm << "\n--------------------\nContinent # " << c.id << " " << c.name << "\nhas " << c.regions.size() << " regions\n--------------------\n";
}

//setters and getters

void Continent::setId(int id){
	this->id = id;
}
void Continent::setName(string name){
	this->name = name;
}
void Continent::setRegions(vector<Region*> regions){
	this->regions = regions;
}
void Continent::setConnectedContinents(vector<int> connectedContinents){
	this->connectedContinents = connectedContinents;
}

int Continent::getId(){
	return this->id;
}
string Continent::getName(){
	return this->name;
}
vector<Region*> Continent::getRegions(){
		return this->regions;
}

vector<int> Continent::getListOfRegionId(){
	vector<int> listOfRegionIds = vector<int>();
	for (Region* r : this->regions){
		listOfRegionIds.push_back(r->getId());
	}
	return listOfRegionIds;
}

string Continent::getOwner(Map* m) {
	string owner = "";
	int bestScore = 0;
	int compareScore = 0;
	
	vector<Player*> p = m->getPlayers();
	
	for (int i = 0; i < p.size(); i++) {
		compareScore = 0;
		for (int j = 0; j < regions.size(); j++) {
			if (p.at(i)->getName()==regions.at(j)->getOwner())
				compareScore++;
		}
		if (compareScore > bestScore) {
			bestScore = compareScore;
			owner = p.at(i)->getName();
		}
		else if (compareScore == bestScore)
			owner = "none";
	}
	return owner;
	
}

int Continent::getNbRegions(){
	return this->regions.size();
}
vector<int> Continent::getConnectedContinents(){
	return this->connectedContinents;
}
//add region from reference
Region* Continent::addRegion(int id, string name){
	this->regions.push_back(new Region(id, name, this->name, this->id));
	return this->regions.back();
}
////add region by parameter
void Continent::addRegion(Region* r){
	this->regions.push_back(r);
	r->setContinentId(this->getId());
	r->setContinent(this->getName());
}

bool Continent::hasRegion(int id){
	for(Region* r: this->regions){
		if(r->getId() == id){
			return true;
		}
	}
	return false;
}

Region* Continent::getRegionById(int id){
	if(this->hasRegion(id)){
		for(Region* r: this->regions){
			if(r->getId() == id){
				return r;
			}
		}
	}

	cout << "no such region in continent" << endl;
	return new Region();
}



//adds the id of a connected continent
void Continent::addConnectedContinent(int id){
	this->connectedContinents.push_back(id);
}

//verifies if another continent is connected
bool Continent::isConnectedToContinent(int id){
	for (int c: connectedContinents){
		if (c == id){
			return true;
		}
	}
	return false;
}

int Continent::getNbConnectedContinents(){
	return this->connectedContinents.size();
}

/* end of continent functions */


/*Begin Map*/

//default constructor
Map::Map(){
	this->name = "";
	this->continents = vector<Continent*>();
	this->borders = vector<vector <int>>();
}

Map::Map(string name){
	this->name = name;
	this->continents = vector<Continent*>();
	this->borders = vector<vector <int>>();
}
//parameter constructor
Map::Map(string name, vector<Continent*> continents, vector<vector<int>> borders){
	this->name = name;
	this->continents = continents;
	this->borders = borders;
}
//copy constructor
Map::Map(const Map& map){
	this->name = map.name;
	this->continents = map.continents;
	this->borders = map.borders;
}
//destructor
Map::~Map(){	
}

////constructor for the mapLoader
Map:: Map(vector<vector<string>> listContinents,
vector<vector<string>> listRegions,
vector<vector<string>> listBorders){
	cout << "\n+++ loading map from file +++\n" << endl;
	
	this->loadContinents(listContinents);
	cout << "\n";
	this->loadRegions(listRegions);
	cout << "\n";
	this->loadBorders(listBorders);
	cout << "\n";
}


std::ostream& operator<<(std::ostream &strm, const Map &m) {
	return strm << "\n\n-------------- Map :: " << m.getName() << "--------------\nNb of Continents:: " << m.getNbContinents() << "\nNb of regions:: " << m.getNbRegions() << "\n-----------------------------------------" << endl;
}

//setters
void Map::setName(string name){
	this->name = name;
}
void Map::setContinents(vector<Continent*> continents){
	this->continents = continents;
}
void Map::setBorders(vector<vector<int>> borders){
	this->borders = borders;
}

void Map::setStartingRegion(Region* r){
	this->startingRegion = r;
}

const string Map::getName() const{
	return this->name;
}
vector<Continent*> Map::getContinents(){
	return this->continents;
}
vector<vector<int>> Map::getBorders(){
	return this->borders;
}

Region* Map::getStartingRegion() {
	return this->startingRegion;
}

Continent* Map::addContinent(int id, string name){
	this->continents.push_back(new Continent(id, name));
	return this->continents.back();
}

void Map::addContinent(Continent& c){
	this->continents.push_back(new Continent(c));
} 

int Map::getNbContinents() const{
	return this->continents.size();
}

vector<Player*> Map::getPlayers() {
	return this->players;
}

Continent* Map::getRegionContinent(Region* r){
	
	for (Continent* c : this->continents){
		if(c->getName() == r->getContinent()){
			return c;
		}
	}
	//if you can't find the regions continent, warn the user
	cout << "cannot find regions continent" << endl;
	return new Continent();
}

Continent* Map::getContinentById(int id){
	//declare an empty continent
	Continent* continent = new Continent();
	for (Continent* c : this->continents){
		cout << id <<  " x " << c->getId() << endl;
		if(c->getId() == id){
			continent = c;
		}
	}
	//if no continent was found, let the user know
	if (continent->getName() ==""){
		cout << "no such continent" << endl;
	}
	return continent;	
}

void Map::addBorder(vector<int> border){
//	verify if the border already exists
	if (std::find(this->borders.begin(), this->borders.end(), border) != this->borders.end()){
		return;
	}
//if not present add border to the list
	else{
		this->borders.push_back(border);	
	}
//	check if this border connects two continents
// Continent connection borders only have two elements
	for (Continent* c1: this->continents){
		//if a continent has the first region but not the second
		if (c1->hasRegion(border.at(1)) && !c1->hasRegion(border.at(2))){
			//find the continent that contains the second region and add to both the respective connected continent
			for(Continent* c2: this->continents){
				if(c2->hasRegion(border.at(2))){
					c1->addConnectedContinent(border.at(2));
					c2->addConnectedContinent(border.at(1));
				}
			}
		}
	}
}

int Map::getNbRegions() const{
	int nbRegions = 0;
	for (Continent* c: this->continents){
		nbRegions += c->getNbRegions();
	}
	return nbRegions;
}

Region* Map::getRegionById(int id){
	for (Continent* c : this->continents){
		if(c->hasRegion(id)){
			for(Region* r: c->getRegions()){
				if(r->getId() == id){
					return r;
				}
			}
		}
	}
	//if no such region was found, let the user know
	cout << "no such region in Map" << endl;
	return new Region();
}

bool Map::hasRegionById(int id){
	Region* r = getRegionById(id);
	if (r->getId() == 0){
		return false;
	}
	return true;
}

bool Map::areAdjacent(Region* r1, Region* r2){
	int id1 = r1->getId();
	int id2 = r2->getId();

	//search amoungst the borders if a border contains both elements
	for(vector<int> b: this->borders){
		if (std::find(b.begin()+1, b.end(), id1) != b.end() && std::find(b.begin()+1, b.end(), id2) != b.end()){
			return true;
		}
	}
	return false;
}


void Map :: loadContinents(vector<vector<string>> listContinents){
	int tempID;
	string tempName;
	Continent * tempContinent;
	cout << "loading continents...";
	for(vector<string> c: listContinents){
		//check if the file gives the id, name and nb regions
		if(c.size() != 3){
			cout << "invalid continent data" << endl;
		}
		else{
			//check if id and nb of regions are int
			if (!isNumber(c.at(0))){
				cout << "invalid continent structure" << endl;
			}
			//get data
			else {
				tempID = stoi(c.at(0));
				tempName = c.at(1);
				tempContinent = new Continent(tempID, tempName);
			}
			this->addContinent(*tempContinent);
		}
	}
	cout << "...done" << endl;
}
//function  to load regions to the maps continents from file
void Map :: loadRegions(vector<vector<string>> listRegions){
	//verify that the vector has the right size
	cout << "loading regions...";
	int tempID;
	string tempName;
	string tempContinent;
	Region *tempRegion;
	for(vector<string> r: listRegions){
		if (r.size() != 3){
			cout << "invalid region data";
		}
		else{
			if (!isNumber(r.at(0))){
				cout << "invalid region structure" << endl;
			}
			else {
				tempID = stoi(r.at(0));
				tempName = r.at(1);
				tempContinent = r.at(2);
				
				for (Continent* c: this->continents){
					if(c->getName() == tempContinent){
						c->addRegion(tempID, tempName);
					}
				}
			}
		}
	}
	cout << "...done" << endl;
}

void Map::determineStartingRegion(){
	cout << "\n+++ determining starting region +++" << endl;
	//	find regions that have a water connection
	vector<Region*> possibleRegions;
	vector<Region*> finale;
	for(Continent* c: continents){
		for (Region* r: c->getRegions()) {
			for(Continent* b: continents){
				for (Region* q: b->getRegions()) {
					if (borderIsWater(r, q)) {
						if (find(possibleRegions.begin(), possibleRegions.end(), r) == possibleRegions.end()) {
							possibleRegions.push_back(r);
						}
						if (find(possibleRegions.begin(), possibleRegions.end(), q) == possibleRegions.end()) {
							possibleRegions.push_back(q);
						}
					}
				}
				
			}
		}
	}
	
	for (Region* r: possibleRegions) {
		for(Continent* b: continents) {
			for (Region* q: b->getRegions()) {
				if (areAdjacent(r, q)) {
					for(Continent* c: continents) {
						for (Region* s: c->getRegions()) {
							if ((s != r)&&(borderIsWater(q, s)))
								finale.push_back(r);
						}
					}
				}
			}
		}
	}
	
			
	srand(time(0));
	int select = rand() % finale.size();
	
	setStartingRegion(finale.at(select));
			
		
	
}

bool Map::connectedToOtherContinent(Region* r){
	for (vector<int> border: this->borders){
		if (border.at(1) == r->getId()){
			if (r->getContinent() != getRegionById(border.at(2))->getContinent()){
				return true;
			}
		}
		
		if(border.at(2) == r->getId()){
			if (r->getContinent() != getRegionById(border.at(1))->getContinent()){
				return true;
			}
		}
	}
	
	return false;
}

bool Map::borderIsWater(Region* r1, Region* r2){
	int id1 = r1->getId();
	int id2 = r2->getId();
	
	//search amoungst the borders if a border contains both elements
	for(vector<int> b: this->borders){
		if (std::find(b.begin()+1, b.end(), id1) != b.end() && std::find(b.begin()+1, b.end(), id2) != b.end()){
			if (b.front() == 1)
				return true;
		}
	}
	return false;
	
}

//function to load borders to map from file
void Map :: loadBorders(vector<vector<string>> listBorders){
		vector<int> tempV;
		int tempI;
		cout << "loading Borders...";
		for(vector<string> b: listBorders){
			for(int i = 0; i < b.size(); i++){
				tempI = stoi(b.at(i));
				tempV.push_back(tempI);
//				cout << tempI << " ";
			}
			addBorder(tempV);
			//reset for next border
			tempV.clear();
		}
	cout << "...done" << endl;
}
//extra function to verify a string is a number
bool Map::isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
		return false;
	
	return true;
}

bool Map::canDestroy(Player* p) {
	bool can = true;
	for (Continent* c: this->continents){
		for (Region* r: c->getRegions()){
			int x = 0;
			for (pair<Player*,int> o : r->getPlayerArmies()) {
				if (((o.second) > 0)&&(o.first != p))
					x++;
			}
			if (x > 0)
				return true;
		}
	}
	return false;
}


void Map::setImmunePlayer(Player* p) {
	this->immunePlayer = p;
}

Player* Map::getImmunePlayer() {
	return immunePlayer;
}

void Map::loadPlayers(vector<Player*> listPlayers){
	//run through each region in each territory and add the list of players
	for(Player* p: listPlayers) {
		players.push_back(p);
	}
	for (Continent* c: this->continents){
		for (Region* r: c->getRegions()){
			r->setPlayers(listPlayers);
		}
	}
}



//
//
bool Map::validate() {
	cout << "++++++++++++++++++++++++++++++++++" << endl;
	cout << "Validating Map   " << endl;
	
	
//1 verify that the map is a connected subgraph
//1.1 Verify that there is at least one continent in the map
	if (this->continents.size() < 1){
		cout << "Map has no continents" << endl;
		return false;
	}
//1.2 Verify that each continent has at least one region
	for (Continent* c : this->continents){
		if (c->getNbRegions() < 1){
			cout << *c << endl;
			cout << "continent has no regions" << endl;
			return false;
		}
	}
	cout << "." ;
//2 verify continents are connected subgraph:: each continent has at least one connection
	for (Continent* c : this->continents){
		if(c->getNbConnectedContinents() < 1){
			cout << c->getName() << " continent has no connections" << endl;
			return false;
		}
		cout << "." ;
	}
		
		
//3 verify that each region is in only one continent
//for all continents verify each region and make sure the same id is not found in another continent
	for (Continent* c1 : this->continents){
		for(Region* r: (c1->getRegions())){
			for (Continent* c2 : this->continents){
				if (c2 != c1 && c2->hasRegion(r->getId())){
					return false;
				}
			}
		}
	}
	cout << ". map valid!" << endl;
	cout << "++++++++++++++++++++++++++++++++++\n\n";
	return true;	
}

//function to print all continent, regions and borders in a map
void Map::printMap(){
	cout << "\n\n---------------------------" << endl;
	cout << "		" << this->name << endl;
	cout << "-----------------------------" << endl;
	for(Continent* c: continents){
		cout << "[" << c->getName() << "]";;
		for(Region* r: c->getRegions()){
			if (r == this->getStartingRegion())
				cout << "*******\\/\\/\\/\\/\\/ STARTING REGION BELOW \\/\\/\\/\\/\\/*******";
			cout << *r << endl;
		}
	}
	cout << "---------------------------" << endl;
	cout << "[Borders]" << endl;
	for(vector<int> b: borders){
		for(int region: b){
			cout << region << " " ;
		}
		cout << endl;
	}
	cout << "---------------------------" << endl;
}


void Map::printContinents(){
	cout << "\n+++ continents +++\n";
	for(Continent* c: continents){
		cout << "[" << c->getName() << "]";
	}
}

void Map::printRegions(){
	cout << "\n +++ regions +++\n";
	for(Continent* c: continents){
		cout << "[" << c->getName() << "]\n";;
		for(Region* r: c->getRegions()){
			if (r == this->getStartingRegion()){
				cout << "(" << r->getId() << ")" << r->getName() << " (s)"<< endl;
			}
			else {
				cout << "(" << r->getId() << ")" << r->getName() << endl;
			}
		}
		cout << "\n" << endl;
	}
}