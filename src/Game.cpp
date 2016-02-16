#include <Game.h>

Game::Game() {
	// Window Settings
	settings.antialiasingLevel = 2;

	// Get the Screen Resolution
	screen = sf::VideoMode::getDesktopMode();

	// Open a new Window
	window.create(screen, "SFML Window", sf::Style::Fullscreen, settings);

	window.setFramerateLimit(60);

	//window.setVerticalSyncEnabled(true);

	// Open Font
	font.loadFromFile("OpenSans-Regular.ttf");

	// Unset the stop program variable
	stop = 0;

	// Set View Position
	view.x = 0;
	view.y = 0;

	// Create the Astronomical Objects
	astro.push_back(std::unique_ptr<AstroObject>(new Sun(0, 0, 500, sf::Color(255, 255, 0))));
	astro.push_back(std::unique_ptr<AstroObject>(new Planet(-1000, 1000, 50, sf::Color(0, 0, 255))));

	// Pixels Per Meter
	ppm = 1;

	frameRate.setFont(font);
	frameRate.setString("0");
}

Game::~Game() {
	window.close();
}

int Game::getStop() {
	return stop;
}

float Game::dist(long long x1, long long y1, long long x2, long long y2) {
	float X = pow(x1 - x2, 2);
	float Y = pow(y1 - y2, 2);

	return sqrt(X + Y);
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
		case sf::Event::MouseWheelMoved:
			ppm -= event.mouseWheel.delta;
			if (ppm < 1)
				ppm = 1;
			break;
		default:
			break;
		}
	}
}

void Game::keyPressed() {
	// +
	if (keys[68]) {
		ppm += 0.01;
	}
	// -
	if (keys[67]) {
		ppm -= 0.01;
		if (ppm <= 0)
			ppm = 0.01;
	}
}

void Game::update() {
	// Check Events
	events();

	// Get FrameRate
	if (clock.getElapsedTime().asSeconds() >= 1) {
		clock.restart();
		frameRate.setString(std::to_string(frames + 1));
		frames = 0;
	}
	else
	{
		frames++;
	}

	// *** Not working
	//if (frameTime.getElapsedTime().asSeconds() > 0.01) {
		// Check Keyboard Presses
		keyPressed();

		// Apply Force
		for (int i = 1; i < astro.size(); i++) {
			astro[i]->setForce(astro[0]->getG() * astro[0]->getMass() * astro[i]->getMass() / pow(dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()), 2));
			float x, y;
			if (astro[0]->getX() < astro[i]->getX())
				x = -1;
			else
				x = 1;
			if (astro[0]->getY() < astro[i]->getY())
				y = -1;
			else
				y = 1;
			astro[i]->setDirection(x, y);
		}

		// Update all the objects
		for (int i = 0; i < astro.size(); i++) {
			astro[i]->update();
		}
		//frameTime.restart();
	//}
}

void Game::render() {
	// Clear the Window
	window.clear(sf::Color::Black);

	/* --------------- Draw --------------- */

	for (int i = 0; i < astro.size(); i++) {
		//astro[i] -> update();
		astro[i] -> render(window, view, screen, ppm);
	}

	// Draw the frameRate
	window.draw(frameRate);

	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}