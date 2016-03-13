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
	astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, 100000, 500, sf::Color(0, 0, 255))));

	for (int i = 2; i < 4; i++) {
		float rDist = rand() % (100000 - 50000 + 1) + 50000;
		float rR = rand() % (500 - 250 + 1) + 250;
		astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, dist(astro[0]->getX(), astro[0]->getY(), astro[i - 1] -> getX(), astro[i - 1]->getY()) + rDist, rR, sf::Color(rand() % 256 , rand() % 256 , rand() % 256))));
	}
	

	// Initial Velocity for the Planets
	int i = 1;
	for (unsigned int i = 1; i < astro.size(); i++) {
		astro[i]->addVelocity(sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY())), 0);
	}

	// Add Ships
	ships.push_back(std::unique_ptr<Ship>(new Ship(2500, 100000, (float)(screen.width / 2), (float)(screen.height / 2))));

	//std::cout << ships[0]

	//ships[0]->addVelocity(0, sqrt(astro[1]->getG() * astro[1]->getMass() / (dist(astro[1]->getX(), astro[1]->getY(), ships[0]->getX(), ships[0]->getY()))));
	//std::cout << ships[0]->getVelocity().x << " " << ships[0]->getVelocity().y << std::endl;

	// Add Velocity Vector
	velocityVector = std::unique_ptr<VelocityVector>(new VelocityVector(screen));
	velocityVector -> setFont(font);
	//*velocityVector = std::unique_ptr<VelocityVector>(new VelocityVector(screen));

	// Pixels Per Meter
	ppm = 1;

	// FrameRate Settings
	frameRate.setFont(font);
	frameRate.setString("0");

	// Distance Indicator
	distance.setFont(font);
	distance.scale(0.5, 0.5);
	distance.setOrigin(distance.getLocalBounds().width / 2, distance.getLocalBounds().height / 2);
	distance.setString("0");

	accumulator = 0;
}

Game::~Game() {
	window.close();
}

int Game::getStop() {
	return stop;
}

