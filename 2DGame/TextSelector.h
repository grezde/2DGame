#pragma once
#include "GameElement.h"

class TextSelector :
	public IKeyListener
{
private:
	std::vector<sf::Text> labels;
	float charsize;
	float linesp;
	int selected;

public:
	static const sf::Color SELECTED;
	static const sf::Color UNSELECTED;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	virtual void onSelected(int newsel) = 0;
	virtual void finishedSelection(int sel) = 0;

public:
	TextSelector(float charSize, float lineSpacing);
	void setStrings(std::vector<std::string> values);
	void setPosition(sf::Vector2f pos);
	void setSelected(int newsel);

	sf::Vector2f getSize();
	inline int nChoices() { return labels.size(); }
	inline int getSelected() { return selected; }

	virtual void onKeyPress(sf::Keyboard::Key key) override;
};

