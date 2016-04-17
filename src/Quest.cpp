#include <Quest.h>

Quest::Quest(int _type, int _item, int _destination) {
	type = _type;
	item = _item;
	destination = _destination;

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