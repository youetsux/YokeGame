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
		scoreFont = CreateFontToHandle( "���C���I", 64, 0, DX_FONTTYPE_NORMAL );

}

void PlayScene::Update( float deltaTime )
{
	// �v���C���[�ړ�
	if( CheckHitKey( KEY_INPUT_LEFT ) )
	{
		player.x -= playerSpeed * deltaTime;
	}
	else if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		player.x += playerSpeed * deltaTime;
	}

	// ��莞�Ԍ�A�G����
	enemySpawnTimer += deltaTime;
	if( enemySpawnTimer > enemySpawnInterval )
	{
		CreateEnemy();
	}

	// �G����
	for( auto& enemy : enemies )
	{
		enemy.y += enemySpeed * deltaTime;
	}

	// �G�폜
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

	// �����蔻��
	if( IsHit() )
	{
		isFinished = true;
	}

	// �X�R�A���Z
	score += deltaTime;
}

void PlayScene::Draw()
{
	// �w�i
	DrawBox( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 191, 255), TRUE); // ��
	DrawBox( 0, GROUND_Y, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(34, 139, 34), TRUE); // �n��

	// �L�`��
	// DrawCircle( (int)player.x, (int)player.y, CHARACTER_SIZE/2, GetColor( 255, 255, 0 ), TRUE);
	DrawExtendGraph( (int)(player.x - CHARACTER_SIZE / 2 ), (int)(player.y - CHARACTER_SIZE / 2 ), (int)(player.x + CHARACTER_SIZE / 2 )+1, (int)(player.y + CHARACTER_SIZE / 2 )+1, playerImage, TRUE );

	// �ւ����`��
	for( auto& enemy : enemies )
	{
		// DrawCircle( (int)enemy.x, (int)enemy.y, CHARACTER_SIZE/2, GetColor( 0, 0, 255 ), TRUE);
		DrawExtendGraph( (int)(enemy.x - CHARACTER_SIZE / 2 ), (int)(enemy.y - CHARACTER_SIZE / 2 ), (int)(enemy.x + CHARACTER_SIZE / 2 )+1, (int)(enemy.y + CHARACTER_SIZE / 2 )+1, enemyImage, TRUE );
	}

	// �X�R�A�\��
	//DrawFormatString( 420, 50, GetColor( 255, 255, 255 ), "%.3f", score );
	int scoreWidth = GetDrawFormatStringWidthToHandle( scoreFont, "%.3f", score );
	DrawFormatStringToHandle( WINDOW_WIDTH - scoreWidth, 30, GetColor( 255, 255, 255 ), scoreFont, "%.3f", score );
}

// �G�̐���
void PlayScene::CreateEnemy()
{
	enemySpawnTimer -= enemySpawnInterval;
	Position enemy;
	enemy.x = rand() % WINDOW_WIDTH;
	enemy.y = -CHARACTER_SIZE;
	enemies.push_back(enemy);
}

// �����蔻��
bool PlayScene::IsHit( )
{
	for( auto& enemy : enemies )
	{
		// ��`�̓����蔻��
		float dx = player.x - enemy.x;
		float dy = player.y - enemy.y;

		if( ( dx * dx ) + ( dy * dy ) <= CHARACTER_SIZE * CHARACTER_SIZE )
		{
			return true;
		}
	}

	return false;
}