// PlayScene.h
#pragma once
#include "SceneBase.h"
#include <vector>

struct Position
{
    float x;
    float y;
};

class PlayScene : public SceneBase
{
private:
	Position player;
	float playerSpeed;

	float enemySpeed;
	float enemySpawnInterval;
	float enemySpawnTimer;

	double score;

	std::vector<Position> enemies;

	static int playerImage;
	static int enemyImage;
	static int scoreFont;


public:
	PlayScene();
	void Init() override;
	void Update(float deltaTime) override;
	void Draw() override;
	bool IsHit();
	void CreateEnemy();
};
