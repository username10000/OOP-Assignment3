#include <Quest.h>

Quest::Quest(int _type, int _item, int _noItems, int _destination, int _reward) {
	type = _type;
	item = _item;
	noItems = _noItems;
	destination = _destination;
	reward = _reward;

	switch (type) {
		case 0 :
			// Cargo
			break;
		default:
			break;
	}
}

int Quest::getType() {
	return type;
}

int Quest::getItem() {
	return item;
}

int Quest::getDestination() {
	return destination;
}

int Quest::getReward() {
	return reward;
}

int Quest::getNoItems() {
	return noItems;
}

void Quest::setType(int type) {
	this->type = type;
}

void Quest::setItem(int item) {
	this->item = item;
}

void Quest::setDestination(int destination) {
	this->destination = destination;
}

void Quest::setReward(int reward) {
	this->reward = reward;
}

void Quest::setNoItems(int noItems) {
	this->noItems = noItems;
}