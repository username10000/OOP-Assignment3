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

	// Enable V-Sync to remove Screen Thearing
	window.setVerticalSyncEnabled(true);

	// Open Font
	font.loadFromFile("OpenSans-Regular.ttf");

	oldMouse.x = mouse.getPosition().x;
	oldMouse.y = mouse.getPosition().y;

	// Loading Message
	loadingMessage.setFont(font);
	loadingMessage.setPosition(screen.width / 2, screen.height / 2);
	setLoadingMessage("Loading...");
	loadingBar.setPosition(loadingMessage.getPosition().x - screen.width / 4, loadingMessage.getPosition().y + loadingMessage.getCharacterSize() * 1.5);
	loadingBar.setSize(sf::Vector2f(screen.width / 2, loadingMessage.getCharacterSize()));
	loadingBar.setFillColor(sf::Color::Transparent);
	loadingBar.setOutlineThickness(1);
	loadStatus.setPosition(loadingBar.getPosition());
	loadStatus.setSize(sf::Vector2f(0, 0));
	loadStatus.setFillColor(sf::Color(127, 127, 127));
	loadingState = 0;

	// Unset the stop program variable
	stop = 0;

	// Set View Position
	view.x = 0;
	view.y = 0;

	// Setting the random seed
	srand(time(NULL));

	// Load Sounds
	setLoadingMessage("Loading Music");
	music[0].openFromFile("Source/resources/Audio/planet.ogg");
	music[1].openFromFile("Source/resources/Audio/moon.ogg");
	music[0].setLoop(true);
	music[0].play();

	setLoadingMessage("Loading Sounds");
	std::string filenames[5] = { "acceptQuest.ogg", "returnQuest.ogg", "gameOver.ogg", "error.ogg", "warning.ogg" };
	for (int i = 0; i < 5; i++) {
		buffers.push_back(sf::SoundBuffer());
		buffers[buffers.size() - 1].loadFromFile("Source/resources/Audio/" + filenames[i]);
	}
	sound.setBuffer(buffers[0]);

	// Load Textures for the Objects
	commonTexture.loadFromFile("Source/resources/objectsSheet.png");

	// Create the Astronomical Objects
	astro.push_back(std::unique_ptr<AstroObject>(new Sun(0, 0, 1900, sf::Color(255, 255, 0), 0)));
	
	// Set the name of the Sun
	setLoadingMessage("Generating the Sun");
	astro[0]->setName("Sun");
	astro[0]->setInhabitants(0);

	noPlanets = Functions::randomInt(7, 10);

	setLoadingMessage("Generating Planets");
	float rDist = 0;
	for (int i = 1; i < noPlanets; i++) {
		// Generate random Distance from the Sun, random Radius and random Orbital Phase
		if (i == 1)
			rDist += (float)Functions::randomInt(350000, 350000);
		else
			rDist += (float)Functions::randomInt(150000, 175000);
		float rR = (float)Functions::randomInt(300, 500);
		float angle = (float)Functions::randomFloat(0, PI * 2);
		
		// Create the Astro Object in the generated position
		astro.push_back(std::unique_ptr<AstroObject>(new Planet(-cos(angle) * rDist, -sin(angle) * rDist, rR, sf::Color(rand() % 256, rand() % 256, rand() % 256), Functions::randomFloat(0.005, 0.01))));
		
		// Create Common Textures
		astro[i]->createCommonObjects(&commonTexture);

		// Set number of Inhabitants
		astro[i]->setInhabitants(Functions::randomInt(10, 50));

		// Set the Music File
		//astro[i]->setAudio(&sounds[0]);

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

	noMoons = 0;

	// Genrate Moons
	setLoadingMessage("Generating Moons");
	for (int i = 1; i < noPlanets; i++) {
		rDist = 0;
		int noMoonsPlanet = Functions::randomInt(0, 3);
		for (int j = 1; j <= noMoonsPlanet; j++) {
			// Generate random Distance from the Sun, random Radius and random Orbital Phase
			if (j == 1) {
				rDist += Functions::randomInt(50000, 60000);
			} else {
				rDist += Functions::randomInt(40000, 50000);
			}
			float rR = Functions::randomInt(100, 150);
			float angle = Functions::randomFloat(0, PI * 2);
			int rCol = Functions::randomInt(0, 255);

			// Create the Astro Object in the generated position
			astro.push_back(std::unique_ptr<AstroObject>(new Moon(astro[i]->getX() - cos(angle) * rDist, astro[i]->getY() - sin(angle) * rDist, rR, sf::Color(rCol, rCol, rCol), Functions::randomFloat(0.005, 0.01))));

			noMoons++;

			// Create Common Textures
			astro[astro.size() - 1]->createCommonObjects(&commonTexture);

			// Set number of Inhabitants
			astro[astro.size() - 1]->setInhabitants(0);

			// Set the Parent Planet Number
			astro[astro.size() - 1]->setParentPlanet(i);

			// Increase the Angle to match the Direction of the Velocity Vector
			angle += PI / 2;

			// Calculate the Velocity needed to stay in Circular Orbit
			float aV = sqrt(astro[i]->getG() * astro[i]->getMass() / Functions::dist(astro[i]->getX(), astro[i]->getY(), astro[astro.size() - 1]->getX(), astro[astro.size() - 1]->getY()));

			// Set the velocity of the Astro Object
			astro[astro.size() - 1]->addVelocity(-cos(angle) * aV, -sin(angle) * aV);

			// Set the name of the Planets
			std::ifstream f;
			f.open("Source/resources/Gods.txt");
			if (f) {
				std::string n;
				for (int j = 0; j < Functions::randomInt(0, 2500); j++) {
					f >> n;
				}
				int k = 0;
				do {
					f >> n;
					k++;
				} while (n.size() > 10 && k < 100);
				f.close();
				astro[astro.size() - 1]->setName(n);
			}
		}
	}


	// Generate the end goal object between two random Planets
	setLoadingMessage("Creating Secret");
	int afterPlanet = Functions::randomInt(1, noPlanets - 2);

	// Generate random Distance from the Sun, random Radius and random Orbital Phase
	rDist = ( sqrt( pow(astro[afterPlanet]->getX(), 2) + pow(astro[afterPlanet]->getY(), 2) ) + sqrt( pow(astro[afterPlanet + 1]->getX(), 2) + pow(astro[afterPlanet + 1]->getY(), 2) ) ) / 2;
	float rR = (float)Functions::randomInt(50, 50);
	float angle = (float)Functions::randomFloat(0, PI * 2);

	// Create the Astro Object in the generated position
	astro.push_back(std::unique_ptr<AstroObject>(new AlienObject(-cos(angle) * rDist, -sin(angle) * rDist, rR, sf::Color::Black, 0)));

	// Create Common Textures
	astro[astro.size() - 1]->createCommonObjects(&commonTexture);

	// Set number of Inhabitants
	astro[astro.size() - 1]->setInhabitants(0);

	// Increase the Angle to match the Direction of the Velocity Vector
	angle += PI / 2;

	// Calculate the Velocity needed to stay in Circular Orbit
	float aV = sqrt(astro[0]->getG() * astro[0]->getMass() / Functions::dist(astro[0]->getX(), astro[0]->getY(), astro[astro.size() - 1]->getX(), astro[astro.size() - 1]->getY()));

	// Set the velocity of the Astro Object
	astro[astro.size() - 1]->addVelocity(-cos(angle) * aV, -sin(angle) * aV);

	// Set the name of the Planets
	astro[astro.size() - 1]->setName("Unknown");



	setLoadingMessage("Creating the Ship");
	// Add Ships
	ships.push_back(std::unique_ptr<Ship>(new Ship(astro[1]->getX(), astro[1]->getY() - astro[1]->getRadius(), (float)(screen.width / 2), (float)(screen.height / 2))));

	// Set the closest Planet to the Ship
	ships[0]->setClosestPlanet(1);

	setLoadingMessage("Creating Player");
	// Add Human
	humanTexture.loadFromFile("Source/resources/humanSheet.png");
	human = std::unique_ptr<Human>(new Human(0, 0, &humanTexture));
	human->setColour(sf::Color::White);

	setLoadingMessage("Creating the UI");
	// Add Velocity Vector
	velocityVector = std::unique_ptr<VelocityVector>(new VelocityVector(screen));
	velocityVector -> setFont(font);

	// Add Distance To Object
	distanceObject = std::unique_ptr<DistanceToObject>(new DistanceToObject(screen, font));

	// Add Thrust
	thrust = std::unique_ptr<Thrust>(new Thrust(screen, font));

	// Add Fuel
	fuel = std::unique_ptr<Fuel>(new Fuel(screen, font));

	// Add Info Panel
	infoPanel = std::unique_ptr<InfoPanel>(new InfoPanel(screen, font));

	// Add Message
	message = std::unique_ptr<Message>(new Message(screen, font));

	shipTexture.loadFromFile("Source/resources/shipSheet.png");

	// Add Shop
	shop = std::unique_ptr<Shop>(new Shop(screen, font, &shipTexture));

	// Add Console
	console = std::unique_ptr<Console>(new Console(screen, font));

	// Pixels Per Meter
	ppm = 0.05;

	// FrameRate Settings
	frameRate.setFont(font);
	frameRate.setPosition(screen.width / 2, 0);
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

	//for (unsigned int i = 0; i < 200; i++) {
	//	stars[i][0] = Functions::randomInt(0, screen.width);
	//	stars[i][1] = Functions::randomInt(0, screen.height);
	//	stars[i][2] = Functions::randomInt(1, 3);
	//}

	// Menu Flags
	menu["map"] = false;
	menu["infoPanel"] = true;
	menu["thrust"] = true;
	menu["fuel"] = true;
	menu["distance"] = true;
	menu["velocity"] = true;
	menu["shop"] = false;
	menu["quests"] = false;
	menu["console"] = false;
	menu["exit"] = false;

	//ppm = dist(0, 0, astro[noPlanets - 1] -> getX(), astro[noPlanets - 1] -> getY()) / (screen.height / 2);

	setLoadingMessage("Creating Map");
	// Create an Astro Map
	astroMap = std::unique_ptr<AstroMap>(new AstroMap((float)(Functions::dist(0, 0, astro[noPlanets - 1]->getX(), astro[noPlanets - 1]->getY()) / (screen.height / 2.2)), font));
	astroMap -> setShip(ships[0]->getX(), ships[0]->getY());
	for (unsigned i = 0; i < astro.size() - 1; i++) {
		astroMap -> addAstro(screen, astro[i] -> getX(), astro[i] -> getY(), astro[i] -> getColour(), astro[i] -> getRadius());
		if (i >= noPlanets) {
			astroMap -> setParent(i, astro[i]->getParentPlanet());
		} else {
			astroMap -> setParent(i, 0);
		}
	}
	astroMap -> setNoPlanets(noPlanets);

	// Unset the Target Object
	targetAstro = -1;

	// Set the player mode
	onPlanet = false;

	// Set the Human's state
	jump = false;

	gameOver = false;

	closestPlanet = 1;

	setLoadingMessage("Getting Item Names");
	std::ifstream f;
	f.open("Source/resources/QuestItems.txt");
	int goodsNo;
	f >> goodsNo;
	for (int i = 0; i < goodsNo; i++) {
		std::string item;
		std::getline(f, item);
		if (i != 0)
			goods.push_back(item);
	}
	f.close();

	setLoadingMessage("Creating Locals");
	// Create Vector to store the Locals
	int totalReward = 0;
	for (int i = 0; i < 100; i++) {
		locals.push_back(std::unique_ptr<Human>(new Human(0, 0, &humanTexture)));
		int cP = closestPlanet;
		float theta = Functions::randomFloat(0, 2 * PI);
		locals[i]->setX(astro[cP]->getX() - cos(theta) * astro[cP]->getRadius());
		locals[i]->setY(astro[cP]->getY() - sin(theta) * astro[cP]->getRadius());

		if (i % 5 == 0 && i < astro[closestPlanet]->getInhabitants()) {
			//locals[i]->setQuest(0, Functions::randomInt(0, goods.size() - 1), Functions::randomInt(2, 20), Functions::randomInt(1, noPlanets - 1), Functions::randomInt(100, 1000));
			int reward = Functions::randomInt(100, 300);
			locals[i]->setQuest(0, Functions::randomInt(0, goods.size() - 1), 2, 1, reward);
			totalReward += reward;
		}
	}
	shop->setPrice(0, totalReward - Functions::randomInt(0, 75));

	setLoadingMessage("Generating Background Stars");
	// Star Field - generate stars
	bRenderTexture.create(screen.width, screen.height);
	bRenderTexture.clear(sf::Color::Black);

	int numStars = Functions::randomInt(100, 200);
	for (int i = 0; i < numStars; i++) {
		float xStar, yStar;
		//if (Functions::randomInt(0, 3) == 0) {
		//	xStar = Functions::randomFloat(screen.width / 4, screen.width - screen.width / 4);
		//	yStar = Functions::randomFloat(screen.height / 4, screen.height - screen.height / 4);
		//}
		//else {
			xStar = Functions::randomInt(0, screen.width);
			yStar = Functions::randomInt(0, screen.height);
		//}
		float rStar = 1; //Functions::randomFloat(1, 1);
		sf::CircleShape c(rStar);
		c.setPosition(xStar, yStar);
		//c.setPosition(xStar - 20, yStar - 20);
		//c.setPointCount(100);
		bRenderTexture.draw(c);
	}

	bRenderTexture.display();
	bTexture = bRenderTexture.getTexture();

	background.setSize(sf::Vector2f(screen.width, screen.height));
	background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
	background.setPosition(screen.width / 2, screen.height / 2);
	background.setTexture(&bTexture);

	noSpeedLines = 0;

	money = 0;

	setLoadingMessage("Generating More UI");
	moneyText.setFont(font);
	moneyText.setCharacterSize(15);
	moneyText.setString("Money: " + Functions::toStringWithComma(money) + " $");
	//moneyText.setOrigin(moneyText.getLocalBounds().width / 2, moneyText.getLocalBounds().height / 2);
	moneyText.setPosition(0, 0);
	//moneyText.setPosition(moneyText.getGlobalBounds().width / 2, moneyText.getGlobalBounds().height / 2);

	cargoText.setFont(font);
	cargoText.setCharacterSize(15);
	cargoText.setString("Cargo: " + Functions::toStringWithComma(ships[0]->getCargo()) + " / " + Functions::toStringWithComma(ships[0]->getMaxCargo()));
	cargoText.setPosition(screen.width, 0);
	cargoText.setOrigin(cargoText.getLocalBounds().width, 0);

	//questBackground.setFillColor(sf::Color(0, 0, 0, 150));
	//questBackground.setPosition(screen.width / 10, screen.height / 10);
	//questBackground.setSize(sf::Vector2f(screen.width - 2 * questBackground.getPosition().x, screen.height - 2 * questBackground.getPosition().y));
	//questBackground.setOutlineThickness(1);
	//questBackground.setOutlineColor(sf::Color::White);

	questRect[0].setFillColor(sf::Color(0, 0, 0, 150));
	questRect[0].setPosition(screen.width / 5, screen.height / 5);
	questRect[0].setSize(sf::Vector2f(screen.width - 2 * questRect[0].getPosition().x, (screen.height - 2 * questRect[0].getPosition().y) / 10));
	questRect[0].setOutlineThickness(1);
	questRect[0].setOutlineColor(sf::Color::White);
	for (int i = 1; i < 10; i++) {
		questRect[i].setFillColor(sf::Color(0, 0, 0, 150));
		questRect[i].setPosition(questRect[0].getPosition().x, questRect[0].getPosition().y + i * questRect[0].getSize().y);
		questRect[i].setSize(sf::Vector2f(screen.width - 2 * questRect[0].getPosition().x, (screen.height - 2 * questRect[0].getPosition().y) / 10));
		questRect[i].setOutlineThickness(1);
		questRect[i].setOutlineColor(sf::Color::White);
	}

	for (int i = 0; i < 10; i++) {
		questDesc[i].setFont(font);
		questDesc[i].setCharacterSize(20);
		questDesc[i].setString("Quest Description");
		questDesc[i].setOrigin(questDesc[i].getLocalBounds().width / 2, questDesc[i].getLocalBounds().height / 2);
		questDesc[i].setPosition(screen.width / 2, questRect[i].getPosition().y + questRect[i].getSize().y / 2);
	}

	startQuest = 0;
	consoleInput = "";

	scrollBar.setFillColor(sf::Color(127, 127, 127));
	scrollBar.setPosition(questRect[0].getPosition().x + questRect[0].getSize().x, questRect[0].getPosition().y);
	scrollBar.setSize(sf::Vector2f(questRect[0].getSize().y / 2, questRect[0].getSize().y * 10));
	scrollBar.setOutlineThickness(1);

	scrollBarBg.setFillColor(sf::Color::Transparent);
	scrollBarBg.setPosition(scrollBar.getPosition().x, scrollBar.getPosition().y);
	scrollBarBg.setSize(scrollBar.getSize());
	scrollBarBg.setOutlineThickness(1);

	astroType = 0;

	//window.setMouseCursorVisible(false);

	// Initial Settings when the Player Exits the Ship
	onPlanet = true;
	float theta = Functions::randomFloat(0, 2 * PI);
	human->setX(astro[closestPlanet]->getX() + sin(theta) * astro[closestPlanet]->getRadius());
	human->setY(astro[closestPlanet]->getY() - cos(theta) * astro[closestPlanet]->getRadius());

	scroll = 0;
	curScroll = 0;
	tutorialStep = 0;
	tutColour = sf::Color::White;
	resetConditions();

	setLoadingMessage("Starting");
}

