#include "map.h"
#include <algorithm>



/* Begin Region*/

//Empty constructor
Region::Region() {
	this->id = 0;
	this->name = "";
	this->continentId = 0;
	this->continent = "";
	this->owner = "";
	this->nbArmies = 0;
}


//Region default destructor
Region::~Region(){
	
}

//copy Constructor
Region::Region(const Region& region){
	this->id = region.id;
	this->name = region.name;
	this->nbArmies = region.nbArmies;
	this->owner = region.owner;
}

//parameter constructor
Region::Region(int id, string name, string continent, int continentId){
	this->id = id;
	this->name = name;
	this->continent = continent;
	this->continentId = continentId;
	this->owner = "";
	this->nbArmies = 0;
}

//streaming friend
std::ostream& operator<<(std::ostream &strm, const Region &r) {
	return strm << "\n--------------------\nRegion #" << r.id << " " << r.name << " of " << r.continent << "\nbelongs to: " << r.owner << " " << r.continent << "\nnb of armies: " << r.nbArmies << "\n--------------------\n";
}

//setters and getters
void Region::setName(string name){
	this->name = name;
}
string Region::getName(){
	return this->name;
}

void Region::setOwner(string owner){
	this->owner = owner;
}

string Region::getOwner(){
	return this->owner;
}

void Region::addArmies(int nb){
	this->nbArmies += nb;
}

void Region::setArmies(int nb){
	this->nbArmies = nb;
}

void Region::removeArmies(int nb){
	if(this->nbArmies - nb < 0){
		this->nbArmies = 0;
	}
	else {
		this->nbArmies = this->nbArmies - nb;
	}
}

int Region::getNbArmies(){
	return this->nbArmies;
}

int Region::getId(){
	return this->id;
}

void Region::setContinent(string continent){
	this->continent = continent;
}

string Region::getContinent(){
	return this->continent;
}

int Region::getContinentId(){
	return this->continentId;
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
void Continent::addRegion(Region& r){
	this->regions.push_back(new Region(r));
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
	cout << "+++ loading map from file +++" << endl;
	
	this->loadContinents(listContinents);
	this->loadRegions(listRegions);
	this->loadBorders(listBorders);
}


std::ostream& operator<<(std::ostream &strm, const Map &m) {
	return strm << "\n--------------------\nMap ::" << m.name << endl;
//	return strm << "\n--------------------\nMap ::" << m.getName() << "\nhas " << m.getNbContinents() << " continents\nhas " << m.getNbRegions() << " regions\n has" << m.getNbBorders() << " borders\n--------------------\n";
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


string Map::getName(){
	return this->name;
}
vector<Continent*> Map::getContinents(){
	return this->continents;
}
vector<vector<int>> Map::getBorders(){
	return this->borders;
}

Continent* Map::addContinent(int id, string name){
	this->continents.push_back(new Continent(id, name));
	return this->continents.back();
}

void Map::addContinent(Continent& c){
	this->continents.push_back(new Continent(c));
} 

int Map::getNbContinents(){
	return this->continents.size();
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
		if (c1->hasRegion(border.at(0)) && !c1->hasRegion(border.at(1))){
			//find the continent that contains the second region and add to both the respective connected continent
			for(Continent* c2: this->continents){
				if(c2->hasRegion(border.at(1))){
					c1->addConnectedContinent(border.at(1));
					c2->addConnectedContinent(border.at(0));
				}
			}
		}
	}
}

int Map::getNbRegions(){
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

bool Map::areAdjacent(Region* r1, Region* r2){
	int id1 = r1->getId();
	int id2 = r2->getId();

	//search amoungst the borders if a border contains both elements
	for(vector<int> b: this->borders){
		if (std::find(b.begin(), b.end(), id1) != b.end() && std::find(b.begin(), b.end(), id2) != b.end()){
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



//
//
bool Map::validate() {
	cout << "Validating Map...";
	
//1 verify that the map is a connected subgraph
//1.1 Verify that there is at least one continent in the map
	if (this->continents.size() < 1){
		cout << "Map has no regions" << endl;
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
	
//2 verify continents are connected subgraph:: each continent has at least one connection
	for (Continent* c : this->continents){
		if(c->getNbConnectedContinents() < 1){
			cout << c->getName() << endl;
			cout << "continent has no connections" << endl;
			return false;
		}
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
	cout << "map valid!" << endl;
	return true;	
}

//function to print all continent, regions and borders in a map
void Map::printMap(){
	cout << "---------------------------" << endl;
	cout << this->name << endl;
	cout << "---------------------------" << endl;
	for(Continent* c: continents){
		cout << "[" << c->getName() << "]" << endl;
		for(Region* r: c->getRegions()){
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