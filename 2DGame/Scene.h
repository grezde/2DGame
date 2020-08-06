#pragma once
#include "GameElement.h"

class Scene : public IGameElement
{
protected:
	Scene* next = nullptr;
	bool exit = false;
	bool updateDown, saveDraw;
	sf::Transform transform;

public:
	Scene()
	{
		updateDown = false;
		saveDraw = false;
	}

	virtual void init() {}
	virtual void reinit() {}
	virtual void onKeyPress(sf::Keyboard::Key key) {}
	virtual void onMousePress(sf::Mouse::Button button, sf::Vector2i position) {}
	virtual void onTextEntered(char character) {}
	virtual void onWindowResize(sf::Vector2i size) = 0; //for transforms
	
	inline bool shouldQuit() const { return exit; }
	inline Scene* nextScene() const { return next; }
	inline void nextScene(Scene* next) { this->next = next; }
	inline sf::Transform getTransform() const { return transform; }
	inline bool updateBeneath() const { return updateDown; }
	inline bool drawOnSave() const { return saveDraw; }
};

