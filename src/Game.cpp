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

	// Set framerate limit - maybe temporarily
	window.setFramerateLimit(60);

	//window.setVerticalSyncEnabled(true);

	// Open Font
	font.loadFromFile("OpenSans-Regular.ttf");

	// Unset the stop program variable
	stop = 0;

	// Set View Position
	view.x = 0;
	view.y = 0;

	// Setting the random seed
	srand(time(NULL));

	// Create the Astronomical Objects
	astro.push_back(std::unique_ptr<AstroObject>(new Sun(0, 0, 1900, sf::Color(255, 255, 0))));
	
	// Set the name of the Sun
	astro[0]->setName("Sun");

	//float rae = rand() % 6;
	//astro.push_back(std::unique_ptr<AstroObject>(new Planet(-cos(rae) * 100000, -sin(rae) * 100000, 500, sf::Color(0, 0, 255))));
	//astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, 100000, 500, sf::Color(0, 0, 255))));

	noPlanets = randomInt(5, 10);

	float rDist = 0;
	for (int i = 1; i < noPlanets; i++) {
		//float rDist = rand() % (100000 - 50000 + 1) + 50000;
		//float rR = rand() % (500 - 250 + 1) + 250;
		
		// Generate random Distance from the Sun, random Radius and random Orbital Phase
		rDist += randomInt(100000, 150000);
		float rR = randomInt(300, 500);
		float angle = randomFloat(0, PI * 2);
		
		// Create the Astro Object in the generated position
		astro.push_back(std::unique_ptr<AstroObject>(new Planet(-cos(angle) * rDist, -sin(angle) * rDist, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256))));

		// Increase the Angle to match the Direction of the Velocity Vector
		angle += PI / 2;

		// Calculate the Velocity needed to stay in Circular Orbit
		float aV = sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()));
	
		// Set the velocity of the Astro Object
		astro[i]->addVelocity(-cos(angle) * aV, -sin(angle) * aV);

		// Set the name of the Planets
		//astro[i]->setName("Planet" + std::to_string(i));
		std::ifstream f;
		f.open("Gods.txt");
		if (f) {
			std::string n;
			for (int i = 0; i < randomInt(0, 2500); i++) {
				f >> n;
			}
			int k = 0;
			do {
				f >> n;
				k++;
			} while (n.size() > 10 && k < 100);
			f.close();
			astro[i]->setName(n);
		}

		//switch (randomInt(1, 4)) {
		//	case 1:
		//		astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, rDist, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256))));
		//		astro[i]->addVelocity(sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY())), 0);
		//		break;
		//	case 2:
		//		astro.push_back(std::unique_ptr<AstroObject>(new Planet(rDist, 0, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256))));
		//		astro[i]->addVelocity(0, -sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY())));
		//		break;
		//	case 3:
		//		astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, -rDist, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256))));
		//		astro[i]->addVelocity(-sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY())), 0);
		//		break;
		//	default:
		//		astro.push_back(std::unique_ptr<AstroObject>(new Planet(-rDist, 0, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256))));
		//		astro[i]->addVelocity(0, sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY())));
		//		break;
		//}
		//astro.push_back(std::unique_ptr<AstroObject>(new Planet(0, rDist, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256))));
		//astro[i]->addVelocity(sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY())), 0);
		//fastForwardObject(1, randomInt(1000, 10000));
	}

	// Initial Velocity for the Planets
	//int i = 1;
	//for (unsigned int i = 1; i < astro.size(); i++) {
	//	//double vel = sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()));
	//	//astro[i]->addVelocity(-sin(rae) * vel, -cos(rae));
	//	astro[i]->addVelocity(sqrt(astro[0]->getG() * astro[0]->getMass() / dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY())), 0);
	//	fastForwardObject(1, (int)(rand() % (100000 - 1000 + 1) + 1000));
	//}

	// Add Ships
	//ships.push_back(std::unique_ptr<Ship>(new Ship(-cos(rae) * 100000 + 500, -sin(rae) * 100000, (float)(screen.width / 2), (float)(screen.height / 2))));
	ships.push_back(std::unique_ptr<Ship>(new Ship(astro[1]->getX(), astro[1]->getY() - astro[1]->getRadius(), (float)(screen.width / 2), (float)(screen.height / 2))));

	//std::cout << ships[0]

	//ships[0]->addVelocity(0, sqrt(astro[1]->getG() * astro[1]->getMass() / (dist(astro[1]->getX(), astro[1]->getY(), ships[0]->getX(), ships[0]->getY()))));
	//std::cout << ships[0]->getVelocity().x << " " << ships[0]->getVelocity().y << std::endl;

	// Add Velocity Vector
	velocityVector = std::unique_ptr<VelocityVector>(new VelocityVector(screen));
	velocityVector -> setFont(font);

	// Add Distance To Object
	distanceObject = std::unique_ptr<DistanceToObject>(new DistanceToObject(screen, font));
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

	for (unsigned int i = 0; i < 200; i++) {
		stars[i][0] = randomInt(0, screen.width);
		stars[i][1] = randomInt(0, screen.height);
		stars[i][2] = randomInt(1, 3);
	}

	// Menu Flags
	menu["map"] = false;

	//ppm = dist(0, 0, astro[noPlanets - 1] -> getX(), astro[noPlanets - 1] -> getY()) / (screen.height / 2);

	// Create an Astro Map
	astroMap = std::unique_ptr<AstroMap>(new AstroMap((float)(dist(0, 0, astro[noPlanets - 1]->getX(), astro[noPlanets - 1]->getY()) / (screen.height / 2.2)), font));
	astroMap -> setShip(ships[0]->getX(), ships[0]->getY());
	for (unsigned i = 0; i < astro.size(); i++) {
		astroMap -> addAstro(screen, astro[i] -> getX(), astro[i] -> getY(), astro[i] -> getColour(), astro[i] -> getRadius());
	}

	// Unset the Target Object
	targetAstro = -1;
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

