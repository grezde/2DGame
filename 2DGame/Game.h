#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.h"

class Game
{
private:
	sf::RenderWindow* window;
	std::vector<Scene*> scenes;

public: 
	static const int HEIGHT = 600;
	static const int WIDTH  = 800;

public:
	Game();
	void run(Scene* initialScene);
	~Game();
};

