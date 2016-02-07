#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	// Window Settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Open a new Window
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Window", sf::Style::Fullscreen, settings);

	// Load the Font
	sf::Font font;
	if (!font.loadFromFile("CALIBRI.TTF"))
		return EXIT_FAILURE;

	// Rendering Loop
	while (window.isOpen())
	{
		// Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// Close the Window
				case sf::Event::Closed:
					window.close();
					break;
				// Close the Window if Escape is pressed
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					break;
				default:
					break;
			}
		}

		// Clear the Window
		window.clear(sf::Color::Black);

		/* --------------- Draw --------------- */

		// Text Test
		sf::Text text;
		text.setFont(font);
		text.setString("Hello World");
		text.setCharacterSize(24); // In Pixels
		text.setColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		//window.draw(text);

		// Shapes

		// Circle
		sf::CircleShape circle(50);
		circle.setRadius(1000);
		circle.setPointCount(100);
		circle.setFillColor(sf::Color(100, 250, 50));
		//circle.setOutlineThickness(2);
		//circle.setOutlineColor(sf::Color(250, 150, 100));
		//window.draw(circle);

		// Rectangle
		sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		//rectangle.setSize(sf::Vector2f(100, 100)); // Change the size
		//window.draw(rectangle);

		// Convex Shapes
		sf::ConvexShape convex;
		convex.setPointCount(4);
		convex.setPoint(0, sf::Vector2f(100, 100));
		convex.setPoint(1, sf::Vector2f(150, 150));
		convex.setPoint(2, sf::Vector2f(100, 125));
		convex.setPoint(3, sf::Vector2f(50, 150));
		//window.draw(convex);

		// Vertex Array
		sf::VertexArray triangle(sf::Triangles, 3);
		triangle[0].position = sf::Vector2f(10, 10);
		triangle[1].position = sf::Vector2f(100, 10);
		triangle[2].position = sf::Vector2f(100, 100);

		triangle[0].color = sf::Color::Red;
		triangle[1].color = sf::Color::Blue;
		triangle[2].color = sf::Color::Green;
		window.draw(triangle);


		/* --------------- Draw --------------- */

		// End the Frame
		window.display();
	}

	return 0;
}