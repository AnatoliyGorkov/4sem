#include "Particle.h"

// особо нет смысла писать position(Vector2()) ... ровно то же самое компилятор по умолчанию сделает
Particle::Particle() :
	position(Vector2()),
	velocity(Vector2()),
	mass(0),
	radius(0)
{
}

Particle::Particle(const Vector2& position, const Vector2& velocity, float radius, float mass) :
	position(position),
	velocity(velocity),
	mass(mass),
	radius(radius)
{
}

Vector2 Particle::getImpulse()
{
	// return mass * velocity; ?
	return Vector2(mass * velocity.x, mass * velocity.y);
}

void Particle::draw(sf::RenderWindow& window, sf::Color color, sf::Color outlineColor) const
{
	sf::CircleShape shape(radius);
	shape.setOrigin(radius / 2, radius / 2);
	shape.setPosition(position.x, position.y);
	shape.setFillColor(color);
	shape.setOutlineThickness(-1);
	shape.setOutlineColor(outlineColor);
	window.draw(shape);
}

// моя интуиция подсказывает, что если ф-я называется check, то она должна быть 
// константной и возвращать bool ... да/нет
void Particle::checkCollision(const sf::RenderWindow& window, const float bounceFactor)
{
	// *= можно использовать
	if (position.x < radius && velocity.x < 0)
		velocity.x = -bounceFactor * velocity.x;
	if (position.y < radius && velocity.y < 0)
		velocity.y = -bounceFactor * velocity.y;
	if (position.x > window.getSize().x - radius && velocity.x > 0)
		velocity.x = -bounceFactor * velocity.x;
	if (position.y > window.getSize().y - radius && velocity.y > 0)
		velocity.y = -bounceFactor * velocity.y;
}

void Particle::checkCollision(Particle& other, const float bounceFactor)
{
	Vector2 d = position - other.position;	// d for distance
	if (d.len() > radius + other.radius)	//if not in contact
		return;
	if ((velocity - other.velocity) * d > 0)	//if not headed to each other
		return;
	d.norm();
	Vector2 dp = ((1 + bounceFactor) * (velocity - other.velocity) * (1 / (1 / mass + 1 / other.mass)) * d) * d;
	other.velocity += dp * (1 / other.mass);
	velocity -= dp * (1 / mass);
}

/*
//I did a mistake here, but it looks fine, so I decided to leave it
void Particle::checkCollision(Particle& other, const float bounceFactor)
{
	Vector2 d = position - other.position;	// d for distance
	if (d.len() > radius + other.radius)	//if not in contact
		return;
	if ((other.velocity - velocity) * d > 0)	//if not headed to each other
		return;
	d.norm();
	Vector2 dp = ((1 + bounceFactor) * (other.velocity - velocity) * (1 / (1 / mass + 1 / other.mass)) * d) * d;
	other.velocity += dp * (1 / other.mass);
	velocity -= dp * (1 / mass);
}
*/


void Particle::move(const sf::Time& time)
{
	position.x += velocity.x * time.asSeconds();
	position.y += velocity.y * time.asSeconds();
}

Particle& Particle::setRandom(const sf::RenderWindow& window, const int maxVelocity)
{
	int xmax = window.getSize().x - 2 * radius;
	int ymax = window.getSize().y - 2 * radius;

	position.x = (std::rand() % xmax) + radius;
	position.y = (std::rand() % ymax) + radius;
	velocity.x = std::rand() % maxVelocity;
	velocity.y = std::rand() % maxVelocity;

	return (*this);
}

