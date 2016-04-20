#ifndef UI_H
#define UI_H

// Dependencies
#include <SFML/Graphics.hpp>

class UI {
	public:
		~UI() {};
		virtual void render(sf::RenderWindow &window) = 0;
		virtual bool getHovered() = 0;
		virtual std::string getDescription() = 0;
};

#endif
