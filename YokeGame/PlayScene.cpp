// PlayScene.cpp
#include <DxLib.h>
#include "Global.h"
#include "PlayScene.h"



int PlayScene:: playerImage = -1;
int PlayScene:: enemyImage = -1;
int PlayScene:: scoreFont = -1;

PlayScene::PlayScene()
	: player( { (WINDOW_WIDTH / 2), (GROUND_Y-CHARACTER_SIZE/2) } ), playerSpeed(150.0f),
	  enemySpeed(0.0f), enemySpawnInterval(10.0f), enemySpawnTimer(0.0f),
	  score(0.0)
{
}

void PlayScene::Init()
{
	player.x = WINDOW_WIDTH / 2;
	player.y = GROUND_Y-CHARACTER_SIZE/2;
	//課題02 プレイヤーの移動速度を設定
	playerSpeed = 0.0f;

	//課題03 敵の落下速度を設定
	enemySpeed = 0.0f;
	enemySpawnInterval = 0.5f;
	enemySpawnTimer = 0.0f;

	score = 0.0;
	isFinished = false;
	enemies.clear();

	if( playerImage == -1 )
		//#課題01 LoadGraph関数を使って画像を読み込む
		playerImage = LoadGraph( "image/XXX.png" );
	if( enemyImage == -1 )
		//#課題01 LoadGraph関数を使って画像を読み込む
		enemyImage = LoadGraph( "image/XXXX.png" );
	if( scoreFont == -1 )
		scoreFont = CreateFontToHandle( "メイリオ", 64, 0, DX_FONTTYPE_NORMAL );

}

void PlayScene::Update( float deltaTime )
{
	// プレイヤー移動
	if( CheckHitKey( KEY_INPUT_LEFT ) )
	{
		player.x -= playerSpeed * deltaTime;
	}
	else if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		player.x += playerSpeed * deltaTime;
	}

	//課題04 敵の生成タイマーを加算
	enemySpawnTimer;

	if( enemySpawnTimer > enemySpawnInterval )
	{
		CreateEnemy();
	}

	// 敵落下
	for( auto& enemy : enemies )
	{
		enemy.y += enemySpeed * deltaTime;
	}

	// 敵削除
	for( auto it = enemies.begin(); it != enemies.end(); )
	{
		if( it->y > GROUND_Y - CHARACTER_SIZE / 2 )
		{
			it = enemies.erase( it );
		}
		else
		{
			it++;
		}
	}

	//課題06 当たり判定
	if( IsHit() )
	{
		ClearEnemies();
		//課題07 リザルト画面へ移行
		//->ここに移行処理を追加
	}

	//課題05 スコアの値を更新
	score;
}

void PlayScene::Draw()
{
	// 背景
	DrawBackground();

	// 猫描画
	DrawPlayer(playerImage, false);

	// 蛇たち描画
	DrawEnemies(enemyImage, false);

	// スコア表示
	DrawScore();
}

// 敵の生成
void PlayScene::CreateEnemy()
{
	enemySpawnTimer -= enemySpawnInterval;
	Position enemy;
	enemy.x = rand() % WINDOW_WIDTH;
	enemy.y = -CHARACTER_SIZE;
	enemies.push_back(enemy);
}


void PlayScene::DrawPlayer(int handle, bool is_draw_collider)
{
	if (is_draw_collider <= 0) return; // 描画しない
	// プレイヤーの当たり判定を描画
	if (is_draw_collider)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明に設定
		DrawCircle((int)player.x, (int)player.y, CHARACTER_SIZE / 2, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを元に戻す
		return;
	}
	// プレイヤーの画像を描画
	DrawExtendGraph((int)(player.x - CHARACTER_SIZE / 2), (int)(player.y - CHARACTER_SIZE / 2),
		(int)(player.x + CHARACTER_SIZE / 2) + 1, (int)(player.y + CHARACTER_SIZE / 2) + 1,
		handle, TRUE);
}

void PlayScene::DrawEnemies(int handle, bool is_draw_collider)
{
	if (is_draw_collider <= 0) return; // 描画しない
	for (auto& enemy : enemies)
	{
		// 敵の当たり判定を描画
		if (is_draw_collider)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明に設定
			DrawCircle((int)enemy.x, (int)enemy.y, CHARACTER_SIZE / 2, GetColor(0, 0, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンドモードを元に戻す
			continue;
		}
		// 敵の画像を描画
		DrawExtendGraph((int)(enemy.x - CHARACTER_SIZE / 2), (int)(enemy.y - CHARACTER_SIZE / 2),
			(int)(enemy.x + CHARACTER_SIZE / 2) + 1, (int)(enemy.y + CHARACTER_SIZE / 2) + 1,
			handle, TRUE);
	}
}

void PlayScene::DrawBackground()
{
	// 背景を描画
	DrawBox(0, 0, WINDOW_WIDTH, GROUND_Y, GetColor(0, 191, 255), TRUE); // 空
	DrawBox(0, GROUND_Y, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(34, 139, 34), TRUE); // 地面
}

void PlayScene::DrawScore()
{
	// スコアを描画
	int scoreWidth = GetDrawFormatStringWidthToHandle(scoreFont, "%.3f", score);
	DrawFormatStringToHandle(WINDOW_WIDTH - scoreWidth, 30, GetColor(255, 255, 255), scoreFont, "%.3f", score);
}


// 当たり判定
bool PlayScene::IsHit( )
{
	for( auto& enemy : enemies )
	{
		// 矩形の当たり判定
		float dx = player.x - enemy.x;
		float dy = player.y - enemy.y;

		if( ( dx * dx ) + ( dy * dy ) <= CHARACTER_SIZE * CHARACTER_SIZE )
		{
			return true;
		}
	}

	return false;
}