#pragma once
#include "SceneScaling.h"
#include "TextSelector.h"

class ItemUseTS
	: public TextSelector
{

};

class ItemUseScene 
	: public VideoLikeScene
{
private:
	sf::RectangleShape rext;
	sf::RectangleShape rint;

public:
	ItemUseScene();


};