double Game::dist(double x1, double y1, double x2, double y2) {
	double X = pow(x2 - x1, 2);
	double Y = pow(y2 - y1, 2);

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
			//view.x += (int)(event.mouseButton.x - screen.width / 2) * ppm;
			//view.y += (int)(event.mouseButton.y - screen.height / 2) * ppm;
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

/*
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
*/

void Game::keyPressed() {
	// +
	if (keys[68]) {
		float s = 1;
		// Increase Zoom Speed
		if (keys[37]) {
			s = 100;
		}
		ppm += (float)(0.01 * s);
	}

	// -
	if (keys[67]) {
		float s = 1;
		// Increase Zoom Speed
		if (keys[37]) {
			s = 100;
		}
		ppm -= (float)(0.01 * s);
		if (ppm <= 0)
			ppm = 0.01f;
	}

	// W
	if (keys[22]) {
		ships[0]->addVelocity();
		ships[0]->setAccelerating(true);
		//ships[0]->setLanded(false);
	}

	// S
	if (keys[18]) {
		ships[0]->subVelocity();
		ships[0]->setAccelerating(true);
		//ships[0]->setLanded(false);
	}

	// A
	if (keys[0]) {
		ships[0]->addRotation(-0.05f);
	}

	// D
	if (keys[3]) {
		ships[0]->addRotation(0.05f);
	}

	// SPACE
	if (keys[57]) {
		ships[0]->resetRotation();
	}
}

void Game::collisions() {
	for (int i = 0; i < astro.size(); i++) {
		for (int j = 0; j < ships.size(); j++) {
			//if (ships[j]->getLanded() && ships[j]->getPlanet() == i) {
			//	float theta = ships[j]->getAngleToPlanet();
			//	ships[j]->setX(astro[i]->getX() - cos(theta) * (astro[i]->getRadius() + 20 * 0.25));
			//	ships[j]->setY(astro[i]->getY() - sin(theta) * (astro[i]->getRadius() + 20 * 0.25));
			//	ships[j]->resetVelocity();
			//	sf::Vector2<double> v = astro[i]->getVelocity();
			//	ships[j]->addVelocity(v.x, v.y);
			//} else
			
			//sf::FloatRect bB1 = astro[i] -> getBoundingBox();
			//sf::FloatRect bB2 = ships[j] -> getBoundingBox();
			//if (bB1.intersects(bB2)) {
			ships[j]->setLanded(false);
			if (dist(astro[i]->getX(), astro[i]->getY(), ships[j]->getX(), ships[j]->getY()) < astro[i]->getRadius() + 20 * 0.15) { // + ships[j] -> getRadius()
				float dy = astro[i]->getY() - ships[j]->getY();
				float dx = astro[i]->getX() - ships[j]->getX();
				float theta = atan2(dy, dx);
				theta = theta >= 0 ? theta : theta + 2 * PI;
				ships[j]->resetVelocity();
				sf::Vector2<double> v = astro[i]->getVelocity();
				ships[j]->addVelocity(v.x, v.y);
				ships[j]->setX(astro[i]->getX() - cos(theta) * (astro[i]->getRadius() + 20 * 0.15)); // + ships[j]->getRadius()
				ships[j]->setY(astro[i]->getY() - sin(theta) * (astro[i]->getRadius() + 20 * 0.15)); // + ships[j]->getRadius()
				ships[j]->setLanded(true);
				//std::cout << dist(astro[i]->getX(), astro[i]->getY(), ships[j]->getX(), ships[j]->getY()) << std::endl;
				//ships[j]->setAngleToPlanet(theta);
				//ships[j]->setLanded(true);
				//ships[j]->setPlanet(i);
				//ships[j]->setX(ships[j]->getOldX());
				//ships[j]->setY(ships[j]->getOldY());

				//// Apply force to the Ship
				//ships[0]->setForce(astro[i]->getG() * astro[i]->getMass() * ships[j]->getMass() / pow(dist(astro[i]->getX(), astro[i]->getY(), ships[j]->getX(), ships[j]->getY()), 2));

				//// Angle between the Ship and the Planets
				//float dy = ships[j]->getY() - astro[i]->getY();
				//float dx = ships[j]->getX() - astro[i]->getX();
				//float theta = atan2(dy, dx);
				//theta = theta >= 0 ? theta : theta + 2 * PI;
				//ships[j]->setDirection(cos(theta), sin(theta));
			}
		}
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
	while (accumulator >= dt) {

		ships[0]->setAccelerating(false);
		// *** Not working
		//if (frameTime.getElapsedTime().asSeconds() > 0.01) {
			// Check Keyboard Presses
		keyPressed();

		// Apply Force to the Planets
		for (unsigned int i = 1; i < astro.size(); i++) {
			astro[i]->setForce(astro[0]->getG() * astro[0]->getMass() * astro[i]->getMass() / pow(dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()), 2));

			// Angle between the Sun and the Planets
			float dy = astro[i]->getY() - astro[0]->getY();
			float dx = astro[i]->getX() - astro[0]->getX();
			float theta = atan2(dy, dx);
			theta = theta >= 0 ? theta : theta + 2 * PI;
			astro[i]->setDirection(-cos(theta), -sin(theta));
		}

		// Find the closest Planet
		double minDist = DBL_MAX;
		int z = 0;

		for (int i = 0; i < astro.size(); i++) {
			if (dist(astro[i]->getX(), astro[i]->getY(), ships[0]->getX(), ships[0]->getY()) < minDist) {
				minDist = dist(astro[i]->getX(), astro[i]->getY(), ships[0]->getX(), ships[0]->getY());
				z = i;
			}
		}

		// Apply force to the Ship
		ships[0]->setForce(astro[z]->getG() * astro[z]->getMass() * ships[0]->getMass() / pow(dist(astro[z]->getX(), astro[z]->getY(), ships[0]->getX(), ships[0]->getY()), 2));

		// Angle between the Ship and the Planets
		float dy = ships[0]->getY() - astro[z]->getY();
		float dx = ships[0]->getX() - astro[z]->getX();
		float theta = atan2(dy, dx);
		theta = theta >= 0 ? theta : theta + 2 * PI;
		ships[0]->setDirection(-cos(theta), -sin(theta));

		// Set distance to nearest Object
		int distFromCentre = (int)dist(astro[z]->getX(), astro[z]->getY(), ships[0]->getX(), ships[0]->getY()) - (int)astro[z]->getRadius();
		if (distFromCentre < screen.height / 2 * ppm) {
			distance.setString("");
		} else {
			char d[10];
			sprintf(d, "%d m", distFromCentre);
			distance.setString(d);
			distance.setPosition(screen.width / 2 + -cos(theta) * screen.height / 2 * 9 / 10, screen.height / 2 + -sin(theta) * screen.height / 2 * 9 / 10);
		}

		/*
		ships[0]->setForce(0);
		// Apply force to the ship
		for (int i = 0; i < astro.size(); i++) {
			if (dist(astro[i]->getX(), astro[i]->getY(), ships[0]->getX(), ships[0]->getY()) < astro[i]->getRadius() * 10) {
				ships[0]->addForce(astro[i]->getG() * astro[i]->getMass() * ships[0]->getMass() / pow(dist(astro[i]->getX(), astro[i]->getY(), ships[0]->getX(), ships[0]->getY()), 2));

				// Angle between the Ship and the Planets
				float dy = ships[0]->getY() - astro[i]->getY();
				float dx = ships[0]->getX() - astro[i]->getX();
				float theta = atan2(dy, dx);
				theta = theta >= 0 ? theta : theta + 2 * PI;
				ships[0]->setDirection(-cos(theta), -sin(theta));
			}
		}
		*/

		//std::cout << Formula::relativeOrbitalSpeed(astro[1]->getG(), astro[1]->getMass(), ships[0]->getMass(), dist(astro[1]->getX(), astro[1]->getY(), ships[0]->getX(), ships[0]->getY())) << std::endl;

		// Update all the objects
		for (int i = 0; i < astro.size(); i++) {
			astro[i]->update();
		}

		// Update the ships
		for (int i = 0; i < ships.size(); i++) {
			ships[i]->update();
		}

		collisions();

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

	// Distance to nearest Object
	window.draw(distance);


	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}