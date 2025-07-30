// Game.h
#pragma once
#include "SceneBase.h"
#include <vector>

class Game {
private:
	std::vector<SceneBase*> scenes;
	int currentIndex;

public:
	Game();
	~Game();
	void Run();
};
