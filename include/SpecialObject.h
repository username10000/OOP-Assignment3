#ifndef SPECIALOBJECT_H
#define SPECIALOBJECT_H

// Dependecies
#include <CommonObject.h>

// Special Object
class SpecialObject : public CommonObject {
	private:
		int type;
		bool active;
	public:
		SpecialObject(sf::Texture *texture, sf::Color col, float sA, float rA, float r);
		void setType(int t);
		int getType();
		void setActive(bool a);
		bool getActive();
};

#endif