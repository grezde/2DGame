#pragma once
#include "GameElement.h"

class Scene : public IGameElement
{
protected:
	Scene* next = nullptr;
	bool exit = false;
	bool updateDown = false;
	
public:
	virtual void init() {}
	virtual void reinit() {}
	virtual void onKeyPress(sf::Keyboard::Key key) {}
	virtual void onMousePress(sf::Event::MouseButtonEvent button) {}
	virtual void onTextEntered(char character) {}
	
	inline bool shouldQuit() { return exit; }
	inline Scene* nextScene() { return next; }
	inline void nextScene(Scene* next) { this->next = next; }
	inline bool updateBeneath() { return updateDown; }
};

