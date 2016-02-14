#include <Game.h>

Game::Game() {
	// Window Settings
	settings.antialiasingLevel = 2;

	// Get the Screen Resolution
	screen = sf::VideoMode::getDesktopMode();

	// Open a new Window
	window.create(screen, "SFML Window", sf::Style::Fullscreen, settings);

	// Open Font
	font.loadFromFile("OpenSans-Regular.ttf");

	stop = 0;

	// Set View Position
	view.x = 500;
	view.y = 0;

	// Create the Astronomical Objects
	astro.push_back(std::unique_ptr<AstroObject>(new Sun(0, 0, 500, sf::Color(255, 255, 0))));
	astro.push_back(std::unique_ptr<AstroObject>(new Planet(-1000, 0, 50, sf::Color(0, 0, 255))));
}

Game::~Game() {
	window.close();
}

int Game::getStop() {
	return stop;
}

void Game::events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			// Close the Window
			window.close();
			break;
		case sf::Event::KeyPressed:
			// Close the Window if Escape is pressed
			if (event.key.code == sf::Keyboard::Escape)
				stop = 1;
				//window.close();
			// Set the pressed key
			keys[event.key.code] = 1;
			break;
		case sf::Event::KeyReleased:
			// Unset the released key
			keys[event.key.code] = 0;
			break;
		case sf::Event::MouseButtonPressed:
			// Change View
			view.x += (int)(event.mouseButton.x - screen.width / 2);
			view.y += (int)(event.mouseButton.y - screen.height / 2);
			break;
		default:
			break;
		}
	}
}

void Game::update() {
	// Check Events
	events();
}

void Game::render() {
	// Clear the Window
	window.clear(sf::Color::Black);


	/* --------------- Draw --------------- */

	for (int i = 0; i < astro.size(); i++) {
		astro[i] -> render(window, view, screen);
	}

	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}