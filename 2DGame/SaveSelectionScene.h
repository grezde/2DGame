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

	virtual void finsihedSelection(int selected) override;
	virtual void changedSelection(int selected) override;
};

class SaveConfirmationBS
	: public ButtonSet
{
private:
	SaveSelectionScene* parent;

public:
	SaveConfirmationBS(SaveSelectionScene* parent);

	virtual void finsihedSelection(int selected) override;
};

class SaveSelectionScene 
	: public VideoLikeScene
{
private:
	sf::Texture backTex;
	sf::Sprite backSpr;
	sf::Sprite thumbSpr;
	sf::Text dateLabel;
	sf::Text timeLabel;

	int state = 0;
	SaveSelectionBS bs;
	SaveConfirmationBS cbs;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	SaveSelectionScene();

	virtual void update(float dt) override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;

	friend class SaveSelectionBS;
	friend class SaveConfirmationBS;
};

