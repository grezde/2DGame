#pragma once
#include "Scene.h"
#include "Button.h"

class MenuScene :
	public Scene
{
private:
	sf::Texture backTex;
	sf::Sprite backSpr;
	std::vector<Button> buttons;

public:
	MenuScene();
	~MenuScene();

	virtual void draw(sf::RenderWindow* window);
	virtual void update(float dt);
};

