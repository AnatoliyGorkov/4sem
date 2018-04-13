#pragma once
#include <SFML\Graphics.hpp>

class Bullet
{
public:
	float x, y;
	sf::Vector2f velocity;
	
	// не здорово смешивать "логику" и "способ визуализации" в одном классе
	// если вы захотите, например, сделать из этого сетевую игру, то сходу не получится, т.к. 
	// на сервере никакая визуализация не нужна, а на клиентах по факту нужно только отображать что-то ... без логики
	sf::CircleShape shape;

	Bullet(float x, float y, const sf::Vector2f& velocity, float size = 8.0f);

	void move(sf::Time time);
	bool isActive(const sf::Window& window) const;	//checks if the bullet fits the window

};