Game::~Game() {
	window.close();
}

int Game::getStop() {
	return stop;
}

void Game::disableMenus() {
	for (auto el = menu.begin(); el != menu.end(); el++) {
		menu[el->first] = false;
	}
}

void Game::resetConditions() {
	for (int i = 0; i < 5; i++)	
		tutCond[i] = false;
}

void Game::events() {
	//scroll = 0;
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			// Close the Window
			window.close();
			break;
		case sf::Event::KeyPressed:
			// Close the Window if Escape is pressed
			if (event.key.code == sf::Keyboard::Escape) {
				if (menu["quests"] || menu["map"] || menu["shop"] || menu["console"]) {
					menu["quests"] = false;
					menu["map"] = false;
					menu["shop"] = false;
					menu["console"] = false;
				} else {
					menu["exit"] = !menu["exit"];
				}
			}
			
			if (!onPlanet && !ships[0]->getLanded() && !menu["console"]) {
				if (event.key.code == sf::Keyboard::T) {
					float tDist = distanceObject->getTargetAngle() - PI / 2;
					tDist = tDist < 0 ? 2 * PI + tDist : tDist;
					float leftRotate = ships[0]->getAngle() - tDist;
					ships[0]->setLeftRotate(leftRotate * 180 / PI);
				}

				if (event.key.code == sf::Keyboard::R) {
					float tDist = distanceObject->getTargetAngle() - PI / 2 + PI;
					tDist = tDist < 0 ? 2 * PI + tDist : tDist;
					//std::cout << tDist * 180 / PI << " " << ships[0]->getAngle() * 180 / PI << std::endl;
					float leftRotate = ships[0]->getAngle() - tDist;
					ships[0]->setLeftRotate(leftRotate * 180 / PI);
				}
			}

			// ~ - Console
			if (event.key.code == 54) {
				menu["console"] = !menu["console"];
			}

			if (!menu["console"]) {
				// M - Open Map
				if (event.key.code == 12) {
					menu["map"] = !menu["map"];
				}

				// E - Exit / Enter
				if (event.key.code == 4 && !menu["quests"] && !gameOver && !human->getOnHoverboard()) {

					if (!onPlanet && ships[0]->getLanded()) {
						// Initial Settings when the Player Exits the Ship
						onPlanet = true;
						int cP = ships[0]->getClosestPlanet();
						float dy = astro[cP]->getY() - ships[0]->getY();
						float dx = astro[cP]->getX() - ships[0]->getX();
						float theta = atan2(dy, dx);
						theta = theta >= 0 ? theta : theta + 2 * PI;
						//theta += 0.01;
						human->setX(astro[cP]->getX() - cos(theta) * astro[cP]->getRadius());
						human->setY(astro[cP]->getY() - sin(theta) * astro[cP]->getRadius());
					}
					else if (onPlanet && ships[0]->getVisible() && Functions::dist(human->getX(), human->getY(), ships[0]->getX(), ships[0]->getY()) < 20 * 0.15) {
						onPlanet = false;
					}

					int cS = human->getClosestSpecial();
					if (cS != -1) {
						sound.setBuffer(buffers[1]);
						sound.play();
						switch (astro[closestPlanet]->getType(human->getClosestSpecial())) {
							case 0:
								ships[0]->refuel();
								break;
							case 1:
								ships[0]->addMaxFuel(10000);
								astro[closestPlanet]->setInactive(cS);
								break;
							case 2:
								ships[0]->addMaxThrust(10);
								astro[closestPlanet]->setInactive(cS);
								break;
							case 3:
								ships[0]->addMaxVelocity(0.5);
								astro[closestPlanet]->setInactive(cS);
								break;
							case 4:
								ships[0]->setMaxCargo(ships[0]->getMaxCargo() + 50);
								cargoText.setString("Cargo: " + Functions::toStringWithComma(ships[0]->getCargo()) + " / " + Functions::toStringWithComma(ships[0]->getMaxCargo()));
								cargoText.setOrigin(cargoText.getLocalBounds().width, 0);
								astro[closestPlanet]->setInactive(cS);
								break;
							case 10:
								menu["shop"] = !menu["shop"];
							default:
								break;
						}
						cS = -1;
					}

					// Accept or Return Quest
					if (human->getClosestLocal() != -1) {
						int closestLocal = human->getClosestLocal();
						if (locals[closestLocal]->getHasQuest() && quests.size() < 99) {
							// Accept Quest
							if (ships[0]->getCargo() + locals[closestLocal]->getQuest()->getNoItems() <= ships[0]->getMaxCargo()) {
								// Store the Quest
								quests.push_back(locals[closestLocal]->getQuest());
								
								// Update Cargo
								ships[0]->setCargo(ships[0]->getCargo() + locals[closestLocal]->getQuest()->getNoItems());
								cargoText.setString("Cargo: " + Functions::toStringWithComma(ships[0]->getCargo()) + " / " + Functions::toStringWithComma(ships[0]->getMaxCargo()));
								cargoText.setOrigin(cargoText.getLocalBounds().width, 0);
								locals[closestLocal]->setHasQuest(false);

								// Return on Same Planet
								if (closestPlanet == quests[quests.size() - 1]->getDestination()) {
									for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
										if (i != closestLocal && !locals[i]->getHasQuest() && !locals[i]->getHasReturn()) {
											locals[i]->setReturnQuest(quests.size() - 1);
											break;
										}
									}
								}
								
								// Play Sound
								sound.setBuffer(buffers[0]);
								sound.play();
							} else {
								// Play Error Sound
								sound.setBuffer(buffers[3]);
								sound.play();
							}
						} else if (locals[closestLocal]->getHasReturn()) {
							// Return Quest
							int returnQuest = locals[closestLocal]->getReturnQuest();

							// Update Money
							money += quests[returnQuest]->getReward();
							moneyText.setString("Money: " + Functions::toStringWithComma(money) + " $");

							// Update Cargo
							ships[0]->setCargo(ships[0]->getCargo() - quests[returnQuest]->getNoItems());
							cargoText.setString("Cargo: " + Functions::toStringWithComma(ships[0]->getCargo()) + " / " + Functions::toStringWithComma(ships[0]->getMaxCargo()));
							cargoText.setOrigin(cargoText.getLocalBounds().width, 0);
							for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
								if (locals[i]->getHasReturn() && locals[i]->getReturnQuest() > returnQuest) {
									locals[i]->setReturnQuest(locals[i]->getReturnQuest() - 1);
								}
							}

							// Remove the Quest
							quests.erase(quests.begin() + returnQuest);
							locals[closestLocal]->setHasReturn(false);

							// Play Sound
							sound.setBuffer(buffers[1]);
							sound.play();
						}
					}

					//if (onPlanet) {
					//	int cP = ships[0]->getClosestPlanet();
					//	float dy = astro[cP]->getY() - ships[0]->getY();
					//	float dx = astro[cP]->getX() - ships[0]->getX();
					//	float theta = atan2(dy, dx);
					//	theta = theta >= 0 ? theta : theta + 2 * PI;
					//	//theta += 0.01;
					//	human->setX(astro[cP]->getX() - cos(theta) * astro[cP]->getRadius());
					//	human->setY(astro[cP]->getY() - sin(theta) * astro[cP]->getRadius());
					//}
				}

				// F - Set Ship Straight
				if (event.key.code == 5 && onPlanet && !gameOver) {
					// Get the Angle between the Ship and the Object
					float dy = astro[closestPlanet]->getY() - ships[0]->getY();
					float dx = astro[closestPlanet]->getX() - ships[0]->getX();
					float theta = atan2(dy, dx);
					theta = theta >= 0 ? theta : theta + 2 * PI;
					theta -= PI / 2;
					float curTheta = ships[0]->getRotation();

					float dif1 = curTheta - theta;
					dif1 = dif1 < 0 ? dif1 + PI * 2 : dif1;
					float dif2 = theta - curTheta;
					dif2 = dif2 < 0 ? dif2 + PI * 2 : dif2;

					if (dif1 < dif2) {
						if (dif1 > 0.01) {
							//ships[0]->setLeftRotate(dif1 * 180 / PI);
							ships[0]->setLeftRotate(1);
						}
					}
					else {
						if (dif2 > 0.01) {
							//ships[0]->setLeftRotate(-dif2 * 180 / PI);
							ships[0]->setLeftRotate(-1);
						}
					}

					//if (abs(curTheta - theta) < abs(theta - curTheta)) {
					//	ships[0]->setLeftRotate(-(curTheta - theta) * 180 / PI);
					//} else {
					//	ships[0]->setLeftRotate(-(theta - curTheta) * 180 / PI);
					//}
				}

				// H - Hoverboard
				if (event.key.code == sf::Keyboard::H) {
					human->setOnHoverboard(!human->getOnHoverboard());
				}

				// Q - Quest Menu
				if (event.key.code == 16) {
					menu["quests"] = !menu["quests"];
					if (!menu["quests"]) {
						startQuest = 0;
					}
				}

				// X - Cut Thrust
				if (event.key.code == 23 && !gameOver) {
					ships[0]->cutThrust();
				}

				// I - Toggle Inertia Damper
				if (event.key.code == 8 && !gameOver) {
					ships[0]->setInertiaDamper(!ships[0]->getInertiaDamper());
					if (ships[0]->getInertiaDamper())
						idText.setString("Inertia Damper: ON");
					else
						idText.setString("Inertia Damper: OFF");
				}

				// Up Arrow
				if (event.key.code == 73 && startQuest > 0 && quests.size() > 10) {
					startQuest--;
					//if (startQuest < 0)
						//startQuest = 0;
				}

				// Down Arrow
				if (event.key.code == 74 && startQuest < quests.size() - 10 && quests.size() > 10) {
					startQuest++;
					//if (startQuest > quests.size() - 1)
						//startQuest = quests.size() - 1;
				}

				// Exit
				if ((event.key.code == sf::Keyboard::Return && menu["exit"]) || (event.key.code == sf::Keyboard::Escape && gameOver)) {
					stop = 1;
				}

				// 0
				if (event.key.code == 26) {
					if (!menu["distance"] && !menu["velocity"] && !menu["infoPanel"] && !menu["thrust"] && !menu["fuel"]) {
						menu["distance"] = true;
						menu["velocity"] = true;
						menu["infoPanel"] = true;
						menu["thrust"] = true;
						menu["fuel"] = true;
					}
					else {
						menu["distance"] = false;
						menu["velocity"] = false;
						menu["infoPanel"] = false;
						menu["thrust"] = false;
						menu["fuel"] = false;
					}
				}

				// 1
				if (event.key.code == 27) {
					menu["distance"] = !menu["distance"];
				}

				// 2
				if (event.key.code == 28) {
					menu["velocity"] = !menu["velocity"];
				}

				// 3
				if (event.key.code == 29) {
					menu["infoPanel"] = !menu["infoPanel"];
				}

				// 4
				if (event.key.code == 30) {
					menu["thrust"] = !menu["thrust"];
				}

				// 5
				if (event.key.code == 31) {
					menu["fuel"] = !menu["fuel"];
				}

				//window.close();
				// Set the pressed key
				keys[event.key.code] = 1;
				//std::cout << "Key Pressed: " << event.key.code << std::endl;
			}
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
			if (!menu["quests"]) {
				//ppm -= event.mouseWheel.delta * 0.05;
				scroll = event.mouseWheel.delta * Functions::map(ppm, 0.05, 1, 0.03, 0.5);
				curScroll = 0;
				/*if (ppm <= 0.05)
					ppm = 0.05f;
				if (ppm > 1)
					ppm = 1;*/
			} else {
				if (event.mouseWheel.delta > 0 && startQuest > 0 && quests.size() > 10)
					startQuest--;
				if (event.mouseWheel.delta < 0 && startQuest < quests.size() - 10 && quests.size() > 10)
					startQuest;
					
				//if (startQuest < 0)
				//	startQuest = 0;
				//if (startQuest > quests.size() - 1)
				//	startQuest = quests.size() - 1;
			}
			break;
		case sf::Event::TextEntered:
			if (menu["console"] && event.text.unicode < 128 && event.text.unicode != '`') {
				if (event.text.unicode == '\b') {
					if (consoleInput.size() > 0)
						consoleInput.erase(consoleInput.size() - 1, 1);
				} else if (event.text.unicode == '\n' || event.text.unicode == '\r') {
					executeCommand(consoleInput);
					consoleInput = "";
				} else {
					consoleInput += event.text.unicode;
				}
			}
		default:
			break;
		}
	}
}

