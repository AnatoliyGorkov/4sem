#include "Bullet.h"


Bullet::Bullet(float x, float y, const sf::Vector2f& velocity, float size) :
	x(x),
	y(y),
	velocity(velocity),
	shape(size)
{
	shape.setOrigin(size, size);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Blue);
}

void Bullet::move(sf::Time time)
{
	// x += ... ?
	x = x + velocity.x * time.asSeconds();
	y = y + velocity.y * time.asSeconds();
	shape.setPosition(x, y);
}

bool Bullet::isActive(const sf::Window& window) const
{
	/*
	зачем лишние строки ... сразу
	return x >= 0 && x < windowSize.x && ... ;
	*/
	sf::Vector2u windowSize = window.getSize();
	if (x < 0 ||
		y < 0 ||
		x > windowSize.x ||
		y > windowSize.y)
		return false;
	return true;
}
