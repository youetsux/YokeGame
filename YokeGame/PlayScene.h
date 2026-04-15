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
	//表示用関数
	// is_draw_collider: 0<=描画しない, 1=描画する 2=当たり判定のみ描画する
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
