#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "map.h"
#include "PlayerStrategies.h"
//#include "Cards.h"

using namespace std;

int Player::nextID = 0;
//Constructor sets starting coins, consistent # of army and city tokens
//default constructor
Player::Player(){
	this->army = 0;
	this->city = 0;
	this->coin = 0;
	this->elixir = 0;
	this->id = ++nextID;
	this->bid = new Bid();
}

Player::Player(string name){
	this->army = 18;
	this->city = 3;
	this->elixir = 0;
	this->id = ++nextID;
	this->name = name;
	this->bid = new Bid(name);
}

Player::Player(int c, string name){
	this->army = 18;
	this->city = 3;
	this->coin = c;
	this->elixir = 0;
	this->id = ++nextID;
	this->name = name;
	this->bid = new Bid(name);
}

Player::Player(int c) {
	this->army = 18;
	this->city = 3;
	this->coin = c;
	this->elixir = 0;
	this->bid = new Bid();
	cout << "\nNew Player created, parameter of coins passed. Uninitialized void pointers for Territory, cardHand, and Bidding objects yet to be initialized."; 
	this->id = ++nextID;
}

//Copy constructor
Player::Player(const Player &p) {
	this->army = p.army;
	this->city = p.city;
	this->coin = p.coin;
	this->name = p.name;
	this->elixir = p.elixir;
	this->id = p.id;
	this->bid = new Bid(*p.bid);
	cout << "\nCopy Constructor used.";
}

//Assignment operator
Player& Player::operator = (const Player &p) {
//	cout << "\nAssignment operator used.";
	return *this;
}

//Output
std::ostream& operator<<(std::ostream &strm, const Player &p) {
	return strm << p.name << " has...\n" << p.coin << " coins.\n" << p.city <<" cities.\n" << p.army << " armies.";
}


void Player::setArmy(int a){
	this->army = a;
}

void Player::setCity(int c){
	this->city = c;
}

int Player::getArmy(){
	return this->army;
}

int Player::getCity(){
	return this->city;
}


void Player::setName(std::string name){
	this->name = name;
}

void Player::addCoin(int c) {
	this->coin += c;
}

void Player::addElixir(int e) {
	this->elixir += e;
}

void Player::setCoin(int c){
	this->coin = c;
}

int Player::getCoins(){
	return this->coin;
}

void Player::setOwned(int o) {
	this->regionsOwned = o;
}

int Player::getOwned() {
	return this->regionsOwned;
}

std::string Player::getName(){
	return this->name;
}


int Player::getId(){
	return this->id;
}

int Player::getElixir() {
	return this->elixir;
}


vector<Card*> Player::getPlayerCards() {
	return this->playerCards;
}


Bid* Player::getBid(){
	return this->bid;
}

int Player::checkPlacementBonus() {
	int ret = 0;
	for (Card* c : playerCards) {
		if (c->getGood() == 1)
			ret++;
	}
	return ret;
}

int Player::checkMovementBonus() {
	int ret = 0;
	for (Card* c : playerCards) {
		if (c->getGood() == 2)
			ret++;
	}
	return ret;
}

int Player::checkFlying() {
	int ret = 0;
	for (Card* c : playerCards) {
		if (c->getGood() == 3)
			ret++;
	}
	if ((3 - ret) >= 1)
		return (3-ret);
	else
		return 1;
}

//STRATEGY TIME

Card* Player::selectCard(Map* m, Deck* d) {
	return this->strat->chooseCard(this, m, d);
}





//Main action functions
void Player::payCoin(int amount) {

	int res = coin - amount;
	if (res < 0) {
		cout << "\n***************************************\n" << this->getName() << " has insufficient funds with only " << this->coin << " coins.\n***************************************" << endl;
	}
	else {
		this->setCoin(res);
		cout << "\n***************************************\n" << this->name << " paid " << amount << " and now has " << this->getCoins() << " coins\n***************************************" << endl;
	}
}

bool Player::checkPlacementValidity(Map* m, Region *r) {
	if ((r->checkStartingRegion(m))||(r->checkCity(this)))
		return true;
	else
		return false;
	
}