void Game::setLoadingMessage(std::string m) {
	loadingState++;
	loadStatus.setSize(sf::Vector2f(Functions::map(loadingState, 0, 15, 0, loadingBar.getSize().x), loadingBar.getSize().y));
	loadingMessage.setString(m);
	loadingMessage.setOrigin(loadingMessage.getLocalBounds().width / 2, loadingMessage.getLocalBounds().height / 2);
	window.clear(sf::Color::Black);
	window.draw(loadingBar);
	window.draw(loadStatus);
	window.draw(loadingMessage);
	window.display();
}

void Game::keyPressed() {
	float speedMult = 1;
	// Shift
	if (keys[38] && !human->getOnHoverboard()) {
		speedMult = 2;
		human->setSpeed(0.5);
	} else {
		if (human->getOnHoverboard()) {
			speedMult = 10;
			human->setSpeed(0.2);
		} else {
			human->setSpeed(1);
		}
	}

	// +
	if (keys[68]) {
		float s = 1;
		// Increase Zoom Speed
		if (keys[37]) {
			s = 100;
		}
		ppm += (float)(0.01 * s);
		if (ppm > 1)
			ppm = 1;
	}

	// -
	if (keys[67]) {
		float s = 1;
		// Increase Zoom Speed
		if (keys[37]) {
			s = 100;
		}
		ppm -= (float)(0.01 * s);
		if (ppm <= 0.05)
			ppm = 0.05f;
		//if (ppm <= 0)
			//ppm = 0.01f;

	}

	// W
	if (keys[22] && !onPlanet && !gameOver) {
		ships[0]->addVelocity();
		//ships[0]->setAccelerating(true);
	}

	// S
	if (keys[18] && !onPlanet && !gameOver) {
		ships[0]->subVelocity();
		//ships[0]->setAccelerating(true);
		//ships[0]->setLanded(false);
	}

	bool moved = false;

	// A
	if (keys[0] && !gameOver) {
		if (!onPlanet) {
			// Ship
			ships[0]->addRotation(-0.05f);
		} else {
			// Human
			float f;
			if (!human->getJump()) {
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
	if (keys[3] && !gameOver) {
		if (!onPlanet) {
			// Ship
			ships[0]->addRotation(0.05f);
		} else {
			// Human
			float f;
			if (!human->getJump()) {
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
	if (!moved && !human->getJump()) {
		human->resetSprite();
	}

	// Reset the Sprite if the Human is not mid air and is on the Hoverboard
	if (human->getOnHoverboard() && !human->getJump()) {
		human->resetSprite();
	}

	// If the human moved play footsteps
	if (moved && !human->getJump()) {
		human->playSound();
	}

	// SPACE
	if (keys[57]) {
		if (onPlanet) {
			if (!human->getJump() && !human->getOnHoverboard()) {
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
				human->setJump(true);
				//jump = true;

				// Add the Velocity that is caused by the Rotation of the Object to the Human
				double circumference = (double)(2.0f * (double)PI * (double)astro[cP]->getRadius());
				double velVect = (double)Functions::map((double)astro[cP]->getRotation(), 0, 358.75, 0, circumference);
				human->addVelocity(-cos(theta + (double)PI / 2) * (double)velVect, -sin(theta + (double)PI / 2) * (double)velVect);
			}
		}
	}
}

void Game::executeCommand(std::string command) {
	std::string com;
	int pos;

	com = "GoToAstro ";
	pos = command.find(com);
	if (pos == 0 && command.size() > com.size()) {
		int i;
		int astroNum = 0;
		for (i = com.size(); i < command.size() && command[i] >= '0' && command[i] <= '9'; i++) {
			astroNum = astroNum * 10 + (command[i] - '0');
		}
		if (i == command.size() && astroNum > -1 && astroNum < astro.size()) {
			onPlanet = false;
			ships[0]->setX(astro[astroNum]->getX());
			ships[0]->setY(astro[astroNum]->getY() - astro[astroNum]->getRadius());
		}
	}

	com = "AddMoney ";
	pos = command.find(com);
	if (pos == 0 && command.size() > com.size()) {
		int i;
		int mon = 0;
		for (i = com.size(); i < command.size() && command[i] >= '0' && command[i] <= '9'; i++) {
			mon = mon * 10 + (command[i] - '0');
		}
		if (i == command.size()) {
			money += mon;
			moneyText.setString("Money: " + Functions::toStringWithComma(money) + " $");
			//moneyText.setOrigin(moneyText.getLocalBounds().width / 2, moneyText.getLocalBounds().height / 2);
		}
	}

	com = "GoToShip";
	if (command.compare(com) == 0) {
		onPlanet = false;
	}

	com = "RefuelShip";
	if (command.compare(com) == 0) {
		ships[0]->refuel();
	}

	com = "exit";
	if (command.compare(com) == 0) {
		stop = 1;
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
				// Check if it's Game Over
				if (getRelativeVelocity() > ships[0]->getMaxVelocity() && !gameOver) {
					gameOver = true;
					sound.setBuffer(buffers[2]);
					sound.play();
				}

				// Get the Angle between the Ship and the Object
				float dy = astro[i]->getY() - ships[j]->getY();
				float dx = astro[i]->getX() - ships[j]->getX();
				float theta = atan2(dy, dx);
				theta = theta >= 0 ? theta : theta + 2 * PI;

				//if (!ships[j]->getLanded()) {
				//	ships[j]->setStraight(theta - PI / 2);
				//}

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

			if (!human->getJump())
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
			human->setJump(false);
			//jump = false;
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

void Game::nearObjects() {
	if (onPlanet) {
		if (Functions::dist(human->getX(), human->getY(), ships[0]->getX(), ships[0]->getY()) < 20 * 0.15 && ships[0]->getVisible()) {
			message->update("Press \'E\' to Enter the Ship");
		}

		int specialIndex = astro[closestPlanet]->getNearSpecial(human->getX(), human->getY());
		if (specialIndex != -1) {
			switch (astro[closestPlanet]->getType(specialIndex)) {
				case 0:
					message->update("Press \'E\' to Refuel");
					break;
				case 1:
					message->update("Press \'E\' to Increase the Maximum Fuel");
					break;
				case 2:
					message->update("Press \'E\' to Increase the Maximum Thrust");
					break;
				case 3:
					message->update("Press \'E\' to Increase the Durability");
					break;
				case 4:
					message->update("Press '\E\' to Increase Cargo Space");
					break;
				case 10:
					message->update("Press \'E\' to Enter Shop");
					break;
				default:
					message->update("Allan please add details");
					break;
			}
			
			human->setClosestSpecial(specialIndex);
		} else {
			human->setClosestSpecial(-1);
		}

		human->setClosestLocal(-1);
		for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
			// Close to a person with a Quest
			if (Functions::dist(view.x, view.y, locals[i]->getX(), locals[i]->getY()) < 40 * ppm) {
				if (locals[i]->getHasQuest()) {
					std::unique_ptr<Quest> quest = locals[i]->getQuest();
					std::string m;
					switch (quest->getType()) {
						case 0:
							m = "Deliver " + std::to_string(quest->getNoItems()) + " " + goods[quest->getItem()] + " to " + astro[quest->getDestination()]->getName();
							m += "\nReward: " + std::to_string(quest->getReward()) + " $";
							m += "\nPress \'E\' to accept";
							break;
						default:
							break;
					}
					message->update(m, sf::Color::Green);
					human->setClosestLocal(i);
					locals[i]->setState(0);
				} else if (locals[i]->getHasReturn()) {
					int questNo = locals[i]->getReturnQuest();
					std::string m;
					switch (quests[questNo]->getType()) {
						case 0:
							m = "Press \'E\' to deliver " + std::to_string(quests[questNo]->getNoItems()) + " " + goods[quests[questNo]->getItem()];
							m += "\nReward: " + std::to_string(quests[questNo]->getReward()) + "$";
						default:
							break;
					}
					message->update(m, sf::Color::Cyan);
					human->setClosestLocal(i);
					locals[i]->setState(0);
				}
			}
		}
	}

	if (!onPlanet) {
		if (Functions::dist(ships[0]->getX(), ships[0]->getY(), astro[closestPlanet]->getX(), astro[closestPlanet]->getY()) - astro[closestPlanet]->getRadius() - 20 * 0.15 < 1000 && getRelativeVelocity() > ships[0]->getMaxVelocity()) {
			message->update("WARNING! HIGH SPEED!", sf::Color::Red);
			if (sound.getBuffer() != &buffers[4] || sound.getStatus() != sf::Sound::Playing) {
				sound.setBuffer(buffers[4]);
				sound.setLoop(true);
				sound.play();
			}
		} else if (sound.getBuffer() == &buffers[4]) {
			sound.setLoop(false);
			sound.stop();
		}
	}
}

double Game::getRelativeVelocity() {
	return sqrt( pow( ships[0]->getVelocity().x - astro[closestPlanet]->getVelocity().x, 2 ) + pow( ships[0]->getVelocity().y - astro[closestPlanet]->getVelocity().y, 2 ) );
}

double Game::getRelativeVelocity(int index) {
	return sqrt( pow( ships[0]->getVelocity().x - astro[index]->getVelocity().x, 2) + pow(ships[0]->getVelocity().y - astro[index]->getVelocity().y, 2 ) );
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
		for (unsigned int i = 1; i < noPlanets; i++) {
			astro[i]->setForce(astro[0]->getG() * astro[0]->getMass() * astro[i]->getMass() / pow(Functions::dist(astro[0]->getX(), astro[0]->getY(), astro[i]->getX(), astro[i]->getY()), 2));

			// Angle between the Sun and the Planets
			float dy = astro[i]->getY() - astro[0]->getY();
			float dx = astro[i]->getX() - astro[0]->getX();
			float theta = atan2(dy, dx);
			theta = theta >= 0 ? theta : theta + 2 * PI;
			astro[i]->setDirection(-cos(theta), -sin(theta));
		}

		// Apply Force to the Moons
		for (unsigned int i = noPlanets; i < noPlanets + noMoons; i++) {
			int parent = astro[i]->getParentPlanet();
			astro[i]->setForce(astro[parent]->getG() * astro[parent]->getMass() * astro[i]->getMass() / pow(Functions::dist(astro[parent]->getX(), astro[parent]->getY(), astro[i]->getX(), astro[i]->getY()), 2));

			// Angle between the Planets and the Moons
			float dy = astro[i]->getY() - astro[parent]->getY();
			float dx = astro[i]->getX() - astro[parent]->getX();
			float theta = atan2(dy, dx);
			theta = theta >= 0 ? theta : theta + 2 * PI;
			astro[i]->setDirection(-cos(theta), -sin(theta));
		}

		// Find the closest Object
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
			if (stateTime.getElapsedTime().asSeconds() > locals[i]->getNextStateChange() && i != human->getClosestLocal()) {
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

		// Check for Near Objects
		message->hide();
		if (!human->getOnHoverboard()) {
			nearObjects();
		} else {
			human->setClosestSpecial(-1);
			human->setClosestLocal(-1);
		}

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
			float returnIndex = 0;
			closestPlanet = ships[0]->getClosestPlanet();
			for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
				int cP = closestPlanet;
				float theta = Functions::randomFloat(0, 2 * PI);
				locals[i]->setX(astro[cP]->getX() - cos(theta) * astro[cP]->getRadius());
				locals[i]->setY(astro[cP]->getY() - sin(theta) * astro[cP]->getRadius());

				locals[i]->setHasQuest(false);
				locals[i]->setHasReturn(false);

				while (returnIndex < quests.size()) {
					if (quests[returnIndex]->getDestination() == closestPlanet) {
						locals[i]->setReturnQuest(returnIndex);
						returnIndex++;
						break;
					}
					returnIndex++;
				}

				if (returnIndex == quests.size()) {
					if (Functions::randomInt(0, 3) == 0) {
						locals[i]->setQuest(0, Functions::randomInt(0, goods.size() - 1), Functions::randomInt(2, 20), Functions::randomInt(1, noPlanets - 1), Functions::randomInt(100, 1000));
					}
				}
			}
			music[0].stop();
			music[1].stop();
			if (closestPlanet < noPlanets) {
				astroType = 0;
			} else {
				astroType = 1;
			}
			music[astroType].setVolume(0);
			music[astroType].setLoop(true);
			music[astroType].play();
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
			for (unsigned i = 0; i < astro.size() - 1; i++) {
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

		// Info Panel
		float relToTarget;
		if (targetAstro != -1) {
			relToTarget = getRelativeVelocity(targetAstro);
		} else {
			relToTarget = -1;
		}
		infoPanel->update(idText.getString(), ships[0]->getThrust(), ships[0]->getMaxThrust(), ships[0]->getFuel(), ships[0]->getMaxFuel(), (float)sqrt( pow( ships[0]->getVelocity().x, 2 ) + pow( ships[0]->getVelocity().y, 2 ) ), getRelativeVelocity(),  relToTarget, ships[0]->getMaxVelocity(), ships[0]->getCargo(), ships[0]->getMaxCargo());

		if (menu["shop"]) {
			int shopStatus = shop->update(window);
			if (shopStatus <= 100 && shopStatus >= 0) {
				// Use Item
				ships[0]->setShip(shopStatus);
			}
			if (shopStatus > 100) {
				if (money >= shopStatus) {
					money -= shopStatus;
					moneyText.setString("Money: " + Functions::toStringWithComma(money) + " $");
					//moneyText.setOrigin(moneyText.getLocalBounds().width / 2, moneyText.getLocalBounds().height / 2);
					shop->confirmPurchase();
				}
			}
		}

		//float vel = sqrt(pow(ships[0]->getVelocity().x, 2) + pow(ships[0]->getVelocity().y, 2));
		//ppm = Functions::map(vel, 0, 50, 0.1, 1);

		//// Create Speed Lines
		//float vel = sqrt(pow(ships[0]->getVelocity().x, 2) + pow(ships[0]->getVelocity().y, 2));
		//if (vel > 1 && !onPlanet && lastSpeedLine.getElapsedTime().asSeconds() > 1) {
		//	noSpeedLines = 5;
		//	lastSpeedLine.restart();
		//}
		//if (noSpeedLines > 0) {
		//	float velAngle = atan2(ships[0]->getVelocity().y, ships[0]->getVelocity().x);
		//	velAngle = velAngle >= 0 ? velAngle : velAngle + 2 * PI;
		//	velAngle += PI / 2;
		//	speedLines.push_back(std::unique_ptr<SpeedLine>(new SpeedLine(screen, velAngle, Functions::map(vel, 0, 299792458, 10, 10))));
		//	noSpeedLines--;
		//}

		//// Speed Lines
		//for (int i = 0; i < speedLines.size(); i++) {
		//	speedLines[i]->update();
		//}

		//// Remove Speed Lines
		//for (int i = speedLines.size() - 1; i >= 0; i--) {
		//	if (!speedLines[i]->getIsAlive()) {
		//		speedLines.erase(speedLines.begin() + i);
		//	}
		//}

		if (menu["quests"]) {
			for (int i = 0; i < 10; i++) {
				std::string desc;
				if (startQuest + i < quests.size()) {
					desc = "Deliver " + std::to_string(quests[startQuest + i]->getNoItems()) + " " + goods[quests[startQuest + i]->getItem()] + " to " + astro[quests[startQuest + i]->getDestination()]->getName() + " (" + std::to_string(quests[startQuest + i]->getReward()) + "$)";
					if (quests[startQuest + i]->getDestination() == closestPlanet) {
						questDesc[i].setStyle(sf::Text::Bold);
					}
					else {
						questDesc[i].setStyle(sf::Text::Regular);
					}
				} else {
					desc = "";
				}
				questDesc[i].setString(desc);
				questDesc[i].setOrigin(questDesc[i].getLocalBounds().width / 2, questDesc[i].getLocalBounds().height / 2);
			}
			int dif = quests.size() - 10;
			dif = dif < 0 ? 0 : dif;
			scrollBar.setSize(sf::Vector2f(scrollBar.getSize().x, Functions::map(dif, 0, 89, questRect[0].getSize().y * 10, 1)));
			if (dif != 0)
				scrollBar.setPosition(scrollBar.getPosition().x, questRect[0].getPosition().y + startQuest * ((questRect[0].getSize().y * 10 - scrollBar.getSize().y) / dif));
		}

		if (menu["console"]) {
			console->update(consoleInput);
		}

		if (!onPlanet) {
			if (distanceObject->getHovered() && menu["distance"]) {
				message->update(distanceObject->getDescription(), sf::Color::Yellow);
			}

			if (infoPanel->getHovered() && menu["infoPanel"]) {
				message->update(infoPanel->getDescription(), sf::Color::Yellow);
			}

			if (thrust->getHovered() && menu["thrust"]) {
				message->update(thrust->getDescription(), sf::Color::Yellow);
			}

			if (fuel->getHovered() && menu["fuel"]) {
				message->update(fuel->getDescription(), sf::Color::Yellow);
			}

			if (velocityVector->getHovered() && menu["velocity"]) {
				message->update(velocityVector->getDescription(), sf::Color::Yellow);
			}
		}

		// Tutorial Messages
		switch (tutorialStep) {
			case 0:
				message->update("A / D to Move\nHold Shift to run\nSpace to Jump", tutColour);
				if (keys[0])
					tutCond[0] = true;
				if (keys[3])
					tutCond[1] = true;
				if ((keys[38] && keys[0]) || (keys[38] && keys[3]))
					tutCond[2] = true;
				if (keys[57])
					tutCond[3] = true;
				if (tutCond[0] && tutCond[1] && tutCond[2] && tutCond[3]) {
					tutorialStep++;
					resetConditions();
				}
				break;
			case 1:
				message->update("Use the Scroll Wheel or + / - to Zoom In and Out");
				if (scroll != 0 || keys[68] || keys[67]) {
					tutorialStep++;
					tutClock.restart();
				}
				break;
			case 2:
				message->update("You can get Missions from People with a Green \'!\' above them", tutColour);
				if (tutClock.getElapsedTime().asSeconds() > 5) {
					tutorialStep++;
				}
				break;
			case 3:
				if (quests.size() > 0) {
					message->update("Press Q to see all the Active Missions");
					if (menu["quests"]) {
						tutorialStep++;
					}
				}
				break;
			case 4:
				if (!menu["quests"]) {
					message->update("You have to Deliver the Objects to the People with a Cyan \'!\' above them");
					if (tutClock.getElapsedTime().asSeconds() > 5 && !tutCond[0]) {
						tutClock.restart();
						tutCond[0] = 1;
					}
					if (tutClock.getElapsedTime().asSeconds() > 5) {
						tutorialStep++;
						resetConditions();
						tutClock.restart();
					}
				}
				break;
			case 5:
				if (tutClock.getElapsedTime().asSeconds() > 10) {
					message->update("Tired of Running?\nPress 'H' to get on your Hoverboard\nNote: You cannot interact with objects while on the Hoverboard");
				}
				if (keys[sf::Keyboard::H]) {
					tutorialStep++;
				}
				break;
			case 6:
				if (money > 0) {
					if (!tutCond[0]) {
						tutCond[0] = true;
						tutClock.restart();
					}
					message->update("Your Money is displayed in the Top Left Corner\nWhen you have enough Money go buy a Ship from the Shop\nTo buy a Ship use the Mouse to Select one and Click on it");
					if (tutCond[0] && tutClock.getElapsedTime().asSeconds() > 10) {
						tutorialStep++;
						resetConditions();
					}
				}
				break;
			case 7:
				if (ships[0]->getVisible() && !menu["shop"]) {
					if (!tutCond[0]) {
						tutCond[0] = true;
						tutClock.restart();
					}
					message->update("Find the Ship");
					if (tutCond[0] && tutClock.getElapsedTime().asSeconds() > 5) {
						tutorialStep++;
						resetConditions();
					}
				}
				break;
			default:
				break;
		}

		if (menu["exit"]) {
			message->update("Press \'ENTER\' to Exit", sf::Color::Red);
		}

		// Show the Mouse if it was moved
		if (oldMouse.x != mouse.getPosition().x && oldMouse.y != mouse.getPosition().y) {
			mouseTimeout.restart();
			window.setMouseCursorVisible(true);
			oldMouse.x = mouse.getPosition().x;
			oldMouse.y = mouse.getPosition().y;
		}

		if (gameOver) {
			message->update("GAME OVER! Press \'Esc\' to Exit", sf::Color::Red);
			ships[0]->cutThrust();
			ships[0]->destroy();
		}

		//frameTime.restart();
		accumulator -= dt;
	//}
	}
}

void Game::render() {
	// Clear the Window
	window.clear(sf::Color::Black);


	/* --------------- Draw --------------- */

	// Zoom
	if (scroll != 0 && abs(abs(scroll) - abs(curScroll)) > 0.000001) {
		float howMuch = scroll / 15;
		ppm -= howMuch;
		curScroll += howMuch;

		if (ppm <= 0.05) {
			ppm = 0.05f;
			scroll = 0;
		}
		if (ppm > 1) {
			ppm = 1;
			scroll = 0;
		}
	} else {
		scroll = 0;
		curScroll = 0;
	}

	if (mouseTimeout.getElapsedTime().asSeconds() > 1) {
		window.setMouseCursorVisible(false);
	}

	if (menu["map"]) {
		// Astro Map
		astroMap->render(window, screen);

		// Velocity Vector
		if (menu["velocity"]) {
			velocityVector->render(window);
		}

		// Distance To Object
		if (menu["distance"]) {
			distanceObject->render(window);
		}

		// Thurst
		if (menu["thrust"]) {
			thrust->render(window);
		}

		// Fuel
		if (menu["fuel"]) {
			fuel->render(window);
		}

		// Info Panel
		if (menu["infoPanel"]) {
			infoPanel->render(window);
		}
	}
	else {
		// Star Field
		//float textureWidth = bTexture.getSize().x * ppm;
		//float textureHeight = bTexture.getSize().y * ppm;
		//float textureLeft = (bTexture.getSize().x - textureWidth) / 2 + 20 * ppm;
		//float textureTop = (bTexture.getSize().y - textureHeight) / 2 + 20 * ppm;
		//sf::IntRect tR;
		//tR.width = round(textureWidth);
		//tR.height = round(textureHeight);
		//tR.left = round(textureLeft);
		//tR.top = round(textureTop);
		////tR.width = bTexture.getSize().x * ppm;
		////tR.height = bTexture.getSize().y * ppm;
		////tR.left = (bTexture.getSize().x - tR.width) / 2 + 20 * ppm;
		////tR.top = (bTexture.getSize().y - tR.height) / 2 + 20 * ppm;
		//background.setTextureRect(tR);
		//background.setScale(Functions::map(ppm, 0.05, 1, 3, 1), Functions::map(ppm, 0.05, 1, 3, 1));
		background.setScale(1 / ppm, 1 / ppm);
		//std::cout << ppm << std::endl;
		window.draw(background);

		//std::cout << textureLeft << " " << tR.left << std::endl;
		//std::cout << textureTop << "  " << tR.top << std::endl;
		//std::cout << tR.width << " " << tR.height << " " << tR.left << " " << tR.top << std::endl;

		//// Speed Lines
		//for (int i = 0; i < speedLines.size(); i++) {
		//	speedLines[i]->render(window);
		//}

		// Astronomical Object
		for (int i = 0; i < astro.size(); i++) {
			if (i == closestPlanet || i == 0)
				astro[i]->render(window, view, screen, ppm);
		}

		// Ships
		for (int i = 0; i < ships.size(); i++) {
			if (ships[i]->getVisible())
				ships[i]->render(window, view, screen, ppm);
		}

		// Locals
		for (int i = 0; i < astro[closestPlanet]->getInhabitants(); i++) {
			if (Functions::dist(locals[i]->getX(), locals[i]->getY(), view.x, view.y) <= screen.width / ppm / 2 + 15)
				locals[i]->render(window, view, screen, ppm);
		}

		// Human
		if (onPlanet) {
			human->render(window, view, screen, ppm);
			window.draw(moneyText);
			window.draw(cargoText);
		} else {
			// Velocity Vector
			if (menu["velocity"]) {
				velocityVector->render(window);
			}

			// Distance To Object
			if (menu["distance"]) {
				distanceObject->render(window);
			}

			// Thurst
			if (menu["thrust"]) {
				thrust->render(window);
			}

			// Fuel
			if (menu["fuel"]) {
				fuel->render(window);
			}

			// Info Panel
			if (menu["infoPanel"]) {
				infoPanel->render(window);
			}
		}

		// Quest Menu
		if (menu["quests"]) {
			for (int i = 0; i < 10; i++) {
				window.draw(questRect[i]);
				window.draw(questDesc[i]);
				window.draw(scrollBarBg);
				window.draw(scrollBar);
			}
		}

		// Message
		if (message->getIsVisible()) {
			message->render(window);
		}

		if (menu["shop"]) {
			shop->render(window);
		}

		music[astroType].setVolume((int)Functions::map(Functions::dist(ships[0]->getX(), ships[0]->getY(), astro[closestPlanet]->getX(), astro[closestPlanet]->getY()) - astro[closestPlanet]->getRadius(), 0, astro[closestPlanet]->getRadius(), 100, 0));
	}

	// Draw the frameRate
	window.draw(frameRate);

	// Draw the Console
	if (menu["console"]) {
		console->render(window);
	}


	/* --------------- Draw --------------- */


	// End the Frame
	window.display();
}