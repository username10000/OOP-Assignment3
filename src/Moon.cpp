#include <Moon.h>

Moon::Moon(double x, double y, float _radius, sf::Color _colour, float _rotation) : Planet(x, y, _radius, _colour, _rotation) {
	setMass(getRadius() * 9.3 / 5);

	rTexture.create(getRadius(), getRadius());
	rTexture.clear(_colour);
	int rCol = Functions::randomInt(0, 255);
	_colour = sf::Color(rCol, rCol, rCol);
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
		float maxRadius = Functions::randomFloat(10, 20);
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

	setHabitable(false);
}