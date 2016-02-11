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



	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}