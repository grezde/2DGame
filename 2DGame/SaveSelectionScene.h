#pragma once
#include "SceneScaling.h"
#include "ButtonSet.h"

class SaveSelectionScene;

class SaveSelectionBS
	: public ButtonSet
{
private:
	SaveSelectionScene* parent;

private:
	static std::vector<std::string> getSaveNames();

public:
	SaveSelectionBS(SaveSelectionScene* parent);

	virtual void finsihedSelection(int selected);
};

class SaveSelectionScene 
	: public VideoLikeScene
{
private:
	sf::Texture backTex;
	sf::Sprite backSpr;

	SaveSelectionBS bs;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	SaveSelectionScene();

	virtual void update(float dt) override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;
};

