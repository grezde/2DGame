#pragma once
#include "SceneScaling.h"
#include "TextSelector.h"

class InventoryScene;

class InventoryTS
	: public TextSelector
{
private:
	InventoryScene* parent;

public:
	InventoryTS(InventoryScene* parent);

	virtual void onSelected(int newsel) override;
	virtual void finishedSelection(int sel) override;
};

class InventoryScene 
	: public VideoLikeScene
{
private:
	sf::Texture backtex;
	sf::Sprite backspr;
	std::vector<sf::Text> decoration;
	sf::Text description;
	std::vector<sf::Text> stats;
	InventoryTS ts;

private:
	sf::Text createLabel(bool big);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	InventoryScene();

	virtual void update(float dt) override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;
	virtual void reinit() override;

	friend class InventoryTS;
};

