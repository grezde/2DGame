#include "Player.h"
#include "Room.h"
#include "Globals.h"

const float Player::SCALE = 1.6f;
const float Player::STEPSPS = 5.0f;
const float Player::SPEED = 3;
const float Player::EMOTE_SCALE = 2;

const sf::Vector2f Player::BOUNDING_BOX[4] = {
	sf::Vector2f(-0.45f,  0.0f),
	sf::Vector2f( 0.45f,  0.0f),
	sf::Vector2f(-0.45f, -0.3f),
	sf::Vector2f( 0.45f, -0.3f)
};

void Player::setTexCoords(int i, int j)
{
	sf::IntRect rect;
	rect.left = (j == -1) ? spr.getTextureRect().left : j * tex.getSize().x / 4;
	rect.top = (i == -1) ? spr.getTextureRect().top : i * tex.getSize().y / 4;
	rect.height = tex.getSize().y / 4;
	rect.width = tex.getSize().x / 4;
	spr.setTextureRect(rect);
	if(i != -1)
		Globals::save->seti("current_player_rot", i);
}

Player::Player(Room* room)
{
	tex.loadFromFile("Files/global/player.png");
	spr.setTexture(tex);
	spr.setScale(SCALE, SCALE);
	spr.setOrigin(tex.getSize().x / 8, tex.getSize().y / 4);
	
	emoteTex.loadFromFile("Files/global/emotes.png");
	emoteSpr.setTexture(emoteTex);
	setEmote(4);
	emoteSpr.setScale(EMOTE_SCALE, EMOTE_SCALE);
	emoteSpr.setOrigin(emoteTex.getSize().x / 4, emoteTex.getSize().y / 2);

	int toLoad = Globals::save->geti("coords_from_save");
	if (toLoad) {
		float ix = Globals::save->geti("current_player_x");
		float iy = Globals::save->geti("current_player_y");
		int ii = Globals::save->geti("current_player_rot");
		pos = sf::Vector2f(ix / 100.0f, iy / 100.0f);
		setTexCoords(ii, 0);
	}

	this->room = room;
}

void Player::setEmote(int number)
{
	if(number != 0)
		emoteNumber = number;
	int x = (emoteNumber - 1) % 2;
	int y = (emoteNumber - 1) / 2;
	emoteSpr.setTextureRect(sf::IntRect(
		x * emoteTex.getSize().x / 2,
		y * emoteTex.getSize().y / 2,
		emoteTex.getSize().x / 2,
		emoteTex.getSize().y / 2
	));
}

void Player::update(float dt)
{
	emoteNumber = 0;
	float dx = 0, dy = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dx -= 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dx += 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		dy -= 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		dy += 1.0f;

	if (dx != 0 && dy != 0) {
		dx *= 0.7f;
		dy *= 0.7f;
		setTexCoords(-1, int(timeSinceStopped / 0.2f) % 4);
	} 
	else {
		if (dx == 1.0f)
			setTexCoords(3, int(timeSinceStopped / 0.2f) % 4);
		if (dx == -1.0f)
			setTexCoords(2, int(timeSinceStopped / 0.2f) % 4);
		if (dy == 1.0f)
			setTexCoords(0, int(timeSinceStopped / 0.2f) % 4);
		if (dy == -1.0f)
			setTexCoords(1, int(timeSinceStopped / 0.2f) % 4);
	}

	timeSinceStopped += dt;
	if (dx == 0 && dy == 0) {
		setTexCoords(-1, 0);
		timeSinceStopped = 0;
		pWalking = false;
	}
	else {
		pWalking = true;
		nextCoords = sf::Vector2f(pos.x + dx/1.5f, pos.y + dy/1.5f);
	}

	float mult = dt * SPEED * Room::SCALE * Room::PIXPM;

	sf::Vector2f newpos = pos + sf::Vector2f(dx * dt * SPEED, dy * dt * SPEED);
	for (auto dp : BOUNDING_BOX)
		if (!room->positionValid(newpos + dp)) {
			newpos = pos + room->projectSpeed(pos+dp, newpos+dp);
		}

	pos = newpos;
	room->setCenterPosition(pos);
	spr.setPosition(room->getPosOnScreen(pos));
	emoteSpr.setPosition(spr.getPosition() + sf::Vector2f(0, - float(tex.getSize().y) * SCALE / 4));

	Globals::save->seti("current_player_x", pos.x * 100.0f);
	Globals::save->seti("current_player_y", pos.y * 100.0f);
	Globals::save->remi("coords_from_save");
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spr, states);
	if (emoteNumber != 0) {
		target.draw(emoteSpr, states);
	}
}


