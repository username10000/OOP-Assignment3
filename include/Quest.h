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
		int reward;
		int noItems;
	public:
		Quest(int _type, int _item, int _noItems, int _destination, int _reward);
		int getType();
		int getItem();
		int getDestination();
		int getReward();
		int getNoItems();
		void setType(int type);
		void setItem(int item);
		void setDestination(int destination);
		void setReward(int reward);
		void setNoItems(int noItems);
};

#endif