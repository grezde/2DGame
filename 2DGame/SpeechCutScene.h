#pragma once
#include "BasicSpeechScene.h"

class SpeechCutScene :
	public BasicSpeechScene
{
private:


public:
	SpeechCutScene(std::vector<std::string> data);
	SpeechCutScene(std::string filename);

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;

	virtual void styleDisplayText(sf::Text& t) override;
	virtual void styleOptionsText(int i, sf::Text& t) override;
	virtual void stylePromptText(sf::Text& t) override;

};