double Game::map(double v, double lmin, double lmax, double rmin, double rmax) {
	if (v < lmin)
		v = lmin;

	if (v > lmax)
		v = lmax;

	double leftRange = lmax - lmin;
	double rightRange = rmax - rmin;

	double leftPercentage = (v - lmin) / leftRange;

	return rmin + (leftPercentage * rightRange);
}

void Game::disableMenus() {
	for (auto el = menu.begin(); el != menu.end(); el++) {
		menu[el->first] = false;
	}
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
			// M - Open Map
			if (event.key.code == 12) {
				menu["map"] = !menu["map"];
			}
				//window.close();
			// Set the pressed key
			keys[event.key.code] = 1;
			//std::cout << event.key.code << " ";
			break;
		case sf::Event::KeyReleased:
			// Unset the released key
			keys[event.key.code] = 0;
			break;
		case sf::Event::MouseButtonPressed:
			// Change View
			//view.x += (int)(event.mouseButton.x - screen.width / 2) * ppm;
			//view.y += (int)(event.mouseButton.y - screen.height / 2) * ppm;
			break;
		case sf::Event::MouseWheelMoved:
			ppm -= event.mouseWheel.delta * 0.05;
			if (ppm <= 0.1)
				ppm = 0.1f;
			if (ppm > 1)
				ppm = 1;
			break;
		default:
			break;
		}
	}
}

int Game::randomInt(int start, int stop) {
	return rand() % (stop - start + 1) + start;
}

float Game::randomFloat(float start, float stop) {
	return start + (float)(rand() / (float)(RAND_MAX / (stop - start)));
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

void Game::fastForwardObject(int i, int loops) {
	for (int j = 0; j < loops; j++) {
		// Apply Force to the Planet
		astro[i]->setForce(astro[0]->getG() * astro[0]->getMass() * astro[i]->getMass() / pow(dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()), 2));

		// Angle between the Sun and the Planet
		float dy = astro[i]->getY() - astro[0]->getY();
		float dx = astro[i]->getX() - astro[0]->getX();
		float theta = atan2(dy, dx);
		theta = theta >= 0 ? theta : theta + 2 * PI;
		astro[i]->setDirection(-cos(theta), -sin(theta));
		astro[i]->update();
	}
}

