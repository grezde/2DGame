#pragma once
#include "SceneScaling.h"
#include "TextSelector.h"

class ItemUseScene;

class ItemUseTS
	: public TextSelector
{
private:
	ItemUseScene* parent;

public:
	ItemUseTS(ItemUseScene* parent);

	virtual void onSelected(int newsel) override;
	virtual void finishedSelection(int sel) override;
};

class ItemUseScene 
	: public VideoLikeScene
{
private:
	int invIndex;
	sf::RectangleShape rext;
	sf::RectangleShape rint;
	ItemUseTS ts;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	ItemUseScene(int invIndex);

	virtual void update(float dt) override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;
	
	friend class ItemUseTS;
};

