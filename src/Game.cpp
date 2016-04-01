#include <Game.h>

Game::Game() {
	// Window Settings
	settings.antialiasingLevel = 2;

	// Get the Screen Resolution
	screen = sf::VideoMode::getDesktopMode();

	// Open a new Window
	window.create(screen, "SFML Window", sf::Style::None, settings); //sf::Style::Fullscreen

	// Frame Count
	fps = 60;
	dt = 1 / fps;

	// Set framerate limit - maybe temporarily
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	// Open Font
	font.loadFromFile("OpenSans-Regular.ttf");

	// Unset the stop program variable
	stop = 0;

	// Set View Position
	view.x = 0;
	view.y = 0;

	// Setting the random seed
	srand(time(NULL));

	// Load Textures for the Objects
	commonTexture.loadFromFile("Source/resources/tree.png");

	// Create the Astronomical Objects
	astro.push_back(std::unique_ptr<AstroObject>(new Sun(0, 0, 1900, sf::Color(255, 255, 0), 0)));
	
	// Set the name of the Sun
	astro[0]->setName("Sun");
	astro[0]->setInhabitants(0);

	noPlanets = Functions::randomInt(5, 10);

	float rDist = 0;
	for (int i = 1; i < noPlanets; i++) {
		// Generate random Distance from the Sun, random Radius and random Orbital Phase
		rDist += Functions::randomInt(100000, 150000);
		float rR = Functions::randomInt(300, 500);
		float angle = Functions::randomFloat(0, PI * 2);
		
		// Create the Astro Object in the generated position
		astro.push_back(std::unique_ptr<AstroObject>(new Planet(-cos(angle) * rDist, -sin(angle) * rDist, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256), Functions::randomFloat(0.005, 0.01))));
		
		// Create Common Textures
		astro[i]->createCommonObjects(&commonTexture);

		// Set number of Inhabitants
		astro[i]->setInhabitants(Functions::randomInt(10, 99));

		// Increase the Angle to match the Direction of the Velocity Vector
		angle += PI / 2;

		// Calculate the Velocity needed to stay in Circular Orbit
		float aV = sqrt(astro[0]->getG() * astro[0]->getMass() / Functions::dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()));
	
		// Set the velocity of the Astro Object
		astro[i]->addVelocity(-cos(angle) * aV, -sin(angle) * aV);

		// Set the name of the Planets
		std::ifstream f;
		f.open("Source/resources/Gods.txt");
		if (f) {
			std::string n;
			for (int i = 0; i < Functions::randomInt(0, 2500); i++) {
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
	}

	// Add Ships
	ships.push_back(std::unique_ptr<Ship>(new Ship(astro[1]->getX(), astro[1]->getY() - astro[1]->getRadius(), (float)(screen.width / 2), (float)(screen.height / 2))));

	// Set the closest Planet to the Ship
	ships[0]->setClosestPlanet(1);

	// Add Human
	humanTexture.loadFromFile("Source/resources/humanSheet.png");
	human = std::unique_ptr<Human>(new Human(0, 0, &humanTexture));

	// Add Velocity Vector
	velocityVector = std::unique_ptr<VelocityVector>(new VelocityVector(screen));
	velocityVector -> setFont(font);

	// Add Distance To Object
	distanceObject = std::unique_ptr<DistanceToObject>(new DistanceToObject(screen, font));

	// Add Thrust
	thrust = std::unique_ptr<Thrust>(new Thrust(screen, font));

	// Add Fuel
	fuel = std::unique_ptr<Fuel>(new Fuel(screen, font));

	// Pixels Per Meter
	ppm = 1;

	// FrameRate Settings
	frameRate.setFont(font);
	frameRate.setString("0");

	// Distance Indicator
	//distance.setFont(font);
	//distance.scale(0.5, 0.5);
	//distance.setOrigin(distance.getLocalBounds().width / 2, distance.getLocalBounds().height / 2);
	//distance.setString("0");

	// Inertia Dampers Text
	idText.setFont(font);
	idText.setCharacterSize(12);
	idText.setString("Inertia Damper: ON");
	idText.setPosition(0, frameRate.getCharacterSize() * 1.5);

	accumulator = 0;

	for (unsigned int i = 0; i < 200; i++) {
		stars[i][0] = Functions::randomInt(0, screen.width);
		stars[i][1] = Functions::randomInt(0, screen.height);
		stars[i][2] = Functions::randomInt(1, 3);
	}

	// Menu Flags
	menu["map"] = false;

	//ppm = dist(0, 0, astro[noPlanets - 1] -> getX(), astro[noPlanets - 1] -> getY()) / (screen.height / 2);

	// Create an Astro Map
	astroMap = std::unique_ptr<AstroMap>(new AstroMap((float)(Functions::dist(0, 0, astro[noPlanets - 1]->getX(), astro[noPlanets - 1]->getY()) / (screen.height / 2.2)), font));
	astroMap -> setShip(ships[0]->getX(), ships[0]->getY());
	for (unsigned i = 0; i < astro.size(); i++) {
		astroMap -> addAstro(screen, astro[i] -> getX(), astro[i] -> getY(), astro[i] -> getColour(), astro[i] -> getRadius());
	}

	// Unset the Target Object
	targetAstro = -1;

	// Set the player mode
	onPlanet = false;

	// Set the Human's state
	jump = false;

	closestPlanet = 1;

	// Create Vector to store the Locals
	for (int i = 0; i < 100; i++) {
		locals.push_back(std::unique_ptr<Human>(new Human(0, 0, &humanTexture)));
		int cP = closestPlanet;
		float theta = Functions::randomFloat(0, 2 * PI);
		locals[i]->setX(astro[cP]->getX() - cos(theta) * astro[cP]->getRadius());
		locals[i]->setY(astro[cP]->getY() - sin(theta) * astro[cP]->getRadius());
	}
}