void Player::PlaceNewArmies(int a, Map* m) {
	while (a > 0) {
		bool valid = false;
		while (!valid) {
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID that you would like to place on ->";
			cin >> choice;
			Region* r = m->getRegionById(choice);
			if (checkPlacementValidity(m, r)) {
				valid = true;
				bool val = false;
				while (!val) {
					int arms = 0;
					cout << "\n***************************************\nEnter # of armies to place (max " << a << ") ->";
					cin >> arms;
					if (arms > a)
						cout << "\n***************************************\nInvalid, try again...\n";
					else {
						val = true;
						r->addArmies(this, arms);
						a -= arms;
					}
				}
			}
			else 
				cout << "\n***************************************\nInvalid Region, must be the Starting Region or a region where you own a city...\n";
		}
	}
	cout << "\n***************************************\nDone placing Armies!";
}



void Player::MoveArmies(int a, Map* m) {
	while (a > 0) {
		bool valid = false;
		Region* starting;
		Region* moving;
		cout << "\n***************************************\nYou have " << a << " movement points...\n";
		while (!valid) {
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID that you would like to move armies from (0 to skip) ->";
			cin >> choice;
			if (choice == 0) {
				return;
			}
			starting = m->getRegionById(choice);
			vector<pair<Player*, int>> players = starting->getPlayerArmies();
			for (int i = 0; i < players.size(); i++){
				if (players.at(i).first == this) {
					if (players.at(i).second > 0) {
						valid = true;
					}
					else {
						cout << "\n***************************************\nInvalid Region, no armies to move...\n";
					}
				}
			}
		}
		
		valid = false;
		while (!valid) {
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID that you would like to move to (consult the borders displayed above) ->";
			cin >> choice;
			moving = m->getRegionById(choice);
			if (m->areAdjacent(starting, moving)) {
				int moves = a;
				if ((m->getRegionContinent(starting)) != (m->getRegionContinent(moving))) {
					if (a < this->checkFlying()) {
						cout << "\n***************************************\nRegions are adjacent, but you need at least " << this->checkFlying() << " movements to move over water...\n";
					}
					//MOVE OVER WATER
					else {
						a -= MoveOverWater(moves, starting, moving);
						valid = true;
					}
				}
				//MOVE OVER LAND
				else {
					a -= MoveOverLand(moves, starting, moving);
					valid = true;
				}
			}
			else 
				cout << "\n***************************************\nInvalid Region, must be adjacent to " << starting->getName() << "...\n";
		}
		
	}
}
int Player::MoveOverLand(int a, Region* start, Region* move) {
	bool valid = false;
	int choice = 0;
	int maxMoves = a;
	
	if ((start->getNbArmiesByName(this->getName())) < maxMoves)
		maxMoves = start->getNbArmiesByName(this->getName());
	
	while (!valid) {
		
		cout << "\n***************************************\nEnter the number of armies you'd like to move (max " << maxMoves << ") ->";
		cin >> choice;
		if ((choice > maxMoves)||(choice < 1))
			cout << "\n***************************************\nInvalid, try again...\n";
		else {
			start->removeArmies(this, choice);
			move->addArmies(this, choice);
			valid = true;
		}
	}
	return choice;
	
}

int Player::MoveOverWater(int a, Region* start, Region* move) {
	bool valid = false;
	int choice = 0;
	int maxMoves = a/(this->checkFlying());
	
	if ((start->getNbArmiesByName(this->getName())) < maxMoves)
		maxMoves = start->getNbArmiesByName(this->getName());
	
	while (!valid) {
		
		cout << "\n***************************************\nEnter the number of armies you'd like to move (max " << maxMoves << ") ->";
		cin >> choice;
		if ((choice > maxMoves)||(choice < 1))
			cout << "\n***************************************\nInvalid, try again...\n";
		else {
			start->removeArmies(this, choice);
			move->addArmies(this, choice);
			choice *= this->checkFlying();
			valid = true;
		}
	}
	return choice;
}

void Player::BuildCity(Map* m) {
	bool valid = false;
	while (!valid) {
		int choice = 0;
		cout << "\n***************************************\nEnter the Region ID that you would like to build a city on ->";
		cin >> choice;
		Region* r = m->getRegionById(choice);
		if (r->addCity(this))
			valid = true;
	}
}

