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
public:
	PlayScene();
	void Init() override;
	void Update(float deltaTime) override;
	void Draw() override;
	bool IsHit();
	void CreateEnemy();
	//ï\é¶ópä÷êî
	// is_draw_collider: 0<=ï`âÊÇµÇ»Ç¢, 1=ï`âÊÇ∑ÇÈ 2=ìñÇΩÇËîªíËÇÃÇ›ï`âÊÇ∑ÇÈ
 	void DrawPlayer(int handle, bool is_draw_collider);
	void DrawEnemies(int handle, bool is_draw_collider);
	void DrawBackground();
	void DrawScore();
	void GoToResultScene() { isFinished = true; }
	void ClearEnemies() { enemies.clear(); }
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



};
