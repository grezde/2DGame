#pragma once
#include <SFML/Graphics.hpp>

class Button
	: public sf::Drawable
{
private:
	static sf::Texture* texture;
	static const int OFFSETS[4];

	sf::FloatRect position;
	bool selected;
	bool enabled;

	sf::Sprite left;
	sf::Sprite right;
	sf::Sprite center;
	sf::Text label;

	float textPercent = 0.3f;
	float paddingTop = 5;

private:
	void remake();

public:
	Button();
	Button(std::string text, sf::FloatRect position);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void draw(sf::RenderWindow* window);

	void setSelected(bool selected);
	void setEnabled(bool enabled);
	void setRect(sf::FloatRect position);
	void setText(std::string text);
	void setPaddingTop(float pt);

	inline bool isEnabled() { return enabled; }
};

