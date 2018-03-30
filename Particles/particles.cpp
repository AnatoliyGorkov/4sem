#include <SFML\Graphics.hpp>
#include "Particle.h"
#include "Vector2.h"
#include <vector>
#include <iostream>

const int maxVelocity = 150;
const int particleNumber = 50;
const int radius = 10;
const float bounceFactor = 1.0f;
void moveParticles(std::vector<Particle>& particles, const sf::Time& time)
{
	for (auto& particle : particles)
		particle.move(time);
}

void checkCollision(std::vector<Particle>& particles, const sf::RenderWindow& window, float bounceFactor = 1.0f)
{
	for (auto& particle : particles)
	{
		particle.checkCollision(window, bounceFactor);
	}
	int particleNumber = particles.size();
	for (int i = 0; i < particleNumber - 1; i++)
		for (int j = i + 1; j < particleNumber; j++)
			particles[i].checkCollision(particles[j], bounceFactor);
}

void createParticles(std::vector<Particle>& particles, int number, const sf::RenderWindow& window,
	const float radius = 10.0f, const float mass = 1.0f)	//creates number particles
{
	if (2 * radius >= window.getSize().x || 2 * radius >= window.getSize().y)
		return;
	Particle particle(Vector2(0, 0), Vector2(0, 0), radius, mass);
	for (int i = 0; i < number; i++)
	{
		particles.push_back(particle.setRandom(window, maxVelocity));
	}
}

void drawParticles(const std::vector<Particle>& particles, sf::RenderWindow& window)
{
	for (auto& particle : particles)
		particle.draw(window);
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1024, 768), "My window", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;
	sf::Time time;
	std::vector<Particle> particles;
	createParticles(particles, particleNumber, window, radius);
	Particle particle(Vector2(0, 0), Vector2(0, 0), radius);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				particles.push_back(particle.setRandom(window, maxVelocity));
			default:
				break;
			}
		}
		window.clear(sf::Color::White);
		
		time = clock.getElapsedTime();
		std::cout << "fps " << (int)(1 / time.asSeconds()) << std::endl;
		std::cout << "particles: " << particles.size() << std::endl;
		clock.restart();
		moveParticles(particles, time);
		checkCollision(particles, window, bounceFactor);
		drawParticles(particles, window);
		window.display();
	}

	return 0;
}
