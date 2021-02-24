#include <iostream>
#include "mapLoader.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
//default constructor
MapLoader::MapLoader()
{
	this->path = "";
	//loading variables
	temp = "";
	index = 0;
	position = 0;
}
//copy constructor
MapLoader::MapLoader(const MapLoader& map)
{
	this->path = map.path;
	this->listContinents = map.listContinents;
	this->listRegions = map.listRegions;
	this->listBorders = map.listBorders;
}
//destructor
MapLoader::~MapLoader(){
	
}

//parameter constructor
MapLoader::MapLoader(string path)
{
	//get the file path
	this->path = path;
	
	//read & load the file
	ifstream input(path);
	
	while (!input.eof()){
		
		temp = "";
		index = 0;
		position = 0;
		
		getline(input, temp);
		cout << temp << endl;
		
//		if entering the continent section
		if (temp.find("[Continents]") != -1){
			cout << "+++ getting continents +++" << endl;
			position = 0;
			//while we are still in the continents subsection
			while(temp.find("[Regions]") == -1 && temp.find("[Borders]") == -1 && temp.length() != 0){
				//add a continent to the list
				if (input.eof()){
					break;
				}
				getline(input, temp);
				//if the line is null, dont add a continent
				if (temp == "") {
					break;
				}
				listContinents.push_back(vector<string>());
				loadContinent(temp, position);
				printContinent(position);
				position++;
			}
			cout << "+++ end of continents +++" << endl;
		}
		
		position = 0;
		
		if (temp.find("[Regions]") != -1){
				cout << "+++ getting regions +++" << endl;
				position = 0;
				//while we are still in the continents subsection
				while(temp.find("[Continents]") == -1 || temp.find("[Borders]") == -1 || temp.length() != 0){
					//add a continent to the list
					if (input.eof()){
						break;
					}
					getline(input, temp);
					//if the line is null, dont add a continent
					if (temp == "") {
						break;
					}
					listRegions.push_back(vector<string>());
					loadRegion(temp, position);
					printRegion(position);
					position++;
				}
				cout << "+++ end of regions +++" << endl;
		}
		
		if (temp.find("[Borders]") != -1){
			cout << "+++ getting borders +++" << endl;
			position = 0;
			
			//while we are still in the continents subsection
			while(temp.find("[Continents]") == -1 && temp.find("[Regions]") == -1 && temp.length() != 0){
				//add a continent to the list
				if (input.eof()){
					break;
				}
				getline(input, temp);
				//if the line is null, dont add a continent
				if (temp == "") {
					break;
				}
				//make space for new border
				listBorders.push_back(vector<string>());
				loadBorder(temp, position);
				printBorder(position);
				position++;
			}
			cout << "+++ end of borders +++" << endl;
		}
	}
//	printContinents();
//	printRegions();
//	printBorders();
//	cout << listContinents.size() << endl;
	
	input.close();
}	

string MapLoader::getPath(){
	return this->path;
}

void MapLoader::setPath(string path){
	this->path = path;
}

vector<vector<string>> MapLoader::getListContinents()
{
	return this->listContinents;
}

vector<vector<string>> MapLoader::getListRegions()
{
	return this->listRegions;
}

vector<vector<string>> MapLoader::getListBorders()
{
	return this->listBorders;
}


//function to print file for tests
void MapLoader::printFile(){
	ifstream input(this->path);
	
	while (!input.eof()){
		string temp;
		getline(input, temp);
		cout << temp << endl;
	}
}

void MapLoader::printContinents(){
	cout << listContinents.size() << endl;
	for(vector<string> c: this->listContinents){
		for(int i = 0; i < c.size(); i++){
			cout << c.at(i) << " " ;
		}
		cout << "" << endl;
	}
}

void MapLoader::printContinent(int position){
	cout << "Loaded Continent #" << position << " :: " << listContinents[position][0] << " " << listContinents[position][1] << " " << listContinents[position][2] << endl;
}

void MapLoader::printRegions(){
	for(vector<string> r: this->listRegions){
		for(int i = 0; i < r.size(); i++){
			cout << r.at(i) << " " ;
		}
		cout << "" << endl;
	}
}


void MapLoader::printBorder(int position){
	cout << "Loaded Border :: ";
	for (int i = 0; i < this->listBorders[position].size(); i++){
		cout << " " << this->listBorders[position][i] << " "; 
	}
	cout << "\n"; 
}

void MapLoader::printBorders(){
	for(vector<string> b: this->listBorders){
		for(int i = 0; i < b.size(); i++){
			cout << b.at(i) << " " ;
		}
		cout << "" << endl;
	}
}

void MapLoader::loadContinent(string temp, int position){
	//	get index the line is not empty
	int index = 0;
	//get continent id
	index = temp.find(" ");
	string id = temp.substr(0,index);
	//	cout << "id:: "<< id << endl;
	temp.erase(0, index+1);
	listContinents[position].push_back(id);
	//	get continent name if present
	if (index == -1){ 
		return; 
	} 
	index = temp.find(" ");
	string name = temp.substr(0, index);
	//	cout << "name:: " << name << endl;
	temp.erase(0, index+1);
	listContinents[position].push_back(name);
	
	//	get number of regions if present
	if (index == -1){ 
		return; 
	}
	string nbRegions = temp.substr(0,index);
	temp.erase(0, index++);
	listContinents[position].push_back(nbRegions);
}

void MapLoader::loadRegion(string temp, int position){
	//	get index the line is not empty
	//	get index the line is not empty
	int index = 0;
	//get continent id
	index = temp.find(" ");
	string id = temp.substr(0,index);
	//	cout << "id:: "<< id << endl;
	temp.erase(0, index+1);
	listRegions[position].push_back(id);
	//	get continent name if present
	if (index == -1){ 
		return; 
	} 
	index = temp.find(" ");
	string name = temp.substr(0, index);
	//	cout << "name:: " << name << endl;
	temp.erase(0, index+1);
	listRegions[position].push_back(name);
	
//	//	get number of regions if present
//	if (index == -1){ 
//		return; 
//	}
	string continent = temp;
	temp.erase(0, index++);
	listRegions[position].push_back(continent);
}

void MapLoader::loadBorder(string temp, int position){
	//	as long as there is still a value in temp
	int index = temp.find(" ");
	string b = "";
	while(index != -1){
		b = temp.substr(0, index);
		//		cout << b << endl;
		temp.erase(0, index+1);
		index = temp.find(" ");
		listBorders[position].push_back(b);
	}
	//	b = temp.substr(0, index);
	//	cout << b << endl;
	temp.erase(0, index+1);
	index = temp.find(" ");
	b = temp.substr(0, index);
	listBorders[position].push_back(b);
}

void MapLoader::printRegion(int position){
	cout << "Loaded Region #" << position << " :: " << listRegions[position][0] << " " << listRegions[position][1] << " " << listRegions[position][2] << endl;
}