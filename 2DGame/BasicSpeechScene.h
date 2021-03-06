#pragma once
#include "SceneScaling.h"
#include "SpeechManager.h"
#include "Face.h"

class BasicSpeechScene
	: public VideoLikeScene, public SpeechManager
{
public:
	static const float INTERVAL;
	static const float FAST_INTERVAL;
	static const float LONG_INTERVAL;
	static const float SELECTION_INTERVAL;

protected:
	sf::Color textColor;
	sf::Color selectedColor; 

	sf::Text label;
	sf::Text submitlabel;
	std::vector<sf::Text> optlabs;
	int selectedOptionIndex;
	float sinceLastPress;

	Face* face = nullptr;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	BasicSpeechScene(std::vector<std::string> lines);
	BasicSpeechScene(std::string sequenceFilename);
	~BasicSpeechScene();

	virtual void update(float dt) override;
	virtual void onTextEntered(char character) override;

	virtual void styleDisplayText(sf::Text& t) = 0;
	virtual void styleOptionsText(int i, sf::Text& t) = 0;
	virtual void stylePromptText(sf::Text& t) = 0;
	virtual void styleFace(Face& face) = 0;
	virtual void onFinished() = 0;

};

