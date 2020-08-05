#pragma once
#include "SceneScaling.h"
#include "ButtonSet.h"

class PauseMenuScene;

class PauseMenuBS
	: public ButtonSet
{
private:
	PauseMenuScene* parent;

public:
	PauseMenuBS(PauseMenuScene* parent);

	virtual void finsihedSelection(int selected) override;
};

class PauseMenuConfirmationBS
	: public ButtonSet
{
private:
	PauseMenuScene* parent;

public:
	PauseMenuConfirmationBS(PauseMenuScene* parent);

	virtual void finsihedSelection(int selected) override;
};

class PauseMenuScene
	: public VideoLikeScene
{
private:
	sf::Texture backtex;
	sf::Sprite backspr;
	
	bool confirmation = false;
	PauseMenuBS bs;
	PauseMenuConfirmationBS cbs;
	sf::Text confirmText;

public:
	PauseMenuScene();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(float dt) override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;

	friend class PauseMenuBS;
	friend class PauseMenuConfirmationBS;
};

