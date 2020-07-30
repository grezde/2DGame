#pragma once
#include "Scene.h"
#include "Button.h"
/*
class ButtonSet : 
	public IGameElement 
{
private:
	std::vector<Button> buttons;
	int selindex;
	float buttonSpace = 0.5f;

	static const float PRESS_INTERVAL;
	float sincePress;

protected:
	int selectedIndex() { return selindex; }

public:
	ButtonSet(std::vector<std::string> options, sf::FloatRect bounds);

	virtual void finsihedSelection(int selected) = 0;
	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
}; */

class ButtonSet : public IGameElement
{
private:
	std::vector<Button> buttons;
	int selindex;
	float buttonSpace = 0.5f;
	
	static const float PRESS_INTERVAL;
	float sincePress;

protected:
	int selectedIndex() { return selindex; }

public:
	ButtonSet(std::vector<std::string> options, sf::FloatRect bounds);

	virtual void finsihedSelection(int selected) = 0;
	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};

class ButtonSetScene : public ButtonSet, public Scene
{
public:
	ButtonSetScene(std::vector<std::string> options, sf::FloatRect bounds)
		: ButtonSet(options, bounds), Scene() 
	{}
};
