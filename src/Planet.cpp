#include <Planet.h>

Planet::Planet(double x, double y, float _radius, sf::Color _colour, float _rotation) : AstroObject(x, y, _radius, _colour, _rotation) {
	//circle.setRadius(_radius);
	//circle.setPointCount(100);
	//circle.setFillColor(_colour);
	//addVelocity(1, 0);

	rTexture.create(getRadius(), getRadius());
	rTexture.clear(_colour);
	if (_rotation != 0)
		_colour = sf::Color(Functions::randomInt(0, 255), Functions::randomInt(0, 255), Functions::randomInt(0, 255));
	else
		_colour = sf::Color::Black;
	setSecondColour(_colour);

	// Create Texture
	for (int z = 0; z < Functions::randomInt(10, 20); z++) {
		// Centre Position
		float xCentre = Functions::randomFloat(0, rTexture.getSize().x - 1);
		float yCentre = Functions::randomFloat(0, rTexture.getSize().y - 1);
		
		// Vertex Array
		std::vector<sf::Vertex> vertices;

		// Create the Centre Vertex
		vertices.push_back(sf::Vertex(sf::Vector2f(xCentre, yCentre), _colour));
		
		// Random Radius
		float maxRadius = Functions::randomFloat(50, 100);
		float lastRadius = maxRadius;

		// Number of Vertices
		int verticesNum = 100;

		for (int i = 1; i <= verticesNum; i++) {
			// Get the Angle of the Vertex
			float theta = Functions::map(i, 1, verticesNum, 0, 2 * PI);
			
			// Increase or Decrease the Distance from the Centre
			if (Functions::randomInt(0, 1) == 0 || lastRadius > maxRadius)
				lastRadius -= Functions::randomFloat(1, 5);
			else
				lastRadius += Functions::randomFloat(1, 5);

			// Find the position of the Vertex
			float xPos = xCentre + sin(theta) * lastRadius;
			float yPos = yCentre - cos(theta) * lastRadius;

			// Create the Vertex
			vertices.push_back(sf::Vertex(sf::Vector2f(xPos, yPos), _colour));
		}

		// Draw the Shape to the Render Texture
		rTexture.draw(&vertices[0], vertices.size(), sf::TrianglesFan);
	}

	// Create the Texture
	rTexture.display();

	// Assign the Texture to the Planet
	texture = rTexture.getTexture();
	setPlanetTexture(&texture);

	setHabitable(true);
}

Planet::Planet() : Planet(0, 0, 100, sf::Color(255, 255, 0), 0.01) {
}

void Planet::update() {
	float acceleration = getForce() / getMass();
	sf::Vector2<double> direction = getDirection();
	setAcceleration(acceleration);
	addVelocity(direction.x * acceleration, direction.y * acceleration);
	sf::Vector2<double> velocity = getVelocity();
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
	rotate();
	updateCommonObject();
	//std::cout << getX() << " " << getY() << std::endl;
	//std::cout << velocity.x << " " << velocity.y << std::endl;
	//std::cout << getDirection().x << " " << getDirection().y << std::endl;
}

/*
void Planet::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen) {
	circle.setPosition((screen.width / 2) + (getX() - view.x) - getRadius(), (screen.height / 2) + (getY() - view.y) - getRadius());
	window.draw(circle);
}
*/