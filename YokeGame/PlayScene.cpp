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
	playerSpeed = 150.0f;

	enemySpeed = 150.0f;
	enemySpawnInterval = 0.5f;
	enemySpawnTimer = 0.0f;

	score = 0.0;
	isFinished = false;
	enemies.clear();

	if( playerImage == -1 )
		playerImage = LoadGraph( "image/cat.png" );
	if( enemyImage == -1 )
		enemyImage = LoadGraph( "image/snake.png" );
	if( scoreFont == -1 )
		scoreFont = CreateFontToHandle( "ÉÅÉCÉäÉI", 64, 0, DX_FONTTYPE_NORMAL );

}

void PlayScene::Update( float deltaTime )
{
	// ÉvÉåÉCÉÑÅ[à⁄ìÆ
	if( CheckHitKey( KEY_INPUT_LEFT ) )
	{
		player.x -= playerSpeed * deltaTime;
	}
	else if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		player.x += playerSpeed * deltaTime;
	}

	// àÍíËéûä‘å„ÅAìGê∂ê¨
	enemySpawnTimer += deltaTime;
	if( enemySpawnTimer > enemySpawnInterval )
	{
		CreateEnemy();
	}

	// ìGóéâ∫
	for( auto& enemy : enemies )
	{
		enemy.y += enemySpeed * deltaTime;
	}

	// ìGçÌèú
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

	// ìñÇΩÇËîªíË
	if( IsHit() )
	{
		isFinished = true;
	}

	// ÉXÉRÉAâ¡éZ
	score += deltaTime;
}

void PlayScene::Draw()
{
	// îwåi
	DrawBackground();

	// îLï`âÊ
	DrawPlayer(playerImage);

	// é÷ÇΩÇøï`âÊ
	DrawEnemies(enemyImage);

	// ÉXÉRÉAï\é¶
	DrawScore();
}

// ìGÇÃê∂ê¨
void PlayScene::CreateEnemy()
{
	enemySpawnTimer -= enemySpawnInterval;
	Position enemy;
	enemy.x = rand() % WINDOW_WIDTH;
	enemy.y = -CHARACTER_SIZE;
	enemies.push_back(enemy);
}

void PlayScene::DrawPlayer(int is_draw_collider)
{
	if (is_draw_collider <= 0) return; // ï`âÊÇµÇ»Ç¢
	// ÉvÉåÉCÉÑÅ[ÇÃìñÇΩÇËîªíËÇï`âÊ
	if (is_draw_collider == 2)
	{
		DrawCircle((int)player.x, (int)player.y, CHARACTER_SIZE / 2, GetColor(255, 0, 0), TRUE);
		return;
	}
	// ÉvÉåÉCÉÑÅ[ÇÃâÊëúÇï`âÊ
	DrawExtendGraph((int)(player.x - CHARACTER_SIZE / 2), (int)(player.y - CHARACTER_SIZE / 2), 
		(int)(player.x + CHARACTER_SIZE / 2) + 1, (int)(player.y + CHARACTER_SIZE / 2) + 1,
		playerImage, TRUE);
}

void PlayScene::DrawEnemies(int is_draw_collider)
{
	if (is_draw_collider <= 0) return; // ï`âÊÇµÇ»Ç¢
	for (auto& enemy : enemies)
	{
		// ìGÇÃìñÇΩÇËîªíËÇï`âÊ
		if (is_draw_collider == 2)
		{
			DrawCircle((int)enemy.x, (int)enemy.y, CHARACTER_SIZE / 2, GetColor(0, 0, 255), TRUE);
			continue;
		}
		// ìGÇÃâÊëúÇï`âÊ
		DrawExtendGraph((int)(enemy.x - CHARACTER_SIZE / 2), (int)(enemy.y - CHARACTER_SIZE / 2),
			(int)(enemy.x + CHARACTER_SIZE / 2) + 1, (int)(enemy.y + CHARACTER_SIZE / 2) + 1,
			enemyImage, TRUE);
	}
}

void PlayScene::DrawBackground()
{
	// îwåiÇï`âÊ
	DrawBox(0, 0, WINDOW_WIDTH, GROUND_Y, GetColor(0, 191, 255), TRUE); // ãÛ
	DrawBox(0, GROUND_Y, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(34, 139, 34), TRUE); // ínñ 
}

void PlayScene::DrawScore()
{
	// ÉXÉRÉAÇï`âÊ
	int scoreWidth = GetDrawFormatStringWidthToHandle(scoreFont, "%.3f", score);
	DrawFormatStringToHandle(WINDOW_WIDTH - scoreWidth, 30, GetColor(255, 255, 255), scoreFont, "%.3f", score);
}


// ìñÇΩÇËîªíË
bool PlayScene::IsHit( )
{
	for( auto& enemy : enemies )
	{
		// ãÈå`ÇÃìñÇΩÇËîªíË
		float dx = player.x - enemy.x;
		float dy = player.y - enemy.y;

		if( ( dx * dx ) + ( dy * dy ) <= CHARACTER_SIZE * CHARACTER_SIZE )
		{
			return true;
		}
	}

	return false;
}