Game::~Game() {
	window.close();
}

int Game::getStop() {
	return stop;
}
//
//double Game::dist(double x1, double y1, double x2, double y2) {
//	double X = pow(x2 - x1, 2);
//	double Y = pow(y2 - y1, 2);
//
//	return sqrt(X + Y);
//}
//
//double Game::map(double v, double lmin, double lmax, double rmin, double rmax) {
//	if (v < lmin)
//		v = lmin;
//
//	if (v > lmax)
//		v = lmax;
//
//	double leftRange = lmax - lmin;
//	double rightRange = rmax - rmin;
//
//	double leftPercentage = (v - lmin) / leftRange;
//
//	return rmin + (leftPercentage * rightRange);
//}

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
			// E - Exit / Enter
			if (event.key.code == 4) {
				onPlanet = !onPlanet;
				// Initial Settings when the Player Exits the Ship
				if (onPlanet) {
					int cP = ships[0]->getClosestPlanet();
					float dy = astro[cP]->getY() - ships[0]->getY();
					float dx = astro[cP]->getX() - ships[0]->getX();
					float theta = atan2(dy, dx);
					theta = theta >= 0 ? theta : theta + 2 * PI;
					//theta += 0.01;
					human->setX(astro[cP]->getX() - cos(theta) * astro[cP]->getRadius());
					human->setY(astro[cP]->getY() - sin(theta) * astro[cP]->getRadius());
				}
			}
			// X - Cut Thrust
			if (event.key.code == 23) {
				ships[0]->cutThrust();
			}

			// I - Toggle Inertia Damper
			if (event.key.code == 8) {
				ships[0]->setInertiaDamper(!ships[0]->getInertiaDamper());
				if (ships[0]->getInertiaDamper())
					idText.setString("Inertia Damper: ON");
				else
					idText.setString("Inertia Damper: OFF");
			}
				//window.close();
			// Set the pressed key
			keys[event.key.code] = 1;
			//std::cout << "Key Pressed: " << event.key.code << std::endl;
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
			if (ppm <= 0.05)
				ppm = 0.05f;
			if (ppm > 1)
				ppm = 1;
			break;
		default:
			break;
		}
	}
}
//
//int Game::randomInt(int start, int stop) {
//	return rand() % (stop - start + 1) + start;
//}
//
//float Game::randomFloat(float start, float stop) {
//	return start + (float)(rand() / (float)(RAND_MAX / (stop - start)));
//}

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
	float speedMult = 1;
	// Shift
	if (keys[38]) {
		speedMult = 5;
	}

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
	if (keys[22] && !onPlanet) {
		ships[0]->addVelocity();
		//ships[0]->setAccelerating(true);
	}

	// S
	if (keys[18] && !onPlanet) {
		ships[0]->subVelocity();
		//ships[0]->setAccelerating(true);
		//ships[0]->setLanded(false);
	}

	bool moved = false;

	// A
	if (keys[0]) {
		if (!onPlanet) {
			// Ship
			ships[0]->addRotation(-0.05f);
		} else {
			// Human
			float f;
			if (!jump) {
				f = 0.001 * speedMult;
				human->setDir(-1);
			} else {
				f = 0.00001 * speedMult;
				human->setDirJump(-1);
			}
			int cP = ships[0]->getClosestPlanet();
			float dy = astro[cP]->getY() - human->getY();
			float dx = astro[cP]->getX() - human->getX();
			float theta = atan2(dy, dx);
			theta = theta >= 0 ? theta : theta + 2 * PI;
			theta -= PI / 2;
			float acceleration = f / human->getMass();
			human->addVelocity(-cos(theta) * acceleration, -sin(theta) * acceleration);
			
			moved = true;
		}
	}

	// D
	if (keys[3]) {
		if (!onPlanet) {
			// Ship
			ships[0]->addRotation(0.05f);
		} else {
			// Human
			float f;
			if (!jump) {
				f = 0.001 * speedMult;
				human->setDir(1);
			} else {
				f = 0.00001 * speedMult;
				human->setDirJump(1);
			}
			int cP = ships[0]->getClosestPlanet();
			float dy = astro[cP]->getY() - human->getY();
			float dx = astro[cP]->getX() - human->getX();
			float theta = atan2(dy, dx);
			theta = theta >= 0 ? theta : theta + 2 * PI;
			theta += PI / 2;
			float acceleration = f / human->getMass();
			human->addVelocity(-cos(theta) * acceleration, -sin(theta) * acceleration);
			
			moved = true;
		}
	}

	// Reset the Sprite if the Human is not moving and he's not mid air
	if (!moved && !jump) {
		human->resetSprite();
	}

	// SPACE
	if (keys[57]) {
		if (!onPlanet) {
			// Ship
			ships[0]->resetRotation();
		} else {
			if (!jump) {
				// Human
				float f = 0.0025;
				int cP = ships[0]->getClosestPlanet();
				float dy = astro[cP]->getY() - human->getY();
				float dx = astro[cP]->getX() - human->getX();
				float theta = atan2(dy, dx);
				theta = theta >= 0 ? theta : theta + 2 * PI;
				//theta += PI;
				float acceleration = f / human->getMass();
				human->addVelocity(-cos(theta) * acceleration, -sin(theta) * acceleration);
				jump = true;

				// Add the Velocity that is caused by the Rotation of the Object to the Human
				double circumference = (double)(2.0f * (double)PI * (double)astro[cP]->getRadius());
				double velVect = (double)Functions::map((double)astro[cP]->getRotation(), 0, 358.75, 0, circumference);
				human->addVelocity(-cos(theta + (double)PI / 2) * (double)velVect, -sin(theta + (double)PI / 2) * (double)velVect);
			}
		}
	}
}

