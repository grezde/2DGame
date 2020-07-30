#pragma once
#include "Scene.h"
#include "ButtonSet.h"

class MenuScene :
	public ButtonSetScene
{
private:
	sf::Texture backTex;
	sf::Sprite backSpr;

public:
	MenuScene();
	~MenuScene();

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;

	virtual void finsihedSelection(int selected) override;
};

