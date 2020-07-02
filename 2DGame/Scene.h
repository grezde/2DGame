#pragma once
#include <SFML/Graphics.hpp>

class IGameElement {
public:
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void update(float dt) = 0;
};

class Scene : public IGameElement
{
protected:
	Scene* next = nullptr;
	bool exit = false;
	
public:
	virtual void init() {};
	virtual void onKeyPress(sf::Keyboard::Key key) {};
	virtual void onMousePress(sf::Mouse::Button button) {};
	
	inline bool shouldQuit() { return exit; };
	inline Scene* nextScene() { return next; }
};

