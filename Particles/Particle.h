#pragma once
#include <SFML\Graphics.hpp>
#include "Vector2.h"
class Particle
{
public:
	Vector2 position;
	Vector2 velocity;
	float mass;
	float radius;
	Particle();
	Particle(const Vector2& position, const Vector2& velocity, float radius = 10.0f, float mass = 1.0f);
	Vector2 getImpulse();
	void draw(sf::RenderWindow& window, sf::Color color = sf::Color(44, 62, 80), sf::Color outlineColor = sf::Color(52, 73, 94)) const;
	void checkCollision(const sf::RenderWindow& window, const float bounceFactor = 1.0f);
	void checkCollision(Particle& other, const float bounceFactor = 1.0f);
	void move(const sf::Time& time);
	Particle& setRandom(const sf::RenderWindow& window, const int maxVelocity = 1000);
};