void Game::fastForwardObject(int i, int loops) {
	for (int j = 0; j < loops; j++) {
		// Apply Force to the Planet
		astro[i]->setForce(astro[0]->getG() * astro[0]->getMass() * astro[i]->getMass() / pow(Functions::dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()), 2));

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
			if (Functions::dist(astro[i]->getX(), astro[i]->getY(), ships[j]->getX(), ships[j]->getY()) < astro[i]->getRadius() + 20 * 0.15) {
				// Get the Angle between the Ship and the Object
				float dy = astro[i]->getY() - ships[j]->getY();
				float dx = astro[i]->getX() - ships[j]->getX();
				float theta = atan2(dy, dx);
				theta = theta >= 0 ? theta : theta + 2 * PI;
				theta += astro[i]->getRotation() * PI / 180;

				// Reset the Velocity of the Ship
				ships[j]->resetVelocity();

				// Add the Velocity of the Object to the Velocity of the Ship
				sf::Vector2<double> v = astro[i]->getVelocity();
				ships[j]->addVelocity(v.x, v.y);

				// Add the Velocity that is caused by the Rotation of the Object to the Ship
				//double circumference = (double)(2.0f * (double)PI * (double)astro[i]->getRadius());
				//double velVect = (double)Functions::map((double)astro[i]->getRotation(), 0, 358.75, 0, circumference);
				//ships[j]->addVelocity(-cos(theta + (double)PI / 2) * (double)velVect, -sin(theta + (double)PI / 2) * (double)velVect);

				// Set the Position of the Human to be at the edge of the Object
				ships[j]->setX(astro[i]->getX() - cos(theta) * (astro[i]->getRadius() + 20 * 0.15)); // + ships[j]->getRadius()
				ships[j]->setY(astro[i]->getY() - sin(theta) * (astro[i]->getRadius() + 20 * 0.15)); // + ships[j]->getRadius()

				// Rotate the Ship to match the Object's Rotation
				ships[j]->setRotation(astro[i]->getRotation());

				// Set the Landed Flag
				ships[j]->setLanded(true);
			}
		}
		if (Functions::dist(astro[i]->getX(), astro[i]->getY(), human->getX(), human->getY()) < astro[i]->getRadius() + 20 * 0.07 && onPlanet) { // i == ships[0]->getClosestPlanet() && 
			// Get the Angle between the Human and the Object
			float dy = astro[i]->getY() - human->getY();
			float dx = astro[i]->getX() - human->getX();
			float theta = atan2(dy, dx);
			theta = theta >= 0 ? theta : theta + 2 * PI;

			if (!jump)
				theta += astro[i]->getRotation() * PI / 180;

			// Reset the Velocity of the Human
			human->resetVelocity();

			// Add the Velocity of the Object to the Velocity of the Human
			sf::Vector2<double> v = astro[i]->getVelocity();
			human->addVelocity(v.x, v.y);

			// Add the Velocity that is caused by the Rotation of the Object to the Human
			//double circumference = (double)(2.0f * (double)PI * (double)astro[i]->getRadius());
			//double velVect = (double)Functions::map((double)astro[i]->getRotation(), 0, 358.75, 0, circumference);
			//human->addVelocity(-cos(theta + (double)PI / 2) * (double)velVect, -sin(theta + (double)PI / 2) * (double)velVect);

			// Set the Position of the Human to be at the edge of the Object
			human->setX(astro[i]->getX() - cos(theta) * (astro[i]->getRadius() + 20 * 0.07));
			human->setY(astro[i]->getY() - sin(theta) * (astro[i]->getRadius() + 20 * 0.07));

			// Reset the Jump Flag
			jump = false;
		}
		for (int j = 0; j < astro[closestPlanet]->getInhabitants(); j++) {
			if (Functions::dist(astro[i]->getX(), astro[i]->getY(), locals[j]->getX(), locals[j]->getY()) < astro[i]->getRadius() + 20 * 0.07) {
				float dy = astro[i]->getY() - locals[j]->getY();
				float dx = astro[i]->getX() - locals[j]->getX();
				float theta = atan2(dy, dx);
				theta = theta >= 0 ? theta : theta + 2 * PI;
				theta += astro[i]->getRotation() * PI / 180;
				locals[j]->resetVelocity();
				sf::Vector2<double> v = astro[i]->getVelocity();
				locals[j]->addVelocity(v.x, v.y);
				locals[j]->setX(astro[i]->getX() - cos(theta) * (astro[i]->getRadius() + 20 * 0.07));
				locals[j]->setY(astro[i]->getY() - sin(theta) * (astro[i]->getRadius() + 20 * 0.07));
				locals[j]->setJump(false);
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
			astro[i]->setForce(astro[0]->getG() * astro[0]->getMass() * astro[i]->getMass() / pow(Functions::dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()), 2));

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
			if (Functions::dist(astro[i]->getX(), astro[i]->getY(), ships[0]->getX(), ships[0]->getY()) < minDist) {
				minDist = Functions::dist(astro[i]->getX(), astro[i]->getY(), ships[0]->getX(), ships[0]->getY());
				z = i;
			}
		}

		// Apply force to the Ship
		ships[0]->setForce(astro[z]->getG() * astro[z]->getMass() * ships[0]->getMass() / pow(Functions::dist(astro[z]->getX(), astro[z]->getY(), ships[0]->getX(), ships[0]->getY()), 2));
		ships[0]->setClosestPlanet(z);

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
			distFromCentre = (int)Functions::dist(astro[z]->getX(), astro[z]->getY(), ships[0]->getX(), ships[0]->getY()) - (int)astro[z]->getRadius() - (int)(20 * 0.15);
		distFromCentre = distFromCentre < 0 ? 0 : distFromCentre;

		// Update for the Human
		if (onPlanet) {
			// Apply force to the human
			human->setForce(astro[z]->getG() * astro[z]->getMass() * human->getMass() / pow(Functions::dist(astro[z]->getX(), astro[z]->getY(), human->getX(), human->getY()), 2));

			// Angle between the Human and the Planets
			dy = human->getY() - astro[z]->getY();
			dx = human->getX() - astro[z]->getX();
			float hAngle = atan2(dy, dx);
			hAngle = hAngle >= 0 ? hAngle : hAngle + 2 * PI;
			human->setDirection(-cos(hAngle), -sin(hAngle));
			human->setAngle((hAngle + PI / 2) * 180 / PI);

			// Update the Human
			human->update();

			//dy = astro[z]->getY() - human->getY();
			//dx = astro[z]->getX() - human->getX();
			//hAngle = atan2(dy, dx);
			//hAngle = hAngle >= 0 ? hAngle : hAngle + 2 * PI;
			//hAngle += astro[z]->getRotation() * PI / 180;

			//human->setX(astro[z]->getX() - cos(hAngle) * (Functions::dist(astro[z]->getX(), astro[z]->getY(), human->getX(), human->getY()) + 20 * 0.07));
			//human->setY(astro[z]->getY() - sin(hAngle) * (Functions::dist(astro[z]->getX(), astro[z]->getY(), human->getX(), human->getY()) + 20 * 0.07));
		}

		// Update for the Locals
		for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
			float f, dx, dy, theta, acceleration;
			int cP;

			// Movement
			if (stateTime.getElapsedTime().asSeconds() > locals[i]->getNextStateChange()) {
				locals[i]->setNextStateChange(stateTime.getElapsedTime().asSeconds() + Functions::randomFloat(0, 10));
				locals[i]->setState(Functions::randomInt(0, 3));
			} else {
				switch (locals[i]->getState()) {
					case 1:
						// Go Left
						if (!locals[i]->getJump()) {
							f = 0.001;
							locals[i]->setDir(-1);
						} else {
							f = 0.00001;
							locals[i]->setDirJump(-1);
						}
						cP = ships[0]->getClosestPlanet();
						dy = astro[cP]->getY() - locals[i]->getY();
						dx = astro[cP]->getX() - locals[i]->getX();
						theta = atan2(dy, dx);
						theta = theta >= 0 ? theta : theta + 2 * PI;
						theta -= PI / 2;
						acceleration = f / locals[i]->getMass();
						locals[i]->addVelocity(-cos(theta) * acceleration, -sin(theta) * acceleration);
						break;
					case 2:
						// Go Right
						if (!locals[i]->getJump()) {
							f = 0.001;
							locals[i]->setDir(1);
						} else {
							f = 0.00001;
							locals[i]->setDirJump(1);
						}
						cP = ships[0]->getClosestPlanet();
						dy = astro[cP]->getY() - locals[i]->getY();
						dx = astro[cP]->getX() - locals[i]->getX();
						theta = atan2(dy, dx);
						theta = theta >= 0 ? theta : theta + 2 * PI;
						theta += PI / 2;
						acceleration = f / locals[i]->getMass();
						locals[i]->addVelocity(-cos(theta) * acceleration, -sin(theta) * acceleration);
						break;
					case 3:
						// Jump
						if (!locals[i]->getJump()) {
							// Human
							f = 0.0025;
							cP = ships[0]->getClosestPlanet();
							dy = astro[cP]->getY() - locals[i]->getY();
							dx = astro[cP]->getX() - locals[i]->getX();
							theta = atan2(dy, dx);
							theta = theta >= 0 ? theta : theta + 2 * PI;
							//theta += PI;
							acceleration = f / locals[i]->getMass();
							locals[i]->addVelocity(-cos(theta) * acceleration, -sin(theta) * acceleration);
							locals[i]->setJump(true);

							// Add the Velocity that is caused by the Rotation of the Object to the Human
							double circumference = (double)(2.0f * (double)PI * (double)astro[cP]->getRadius());
							double velVect = (double)Functions::map((double)astro[cP]->getRotation(), 0, 358.75, 0, circumference);
							locals[i]->addVelocity(-cos(theta + (double)PI / 2) * (double)velVect, -sin(theta + (double)PI / 2) * (double)velVect);
						}
						break;
					default:
						// Wait
						break;
				}
				if (locals[i]->getState() != 1 && locals[i]->getState() != 2 && !locals[i]->getJump()) {
					locals[i]->resetSprite();
				}
			}

			// Gravity
			dy = locals[i]->getY() - astro[z]->getY();
			dx = locals[i]->getX() - astro[z]->getX();
			float hAngle = atan2(dy, dx);
			hAngle = hAngle >= 0 ? hAngle : hAngle + 2 * PI;
			locals[i]->setForce(astro[z]->getG() * astro[z]->getMass() * locals[i]->getMass() / pow(Functions::dist(astro[z]->getX(), astro[z]->getY(), locals[i]->getX(), locals[i]->getY()), 2));
			locals[i]->setDirection(-cos(hAngle), -sin(hAngle));
			locals[i]->setAngle((hAngle + PI / 2) * 180 / PI);
			locals[i]->update();
		}

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

		// Unset the Landed Flag
		if (ships[0]->getLanded() && Functions::dist(astro[closestPlanet]->getX(), astro[closestPlanet]->getY(), ships[0]->getX(), ships[0]->getY()) > astro[closestPlanet]->getRadius() + 20 * 0.15 + 0.1) {
			int cP = ships[0]->getClosestPlanet();
			// Get the Angle between the Ship and the Object
			float dy = astro[cP]->getY() - ships[0]->getY();
			float dx = astro[cP]->getX() - ships[0]->getX();
			float theta = atan2(dy, dx);
			theta = theta >= 0 ? theta : theta + 2 * PI;

			// Add the Velocity that is caused by the Rotation of the Object to the Human
			double circumference = (double)(2.0f * (double)PI * (double)astro[cP]->getRadius());
			double velVect = (double)Functions::map((double)astro[cP]->getRotation(), 0, 358.75, 0, circumference);
			ships[0]->addVelocity(-cos(theta + (double)PI / 2) * (double)velVect, -sin(theta + (double)PI / 2) * (double)velVect);
			ships[0]->setLanded(false);
		}

		// Move Locals to the Closest Planet
		if (ships[0]->getClosestPlanet() != closestPlanet && ships[0]->getClosestPlanet() != 0) {
			closestPlanet = ships[0]->getClosestPlanet();
			for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
				int cP = closestPlanet;
				float theta = Functions::randomFloat(0, 2 * PI);
				locals[i]->setX(astro[cP]->getX() - cos(theta) * astro[cP]->getRadius());
				locals[i]->setY(astro[cP]->getY() - sin(theta) * astro[cP]->getRadius());
			}
		}

		// Update the view
		if (!onPlanet) {
			view.x = ships[0]->getX();
			view.y = ships[0]->getY();
		} else {
			view.x = human->getX();
			view.y = human->getY();
		}

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
			int distFromTarget = (int)Functions::dist(astro[targetAstro]->getX(), astro[targetAstro]->getY(), ships[0]->getX(), ships[0]->getY()) - (int)astro[targetAstro]->getRadius() - (int)(20 * 0.15);
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

		// Thrust
		thrust->update(ships[0]->getThrustPercentage());

		// Fuel
		fuel->update(ships[0]->getFuelPercentage());

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
					c.setPosition(Functions::map(stars[i][0], hMargin, screen.width - hMargin, 0, screen.width) - 20, Functions::map(stars[i][1], vMargin, screen.height - vMargin, 0, screen.height) - 20);
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
			if (i == closestPlanet || i == 0)
				astro[i]->render(window, view, screen, ppm);
		}

		// Ships
		for (int i = 0; i < ships.size(); i++) {
			ships[i]->render(window, view, screen, ppm);
		}

		// Locals
		for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
			locals[i]->render(window, view, screen, ppm);
		}

		// Human
		if (onPlanet) {
			human->render(window, view, screen, ppm);
		} else {
			// Velocity Vector
			velocityVector->render(window);

			// Distance To Object
			distanceObject->render(window);

			// Thurst
			thrust->render(window);

			// Fuel
			fuel->render(window);

			// Inertia Damper
			window.draw(idText);
		}
	}

	// Draw the frameRate
	window.draw(frameRate);


	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}