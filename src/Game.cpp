#include <Game.h>

Game::Game() {
	// Window Settings
	settings.antialiasingLevel = 2;

	// Get the Screen Resolution
	screen = sf::VideoMode::getDesktopMode();

	// Open a new Window
	window.create(screen, "SFML Window", sf::Style::None, settings); //sf::Style::Fullscreen

	// Frame Count
	float fps = 60;
	dt = 1 / fps;

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
	astro.push_back(std::unique_ptr<AstroObject>(new Sun(0, 0, 1900, sf::Color(255, 255, 0))));
	astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, 10000, 500, sf::Color(0, 0, 255))));

	/*
	for (int i = 2; i < 4; i++) {
		float rDist = rand() % (100000 - 50000 + 1) + 50000;
		float rR = rand() % (100 - 50 + 1) + 50;
		astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, apoapsis(i - 1) + rDist, rR, sf::Color(rand() % 256 , rand() % 256 , rand() % 256))));
	}
	*/

	// Initial Velocity for the Planets
	int i = 1;
	for (int i = 1; i < astro.size(); i++) {
		astro[i]->addVelocity(sqrt(astro[0]->getG() * astro[0]->getMass() / (dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()) - astro[0]->getRadius() - astro[i]->getRadius())), 0);
	}

	// Add Ships
	ships.push_back(std::unique_ptr<Ship>(new Ship(10000, 10000, screen.width / 2, screen.height / 2)));

	// Add Velocity Vector
	velocityVector = std::unique_ptr<VelocityVector>(new VelocityVector(screen));
	//*velocityVector = std::unique_ptr<VelocityVector>(new VelocityVector(screen));

	// Pixels Per Meter
	ppm = 1;

	frameRate.setFont(font);
	frameRate.setString("0");

	accumulator = 0;
}

Game::~Game() {
	window.close();
}

int Game::getStop() {
	return stop;
}

float Game::dist(double x1, double y1, double x2, double y2) {
	float X = pow(x2 - x1, 2);
	float Y = pow(y2 - y1, 2);

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
			//std::cout << event.key.code << " ";
			break;
		case sf::Event::MouseButtonPressed:
			// Change View
			view.x += (int)(event.mouseButton.x - screen.width / 2) * ppm;
			view.y += (int)(event.mouseButton.y - screen.height / 2) * ppm;
			break;
		case sf::Event::MouseWheelMoved:
			ppm -= event.mouseWheel.delta;
			if (ppm <= 0)
				ppm = 0.1f;
			break;
		default:
			break;
		}
	}
}

float Game::semiMajorAxis(int i) {
	// Distance from Sun to Planet
	float r = dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY());

	// Sun Mass
	float m1 = astro[0]->getMass();

	// Planet Mass
	float m2 = astro[i]->getMass();

	// G
	float G = astro[0]->getG();

	// Relative Orbital Speed
	float v = sqrt(G * (m1 + m2) / r);

	// Standard Gravitational Parameter
	float u = r * pow(v, 2);

	// Specific Orbital Energy
	float E = (pow(v, 2) / 2) - (u / r);

	// Semi-Major Axis
	float a = - u / 2 * E;

	return a;
}

float Game::eccentricityVector(int i) {
	// Distance from Sun to Planet
	float r = dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY());

	// Sun Mass
	float m1 = astro[0]->getMass();

	// Planet Mass
	float m2 = astro[i]->getMass();

	// G
	float G = astro[0]->getG();

	// Relative Orbital Speed
	float v = sqrt(G * (m1 + m2) / r);

	// Standard Gravitational Parameter
	float u = r * pow(v, 2);

	// Eccentricity Vector
	float e = (pow(v, 2) * r / u) - ((r * v) * v / u) - (r / abs(r));

	return e;
}

float Game::apoapsis(int i) {
	return semiMajorAxis(i) * (1 + abs(eccentricityVector(i)));
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

	// W
	if (keys[22]) {
		ships[0]->addVelocity();
	}

	// S
	if (keys[18]) {
		ships[0]->subVelocity();
	}

	// A
	if (keys[0]) {
		ships[0]->addRotation(-0.05);
	}

	// D
	if (keys[3]) {
		ships[0]->addRotation(0.05);
	}

	// SPACE
	if (keys[57]) {
		ships[0]->resetRotation();
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

	// Add time to the accumulator
	accumulator += frameTime.getElapsedTime().asSeconds();
	frameTime.restart();

	// Reset the accumulator if it's too big
	if (accumulator > 0.2f)
		accumulator = 0.2f;

	// Run Update when the accumualtor is bigger than delta time
	while (accumulator > dt) {

		// *** Not working
		//if (frameTime.getElapsedTime().asSeconds() > 0.01) {
			// Check Keyboard Presses
		keyPressed();

		// Apply Force
		for (int i = 1; i < astro.size(); i++) {
			astro[i]->setForce(astro[0]->getG() * astro[0]->getMass() * astro[i]->getMass() / pow(dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()), 2));
			//astro[i]->setForce(20);
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

		// Apply force to the ship
		for (int i = 1; i < astro.size(); i++) {
			ships[0]->addForce(astro[i]->getG() * astro[i]->getMass() * ships[0]->getMass() / pow(dist(astro[i]->getX(), astro[i]->getY(), ships[0]->getX(), ships[0]->getY()), 2));
			
			float x, y;
			if (astro[i]->getX() < ships[0]->getX())
				x = -1;
			else
				x = 1;
			if (astro[i]->getY() < ships[0]->getY())
				y = -1;
			else
				y = 1;
			ships[0]->setDirection(x, y);
		}

		// Update all the objects
		for (int i = 0; i < astro.size(); i++) {
			astro[i]->update();
		}

		// Update the ships
		for (int i = 0; i < ships.size(); i++) {
			ships[0]->update();
		}

		// Update the view
		view.x = ships[0] -> getX();
		view.y = ships[0] -> getY();

		// Velocity Vector - Fix
		velocityVector->update(ships[0]->getVelocity());

		//frameTime.restart();
		accumulator -= dt;
	//}
	}
}

void Game::render() {
	// Clear the Window
	window.clear(sf::Color::Black);


	/* --------------- Draw --------------- */

	// Star Field - WIP
	for (int i = 1; i < screen.width; i++) {
		for (int j = 1; j < screen.height; j++) {
			if ((i * j) % 100000 == 0) {
				sf::CircleShape star(2);
				star.setFillColor(sf::Color::White);
				star.setPosition(i, j);
				window.draw(star);
			}
		}
	}

	// Astronomical Object
	for (int i = 0; i < astro.size(); i++) {
		if (astro[i]->getX() + astro[i]->getRadius() > view.x - screen.width / 2 * ppm &&
			astro[i]->getX() - astro[i]->getRadius() < view.x + screen.width / 2 * ppm &&
			astro[i]->getY() + astro[i]->getRadius() > view.y - screen.height / 2 * ppm &&
			astro[i]->getY() - astro[i]->getRadius() < view.y + screen.height / 2 * ppm)
				astro[i] -> render(window, view, screen, ppm);
	}

	// Ships
	for (int i = 0; i < ships.size(); i++) {
		ships[i] -> render(window, view, screen, ppm);
	}

	// Velocity Vector
	velocityVector -> render(window);

	// Draw the frameRate
	window.draw(frameRate);


	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}