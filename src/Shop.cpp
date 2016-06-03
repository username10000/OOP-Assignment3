#include <Shop.h>

Shop::Shop(sf::VideoMode screen, sf::Font font, sf::Texture *shipTextures) {
	this->font = font;
	this->shipTextures = *shipTextures;
	
	background.setFillColor(sf::Color(0, 0, 0, 150));
	background.setPosition(screen.width / 10, screen.height / 10);
	background.setSize(sf::Vector2f(screen.width - 2 * background.getPosition().x, screen.height - 2 * background.getPosition().y));
	background.setOutlineThickness(1);
	background.setOutlineColor(sf::Color::White);

	for (int i = 0; i < shipTextures->getSize().x / 40; i++) {
		sf::RectangleShape shipRect;
		sf::IntRect shipTextureRect;
		float shipSize = background.getSize().y / 5.5;
		shipRect.setSize(sf::Vector2f(shipSize, shipSize));
		shipRect.setTexture(shipTextures);
		shipTextureRect.top = 0;
		shipTextureRect.left = i * 41;
		shipTextureRect.width = 40;
		shipTextureRect.height = 40;
		shipRect.setTextureRect(shipTextureRect);
		shipRect.setOrigin(shipRect.getLocalBounds().width / 2, shipRect.getLocalBounds().height / 2);
		float xPos = Functions::map(i, 0, (int)(this->shipTextures.getSize().x / 40) - 1, background.getPosition().x + shipRect.getSize().x, background.getPosition().x + background.getSize().x - shipRect.getSize().x);
		float yPos = background.getPosition().y + background.getSize().y / 2;
		//float yPos = Functions::map(0, 0, 3, background.getPosition().y + shipRect.getSize().y, background.getPosition().y + background.getSize().y + shipRect.getSize().y / 2);
		buttons.push_back(std::unique_ptr<Button>(new Button(shipRect)));
		buttons[buttons.size() - 1]->setPosition(xPos, yPos);

		priceNum.push_back(Functions::randomInt(4000, 10000));

		sf::Text name;

		prices.push_back(name);
		prices[prices.size() - 1].setFont(this->font);
		prices[prices.size() - 1].setCharacterSize(15);
		prices[prices.size() - 1].setString(Functions::toStringWithComma(priceNum[priceNum.size() - 1]));
		prices[prices.size() - 1].setOrigin(prices[prices.size() - 1].getLocalBounds().width / 2, prices[prices.size() - 1].getLocalBounds().height / 2);
		prices[prices.size() - 1].setPosition(xPos, yPos + shipSize / 2 + prices[prices.size() - 1].getCharacterSize());

		purchased.push_back(false);
	}
	//purchased[0] = true;
	//prices[0].setString("Purchased");
	//prices[0].setOrigin(prices[0].getLocalBounds().width / 2, prices[0].getLocalBounds().height / 2);

	purchase = -1;
}

int Shop::update(sf::RenderWindow &window) {
	int returnValue = -1;
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->update(window);
		if (buttons[i]->isActive()) {
			if (!purchased[i]) {
				returnValue = priceNum[i];
				purchase = i;
			} else {
				returnValue = i;
			}
		}
	}
	return returnValue;
}

void Shop::confirmPurchase() {
	if (purchase >= 0 && purchase < prices.size()) {
		prices[purchase].setString("Purchased");
		prices[purchase].setOrigin(prices[purchase].getLocalBounds().width / 2, prices[purchase].getLocalBounds().height / 2);
		purchased[purchase] = true;
	}
}

void Shop::setPrice(int purchaseNo, int price) {
	if (purchaseNo >= 0 && purchaseNo < prices.size()) {
		priceNum[purchaseNo] = price;
		prices[purchaseNo].setString(Functions::toStringWithComma(priceNum[purchaseNo]));
		prices[purchaseNo].setOrigin(prices[purchaseNo].getLocalBounds().width / 2, prices[purchaseNo].getLocalBounds().height / 2);
	}
}

void Shop::render(sf::RenderWindow &window) {
	window.draw(background);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render(window);
		window.draw(prices[i]);
	}
}