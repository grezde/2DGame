#pragma once
#include "PopupScene.h"

class SavePopupScene :
	public PopupScene
{
private:
	sf::Sprite spr;
	sf::Text highlighted;
	sf::Text text2;

protected:
	virtual void normalDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	SavePopupScene(std::string name);
	
};

