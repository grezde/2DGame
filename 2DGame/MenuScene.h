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

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	MenuScene();
	~MenuScene();

	virtual void update(float dt) override;

	friend class MainMenuButtonSet;
};

