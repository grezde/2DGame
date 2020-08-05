#pragma once
#include "SceneScaling.h"

class PopupScene
	: public TopRightScene
{
private:
	float x = 0;
	float t = 0;

protected:
	float width = 300;
	float time1 = 0.3f;
	float time2 = 1.0f;
	float time3 = 0.2f;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	virtual void normalDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

public:
	PopupScene();

	virtual void update(float dt) override;
};