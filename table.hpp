#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <string>

//using namespace std;


struct Player {
	int position;
	int chipcount;
	std::string name;
};


class Table {
public:
	std::vector<Player> active_players;
	std::string id;
	int current_dealer;
	int blinds;
	bool action_request;
};


#endif