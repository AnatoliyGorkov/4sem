#include <SFML\Graphics.hpp>
#include "Bullet.h"
#include <vector>

const float heroVelocity = 250.0f;
const float pi = 3.14159265358f;
const float heroScale = 0.5f;
const float firingRate = 0.3f;
const float bulletVelocity = 1500.0f;
const float collisionRadius = 128.0f;

bool almostEqual(double lhs, double rhs)
{
	return std::abs(lhs - rhs) <= std::numeric_limits<double>::epsilon() * std::max(std::abs(lhs), std::abs(rhs));
}

void normalize(sf::Vector2f& vector)
{
	float len = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (almostEqual(len, 0))
		return;
	vector.x /= len;
	vector.y /= len;
}

/*
в общем случае лучше конечно структуры передавать через const& по возможности.
в данном случае скорее всего sf::Time довольно маленькая, но всё же
*/
void moveBullets(std::vector<Bullet>& bullets, sf::Time elapsed)
{
	for (auto& bullet : bullets)
	{
		bullet.move(elapsed);
	}
}

// ф-я назвается "нарисовать", но делает не только это
void drawBullets(std::vector<Bullet>& bullets, sf::RenderWindow& window)
{
	if (bullets.empty())
		return;
	int i = 0;
	// не уверен, что переменная bulletsNumber необходима, когда есть метод bullets.back()
	int bulletsNumber = bullets.size();
	while (i < bulletsNumber)
	{
		if (!bullets[i].isActive(window))
		{
			bullets[i] = bullets[bulletsNumber - 1];
			bullets.pop_back();
			bulletsNumber--;
		}
		else
			i++;
	}
	for (auto& bullet : bullets)
	{
		window.draw(bullet.shape);
	}
}

void moveHero(sf::Sprite& hero, sf::Time time, sf::RenderWindow& window)
{
	/* в рамках данного упражнения пойдет, конечно, но вы смешиваете код "управления" героя, и "логику"  вместе.
	 также не стоит смешивать "логику" и "визуализацию" */
	float heroAdjustment = time.asSeconds() * heroVelocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hero.getPosition().x - heroAdjustment >= collisionRadius * heroScale)
		hero.move(-heroAdjustment, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && hero.getPosition().x + heroAdjustment <= window.getSize().x - collisionRadius * heroScale)
		hero.move(heroAdjustment, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && hero.getPosition().y - heroAdjustment >= collisionRadius * heroScale)
		hero.move(0, -heroAdjustment);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && hero.getPosition().y + heroAdjustment <= window.getSize().y - collisionRadius * heroScale)
		hero.move(0, heroAdjustment);

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f center = hero.getPosition();
	
	// если итак ясно какой тип можно писать auto d = ...
	sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;

	hero.setRotation(90 + atan2f(d.y, d.x) * 180 / pi);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Hero", sf::Style::Titlebar | sf::Style::Close);
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);	//Framerate = monitor frequency
	sf::Clock clock;

	sf::Texture texture;
	texture.loadFromFile("Superman-256.png");
	texture.setSmooth(true);

	// можно бы инициализацию героя вынести в отдельную ф-ю
	sf::Sprite hero(texture);
	sf::Vector2u heroSize = hero.getTexture()->getSize();
	hero.setOrigin(heroSize.x / 2, heroSize.y / 2);
	hero.setScale(heroScale, heroScale);
	sf::Vector2u windowSize = window.getSize();
	hero.setPosition(windowSize.x / 2, windowSize.y / 2);
	float totalRun = 0.0f;
	float lastBulletFired = 0.0f;
	std::vector<Bullet> bullets;
	sf::Time time;

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
			default:
				break;
			}
		}
		//hero movement
		window.clear(sf::Color(155, 244, 66));
		time = clock.getElapsedTime();
		clock.restart();
		totalRun += time.asSeconds();


		moveHero(hero, time, window);
		
		window.draw(hero);

		// эти три строки кода уже встречались ранее. лучше вынести в отдельную ф-ю
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = hero.getPosition();
		sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center;
		normalize(d);

		//hero shoots bullet
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (totalRun - lastBulletFired >= firingRate)
				//create bullet
			{
				bullets.push_back(Bullet(hero.getPosition().x + hero.getTexture()->getSize().y * heroScale / 2 * d.x,
					hero.getPosition().y + hero.getTexture()->getSize().y * heroScale / 2 * d.y,
					sf::Vector2f(d.x * bulletVelocity, d.y * bulletVelocity)));
				lastBulletFired = totalRun;
			}
		}
		moveBullets(bullets, time);
		drawBullets(bullets, window);

		//hero shoots lasers
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			float maxScreenLen = std::sqrt(window.getSize().x * window.getSize().x + window.getSize().y * window.getSize().y);
			sf::RectangleShape line1(sf::Vector2f(maxScreenLen, 3));
			// обычно размер задают не в пикселях, а как некая доля от диагонали экрана, например.
			// чтобы при смене разрешения все ок осталось 
			sf::RectangleShape line2(sf::Vector2f(maxScreenLen, 3));
			line1.setFillColor(sf::Color::Red);
			line2.setFillColor(sf::Color::Red);
			// so the lasers match the eyes
			
			/// можно для 65 и 42 дать осмысленные названия?
			line1.setPosition(hero.getPosition().x + 65 * heroScale * d.x - 22 * heroScale* d.y,
				hero.getPosition().y + 65 * heroScale* d.y + 22 * heroScale* d.x);

			line2.setPosition(hero.getPosition().x + 65 * heroScale * d.x + 42 * heroScale* d.y,
				hero.getPosition().y + 65 * heroScale* d.y - 42 * heroScale* d.x);

			line1.setRotation(atan2f(d.y, d.x) * 180 / pi);
			line2.setRotation(atan2f(d.y, d.x) * 180 / pi);
			window.draw(line1);
			window.draw(line2);
		}
		window.display();

	}

	return 0;
}
