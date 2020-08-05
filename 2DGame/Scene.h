#pragma once
#include "GameElement.h"

class Scene : public IGameElement
{
protected:
	Scene* next = nullptr;
	bool exit = false;
	bool updateDown = false;
	sf::Transform transform;

public:
	virtual void init() {}
	virtual void reinit() {}
	virtual void onKeyPress(sf::Keyboard::Key key) {}
	virtual void onMousePress(sf::Mouse::Button button, sf::Vector2i position) {}
	virtual void onTextEntered(char character) {}
	virtual void onWindowResize(sf::Vector2i size) = 0; //for transforms
	
	inline bool shouldQuit() { return exit; }
	inline Scene* nextScene() { return next; }
	inline void nextScene(Scene* next) { this->next = next; }
	inline bool updateBeneath() { return updateDown; }
	inline sf::Transform& getTransform() { return transform; }
};