void Game::collisions() {
	for (int i = 0; i < astro.size(); i++) {
		for (int j = 0; j < ships.size(); j++) {
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

		// Check keyboard presses
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
		int distFromCentre;
		if (ships[0]->getLanded())
			distFromCentre = 0;
		else
			distFromCentre = (int)dist(astro[z]->getX(), astro[z]->getY(), ships[0]->getX(), ships[0]->getY()) - (int)astro[z]->getRadius() - (int)(20 * 0.15);
		distFromCentre = distFromCentre < 0 ? 0 : distFromCentre;

		//if (distFromCentre < screen.height / 2 * ppm) {
		//	distance.setString("");
		//} else {
		//	char d[10];
		//	sprintf_s(d, "%d m", distFromCentre);
		//	distance.setString(d);
		//	distance.setPosition(screen.width / 2 + -cos(theta) * screen.height / 2 * 9 / 10, screen.height / 2 + -sin(theta) * screen.height / 2 * 9 / 10);
		//}

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

		// Check collisions
		collisions();

		// Update the view
		view.x = ships[0] -> getX();
		view.y = ships[0] -> getY();

		// Update the position of the Astro Object and Ship if the map is opened
		if (menu["map"]) {
			for (unsigned i = 0; i < astro.size(); i++) {
				astroMap->setAstro(window, screen, i, astro[i] -> getX(), astro[i] -> getY());
			}
			astroMap -> setShip(ships[0] -> getX(), ships[0] -> getY());
			int tempA = astroMap -> getClickedPlanet();
			if (tempA != -1)
				targetAstro = tempA;
		}

		// Setting the info for the target
		if (targetAstro != -1) {
			// Distance from Target
			int distFromTarget = (int)dist(astro[targetAstro]->getX(), astro[targetAstro]->getY(), ships[0]->getX(), ships[0]->getY()) - (int)astro[targetAstro]->getRadius() - (int)(20 * 0.15);
			distFromTarget = distFromTarget < 0 ? 0 : distFromTarget;

			// Angle between the Ship and the Target
			dy = ships[0]->getY() - astro[targetAstro]->getY();
			dx = ships[0]->getX() - astro[targetAstro]->getX();
			float thetaTarget = atan2(dy, dx);
			thetaTarget = thetaTarget >= 0 ? thetaTarget : thetaTarget + 2 * PI;

			distanceObject->setTargetDistance(distFromTarget);
			distanceObject->setTargetAngle(thetaTarget);
			distanceObject->setTargetName(astro[targetAstro]->getName());
		}

		// Velocity Vector
		velocityVector->update(ships[0]->getVelocity());

		// Distance To Object
		distanceObject->update(theta, distFromCentre, astro[z] -> getName(), ships[0] -> getAngle());

		//frameTime.restart();
		accumulator -= dt;
	//}
	}
}

void Game::render() {
	// Clear the Window
	window.clear(sf::Color::Black);


	/* --------------- Draw --------------- */

	if (menu["map"]) {
		// Astro Map
		astroMap -> render(window, screen);

		// Velocity Vector
		velocityVector->render(window);

		// Distance To Object
		distanceObject->render(window);
	} else {
		// Star Field
		for (unsigned int i = 0; i < 200; i++) {
			if (ppm < 1) {
				double newWidth = screen.width * ppm;
				double newHeight = screen.height * ppm;
				double hMargin = (screen.width - newWidth) / 2;
				double vMargin = (screen.height - newHeight) / 2;
				if (stars[i][0] > hMargin && stars[i][0] < screen.width - hMargin && stars[i][1] > vMargin && stars[i][1] < screen.height - vMargin) {
					sf::CircleShape c(stars[i][2]);
					c.setPosition(map(stars[i][0], hMargin, screen.width - hMargin, 0, screen.width) - 20, map(stars[i][1], vMargin, screen.height - vMargin, 0, screen.height) - 20);
					window.draw(c);
				}
			}
			else {
				sf::CircleShape c(stars[i][2]);
				c.setPosition(stars[i][0] - 20, stars[i][1] - 20);
				window.draw(c);
			}
		}

		// Astronomical Object
		for (int i = 0; i < astro.size(); i++) {
			/*if (astro[i]->getX() + astro[i]->getRadius() > view.x - screen.width / 2 * ppm &&
				astro[i]->getX() - astro[i]->getRadius() < view.x + screen.width / 2 * ppm &&
				astro[i]->getY() + astro[i]->getRadius() > view.y - screen.height / 2 * ppm &&
				astro[i]->getY() - astro[i]->getRadius() < view.y + screen.height / 2 * ppm)*/
			astro[i]->render(window, view, screen, ppm);
		}

		// Ships
		for (int i = 0; i < ships.size(); i++) {
			ships[i]->render(window, view, screen, ppm);
		}

		// Velocity Vector
		velocityVector->render(window);

		// Distance To Object
		distanceObject->render(window);
	}

	// Draw the frameRate
	window.draw(frameRate);


	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}