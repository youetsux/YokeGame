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
	//�\���p�֐�
	// is_draw_collider: 0<=�`�悵�Ȃ�, 1=�`�悷�� 2=�����蔻��̂ݕ`�悷��
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
