#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.h"

class Game
	: public sf::Drawable
{
private:
	sf::RenderWindow* window;
	std::vector<Scene*> scenes;
	std::vector<Scene*> weakscenes;
	static Game* curentGame;

	bool exit = false;
	Scene* next = nullptr;
	bool updateAll = false;
	bool clearAll = false;

public: 
	static const int HEIGHT = 600;
	static const int WIDTH  = 800;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Game();
	~Game();
	void run(Scene* initialScene);
	void setNextScene(bool shouldExit, Scene* nextScene = nullptr);
	void drawOnTarget(sf::RenderTarget& target, sf::RenderStates states, int nScenes);

	inline void updateAllScenes() { updateAll = true; };
	inline void clearAllScenes() { clearAll = true; }
	inline static Game* curent() { return curentGame; }

};