void Player::DestroyArmy(Map* m) {
	bool valid = false;
	Region* r;
	vector<pair<Player*, int>> players;
	while (true) {
		while (!valid) {
			bool hasOp = false;
			bool hasSelf = false;
			int choice = 0;
			cout << "\n***************************************\nEnter the Region ID where you would like to destroy an opponent's army (or 0 to skip) ->";
			cin >> choice;
			if (choice == 0)
				return;
			r = m->getRegionById(choice);
			players = r->getPlayerArmies();
			for (int i = 0; i < players.size(); i++) {
				if (players.at(i).first != this) {
					if (players.at(i).second > 0) {
						hasOp = true;
					}
				}
				else if (players.at(i).first == this) {
					if (players.at(i).second > 0)
						hasSelf = true;
				}
			}
			if ((hasOp)&&(hasSelf))
				valid = true;
			else 
				cout << "\n***************************************\nThis Region either has no opponent armies on it or you don't have an army on it...\n";
		}
		valid = false;
		
		while (!valid) {
			int choice = 0;
			cout << *r << "\n***************************************\nEnter the # of the Player whose army you want to destroy (top = 1, 0 to go back) ->";
			cin >> choice;
			if (choice == 0)
				break;
			choice -= 1;
			
			if ((choice < 0)||(choice >= players.size()))
				cout << "\n***************************************\nInvalid...\n";
			else if (players.at(choice).first == this)
				cout << "\n***************************************\nYou can't destroy yourself, silly!!\n";
			else if (players.at(choice).first == m->getImmunePlayer())
				cout << "\n***************************************\n" << players.at(choice).first->getName() << " has immunity! You can't destroy their armies...";
			else {
				cout << "\n***************************************\nDestroying one army of " << players.at(choice).first->getName() << " from Region " << r->getName() << ".\n";
				r->removeArmies(players.at(choice).first, 1);
				return;
			}
		}
	
	}
}

void Player::AndOrAction() {
	
}

void Player::makeBid(int bid){
	if (bid > this->coin){
		cout << "\n***************************************\ncannot make bid greater than the number of coins" << endl;
	}
	else {
		this->bid->betCoins(bid);
	}
}

bool Player::exchange(Deck* d, Card* c){
	if (this->getCoins() < c->getCost()){
		cout << "\n***************************************\nplayer has insufficient funds: " << this->getName() << " only has " << this->getCoins() << " coins, card costs " << c->getCost() << " coins" << endl;
		return false;
	}
	else {
		cout << "\n***************************************\n" << this->getName() << " is purchasing card [" << c->getName() << "] for " << c->getCost() << " coins." << endl;
		// pay the cost
		this->payCoin(c->getCost());
		// add card to the players list
		playerCards.push_back(c);
		int good = c->getGood();
		
		//IMMEDIATELY ADD COIN OR ELIXIR
		if (good == 4152) {
			addCoin(2);
			addElixir(1);
		}
		else {
			int len = 0;
			int first = 0;
			int second = 0;
			for (int i = good; i > 0; i = i/10) {
				len++;
			}
			if (len == 2) {
				first = good/10;
				second = good%10;
				if (first == 4) {
					cout << "\n***************************************\nAdding " << second << " Elixir...";
					addElixir(second);
				}
				else if (first == 5) {
					cout << "\n***************************************\nAdding " << second << " Coins...";
					addCoin(second);
				}
				else if ((first == 6)||(first == 7)||(first == 8))
					scoringCards.push_back({c, good});
			}
		}
		
		d->slideCardInHand(c);
		return true;
	}
}

Player* getPlayerById(int id, vector<Player*> playerList){
	cout << "getting player by ID" << endl;
	for(Player* p: playerList){
			if(p->getId() == id){
				return p;
			}
		}
	//return empty player
	cout << "no player with id " << id << endl;
	return new Player();
}

Player* getPlayerByName(string name, vector<Player*> playerList){
	cout << "getting player by Name" << endl;
	for(Player* p: playerList){
		if((p->getName()).compare(name) == 0){
			return p;
		}
	}
	cout << "no player with name " << name << endl;
	//return empty player
	return new Player();
}

		
		
