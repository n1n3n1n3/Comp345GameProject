#include <iostream>
#include <string>
#include "Bid.h"
#include <vector>

using namespace std;
int main(int argc, char *argv[]) {
	
	//declare bidders
	Bid* b1 = new Bid("John Jacob", 7);
	Bid* b2 = new Bid("Bam Ham", 7);
	Bid* b3 = new Bid("Felicia Frostberry", 7);
	Bid* b4 = new Bid("Xeno Xenegrade", 7);
	
//	Bid::makeBids();
	Bid::compareBids();
}