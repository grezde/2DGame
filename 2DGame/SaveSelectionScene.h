#pragma once
#include "Scene.h"
#include "ButtonSet.h"

class SaveSelectionScene;

class SaveSelectionBS
	: public ButtonSet
{
private:
	SaveSelectionScene* parent;

protected:
	float buttonSpace = 0.25f;

private:
	static std::vector<std::string> getSaveNames();

public:
	SaveSelectionBS(SaveSelectionScene* parent);

	virtual void finsihedSelection(int selected);
};

class SaveSelectionScene :
	public Scene
{
private:
	bool stoppedPressing = false;
	float sinceStart = 0;

	sf::Texture backTex;
	sf::Sprite backSpr;

	SaveSelectionBS bs;

public:
	SaveSelectionScene();

	virtual void draw(sf::RenderWindow* window);
	virtual void update(float dt);
};

