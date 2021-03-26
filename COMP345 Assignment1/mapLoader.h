#pragma once
#include <vector>
#include <iostream>
#include "map.h"
using namespace std;

class MapLoader
{
	private:
		string path;
		vector<vector<string>> listContinents;
		vector<vector<string>> listRegions;
		vector<vector<string>> listBorders;
		Map* map;
		
		friend std::ostream& operator<<(std::ostream&, const MapLoader&);
		
	public:
		//loading variables
		string temp;
		int index;
		int position;
		//constructors
		MapLoader();
		MapLoader(string path);
		MapLoader(const MapLoader& map);
		~MapLoader();
		
		//setters and getters
		string getPath();
		void setPath(string path);
		vector<vector<string>> getListContinents();
		vector<vector<string>> getListRegions();
		vector<vector<string>> getListBorders();
		Map* getMap();
		
		//main loading function for each line
		Map* loadMap();
		void loadContinent(string temp, int position);
		void loadRegion(string temp, int position);
		void loadBorder(string temp, int position);
		
//		verification print funtions
		void printContinents();
		void printContinent(int position);
		void printRegions();
		void printRegion(int position);
		void printBorders();
		void printBorder(int position);
		void printFile();

};