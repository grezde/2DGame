#include "Player.h"
#include "Room.h"

const float Player::SCALE = 1.5f;
const float Player::STEPSPS = 5.0f;
const float Player::SPEED = 2;
const sf::Vector2f Player::BOUNDING_BOX[4] = {
	sf::Vector2f(-0.45f,  0.0f),
	sf::Vector2f( 0.45f,  0.0f),
	sf::Vector2f(-0.45f, -0.5f),
	sf::Vector2f( 0.45f, -0.5f)
};

void Player::setTexCoords(int i, int j)
{
	sf::IntRect rect;
	rect.left = (j == -1) ? spr.getTextureRect().left : j * tex.getSize().x / 4;
	rect.top = (i == -1) ? spr.getTextureRect().top : i * tex.getSize().y / 4;
	rect.height = tex.getSize().y / 4;
	rect.width = tex.getSize().x / 4;
	spr.setTextureRect(rect);
}

Player::Player(sf::Vector2i startPos, Room* room)
{
	tex.loadFromFile("Files/global_pictures/player.png");
	spr.setTexture(tex);
	spr.setScale(SCALE, SCALE);
	spr.setOrigin(tex.getSize().x / 8, tex.getSize().y / 4);
	setTexCoords(0, 0);

	this->room = room;
	this->pos = sf::Vector2f(startPos.x, startPos.y);
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(spr);
}

void Player::update(float dt)
{
	float dx = 0, dy = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dx -= 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dx += 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		dy -= 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		dy += 1.0f;

	if (dx == 1.0f)
		setTexCoords(3, int(timeSinceStopped / 0.2f) % 4);
	if (dx == -1.0f)
		setTexCoords(2, int(timeSinceStopped / 0.2f) % 4);
	if (dy == 1.0f)
		setTexCoords(0, int(timeSinceStopped / 0.2f) % 4);
	if (dy == -1.0f)
		setTexCoords(1, int(timeSinceStopped / 0.2f) % 4);

	if (dx != 0 && dy != 0) {
		dx *= 0.7f;
		dy *= 0.7f;
	}

	timeSinceStopped += dt;
	if (dx == 0 && dy == 0) {
		setTexCoords(-1, 0);
		timeSinceStopped = 0;
	}

	float mult = dt * SPEED * Room::SCALE * Room::PIXPM;

	sf::Vector2f newpos = pos + sf::Vector2f(dx * dt * SPEED, dy * dt * SPEED);
	for (auto dp : BOUNDING_BOX)
		if (!room->positionValid(newpos + dp))
			return;

	pos = newpos;
	room->setCenterPosition(pos);
	spr.setPosition(room->getPosOnScreen(pos));
}


