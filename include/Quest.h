#ifndef QUEST_H
#define QUEST_H

// Dependencies
#include <string>

// Quest
class Quest {
	private:
		int type;
		int item;
		int destination;
	public:
		Quest(int _type, int _item, int _destination);
		int getType();
		int getItem();
		int getDestination();
};

#endif