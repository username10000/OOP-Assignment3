#ifndef HUMAN_H
#define HUMAN_H

// Dependencies
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GameObject.h>
#include <Functions.h>
#include <Quest.h>

// Human
class Human : public GameObject {
	private:
		//sf::Texture texture;
		sf::Sprite sprite;
		sf::Sprite questSprite;
		sf::Vector2<double> velocity;
		sf::Vector2<double> direction;
		sf::Clock clock;
		float force;
		float mass;
		float angle;
		float planetRotation;
		float speed;
		int dir;
		int state;
		int nextStateChange;
		int closestSpecial;
		int closestLocal;
		int questType;
		int returnQuest;
		bool jump;
		bool hasQuest;
		bool hasReturn;
		std::string questItem;
		std::unique_ptr<Quest> quest;
		sf::SoundBuffer buffer;
		sf::Sound sound;
	public:
		Human(double x, double y, sf::Texture *texture);
		sf::Vector2<double> getVelocity();
		sf::Vector2<double> getDirection();
		float getMass();
		float getForce();
		int getDir();
		void addVelocity(double x, double y);
		void setDirection(double x, double y);
		void setForce(float f);
		void resetVelocity();
		void setAngle(float a);
		void setDir(int d);
		void setDirJump(int d);
		void resetSprite();
		void setState(int s);
		int getState();
		void setNextStateChange(int nSC);
		int getNextStateChange();
		void setJump(bool j);
		bool getJump();
		void setClosestSpecial(int cS);
		int getClosestSpecial();
		void setColour(sf::Color colour);
		void setSpeed(float speed);
		void setQuest(int type, int item, int noItems, int destination, int reward);
		bool getHasQuest();
		void setHasQuest(bool hQ);
		bool getHasReturn();
		void setHasReturn(bool hR);
		std::unique_ptr<Quest> getQuest();
		float getWidth();
		float getHeight();
		int getClosestLocal();
		void setClosestLocal(int l);
		int getReturnQuest();
		void setReturnQuest(int rQ);
		void playSound();
		//void setPlanetRotation(float r);
		void update();
		void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
};

#endif