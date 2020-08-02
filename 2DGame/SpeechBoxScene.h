#pragma once
#include <vector>
#include "BasicSpeechScene.h"

class SpeechBoxScene 
	: public BasicSpeechScene
{
private:
	sf::Texture boxTex;
	sf::Sprite boxSpr;
	
public:
	static const float SCALE;

	static const float LINE_SPACING;
	static const float PADDING_X;
	static const float PADDING_Y;
	static const float CHOICE_PADDING_X;
	static const float CHOICE_PADDING_Y;
	static const int CHAR_SIZE;

public:
	SpeechBoxScene(std::vector<std::string> data);
	
	void draw(sf::RenderWindow* window) override;
	void update(float dt) override;

	virtual void styleDisplayText(sf::Text& t) override;
	virtual void styleOptionsText(int i, sf::Text& t) override;
	virtual void stylePromptText(sf::Text& t) override;
	virtual void styleFace(Face& face) override;
};

