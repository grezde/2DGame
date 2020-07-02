#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.h"

class Game
{
private:
	sf::RenderWindow* window;
	std::vector<Scene*> scenes;
	static Game* curentGame;

	bool exit;
	Scene* next;

public: 
	static const int HEIGHT = 600;
	static const int WIDTH  = 800;

public:
	Game();
	void run(Scene* initialScene);
	void setNextScene(bool shouldExit, Scene* nextScene = nullptr);
	inline static Game* curent() { return curentGame; }
	~Game();
};

