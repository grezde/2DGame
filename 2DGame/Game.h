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

	bool exit = false;
	Scene* next = nullptr;
	bool updateAll = false;
	bool clearAll = false;

public: 
	static const int HEIGHT = 600;
	static const int WIDTH  = 800;

public:
	Game();
	void run(Scene* initialScene);
	void setNextScene(bool shouldExit, Scene* nextScene = nullptr);
	inline void updateAllScenes() { updateAll = true; };
	inline void clearAllScenes() { clearAll = true; }
	inline static Game* curent() { return curentGame; }
	~Game();
};

