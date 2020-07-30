#pragma once
#include "Scene.h"
#include "ButtonSet.h"

class MenuScene;

class MainMenuButtonSet
	: public ButtonSet
{
private:
	MenuScene* parent;

public:
	MainMenuButtonSet(MenuScene* parent);

	virtual void finsihedSelection(int selected) override;
};

class MenuScene
	: public Scene
{
private:
	sf::Texture backTex;
	sf::Sprite backSpr;
	MainMenuButtonSet bs;

public:
	MenuScene();
	~MenuScene();

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;

	friend class MainMenuButtonSet;
};