int Player::cardScore(Card *c, int q) {
	cout << "\n***************************************\n***Checking...***\n" << *c << endl;
	int score = 0;
	int len = 0;
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;
	char desiredType;
	int desiredSet;
	for (int i = q; i > 0; i = i/10) {
		len++;
	}
	if (len == 4) {
		first = q/1000;
		second = (q/100)%10;
		third = (q/10)%10;
		fourth = q%10;
	}
	else if (len == 2) {
		first = q/10;
		second = q%10;
	}
	switch (first) {
		case 6:
			cout << "\n^^^This card gives you 1 VP per " << c->getTypeString(second) << "...\n";
			desiredType = c->getType(second);
			for (int i = 0; i < playerCards.size(); i++) {
				if (playerCards.at(i)->getType() == desiredType) {
					cout << "\n+1 VP for Card " << playerCards.at(i)->getName() << "...\n";
					score ++;
				}
			}
			break;
		case 7:
			if (second == 3) {
				desiredType = 'm';
				desiredSet = 2;
			}
			else if (second == 4) {
				desiredType = 'o';
				desiredSet = 3;
			}
			
			for (int i = 0; i < playerCards.size(); i++) {
				if (playerCards.at(i)->getType() == desiredType)
					desiredSet--;
			}
			
			if (desiredSet == 0) {
				cout << "\n+" << second << " VPs for a set of " << third << " " << c->getTypeString(fourth) << "...\n";
				score = second;
			}
			else {
				cout << "\nDesired set not achieved...\n";
			}
			break;
		case 8:
			if (second == 1) {
				score = this->coin/3;
				cout << "\n+" << score << " VPs per 3 Coins...\n";
			}
			else if (second == 2) {
				for (Card* c : playerCards) {
					if (c->getGood() == 3)
						score++;
				}
				cout << "\n+" << score << " for all Flyings...\n";
			}
			break;
		default:
			cout << "Unexpected invalid input!";
			
	}


	
	return score;
}		
		
		
int Player::computeScore(Map* m) {
	int score = 0;
	
	cout << "\n\nCOMPUTING SCORE FOR " << this->getName() <<"...\n";
	
	//REGION SCORE
	vector<Continent*> continents = m->getContinents();
	for (int i = 0; i < continents.size(); i++) {
		vector<Region*> regions = continents.at(i)->getRegions();
		for (int j = 0; j < regions.size(); j++) {
			if ((regions.at(j)->getOwner()) == this->name) {
				cout << "\n+1 VP for Region " << regions.at(j)->getName() << "...\n";
				score++;
			}
		}
	}
	cout << "Region score: " << score;
	
	
	//CONTINENT SCORE
	int cScore = 0;
	for (int i = 0; i < continents.size(); i++) {
		if ((continents.at(i)->getOwner(m)) == this->name) {
			cout << "\n+1 VP for Continent " << continents.at(i)->getName() << "...\n";
			cScore+=1;
		}
	}
	
	cout << "Continent score: " << cScore;
	score+=cScore;
	
	//CARDS SCORE
	cScore = 0;
	for (int i = 0; i < scoringCards.size(); i++) {
		int thisCard = cardScore(scoringCards.at(i).first, scoringCards.at(i).second);
		cScore += thisCard;
	}
	cout <<"Total card score: " << cScore;
	score += cScore;
	
	//ELIXIR SCORE
	vector <Player*> p = m->getPlayers();
	bool most = true;
	bool tie = false;
	for (int i = 0; i < p.size(); i++) {
		if (p.at(i) != this) {
			if (p.at(i)->getElixir() > this->elixir) {
				most = false;
				tie = false;
				break;
			}
			else if (p.at(i)->getElixir() == this->elixir) {
				most = false;
				tie = true;
			}
		}
	}
	if (most) {
		cout << "\n+2 VPs for having the most Elixir...\n";
		score += 2;
	}
	
	else if (tie) {
		cout << "\n+1 VP for tying for most Elixir...\n";
		score += 1;
	}
	
	else {
		cout << "\nNo VP bonus for Elixir...\n";
	}
	
	cout << "\nTotal score: " << score << endl;
	
	return score;
}