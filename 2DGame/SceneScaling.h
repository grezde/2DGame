#pragma once
#include "Scene.h"

class VideoLikeScene
	: public Scene
{
public:
	virtual void onWindowResize(sf::Vector2i size) override;
};

