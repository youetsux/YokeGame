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
	//�ۑ�02 �v���C���[�̈ړ����x��ݒ�
	playerSpeed = 0.0f;

	//�ۑ�03 �G�̗������x��ݒ�
	enemySpeed = 0.0f;
	enemySpawnInterval = 0.5f;
	enemySpawnTimer = 0.0f;

	score = 0.0;
	isFinished = false;
	enemies.clear();

	if( playerImage == -1 )
		//#�ۑ�01 LoadGraph�֐����g���ĉ摜��ǂݍ���
		playerImage = LoadGraph( "image/XXX.png" );
	if( enemyImage == -1 )
		//#�ۑ�01 LoadGraph�֐����g���ĉ摜��ǂݍ���
		enemyImage = LoadGraph( "image/XXXX.png" );
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

	//�ۑ�04 �G�̐����^�C�}�[�����Z
	enemySpawnTimer;

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

	//�ۑ�06 �����蔻��
	if( IsHit() )
	{
		ClearEnemies();
		//�ۑ�07 ���U���g��ʂֈڍs
		//->�����Ɉڍs������ǉ�
	}

	//�ۑ�05 �X�R�A�̒l���X�V
	score;
}

void PlayScene::Draw()
{
	// �w�i
	DrawBackground();

	// �L�`��
	DrawPlayer(playerImage, false);

	// �ւ����`��
	DrawEnemies(enemyImage, false);

	// �X�R�A�\��
	DrawScore();
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


void PlayScene::DrawPlayer(int handle, bool is_draw_collider)
{
	if (is_draw_collider <= 0) return; // �`�悵�Ȃ�
	// �v���C���[�̓����蔻���`��
	if (is_draw_collider)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // �������ɐݒ�
		DrawCircle((int)player.x, (int)player.y, CHARACTER_SIZE / 2, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �u�����h���[�h�����ɖ߂�
		return;
	}
	// �v���C���[�̉摜��`��
	DrawExtendGraph((int)(player.x - CHARACTER_SIZE / 2), (int)(player.y - CHARACTER_SIZE / 2),
		(int)(player.x + CHARACTER_SIZE / 2) + 1, (int)(player.y + CHARACTER_SIZE / 2) + 1,
		handle, TRUE);
}

void PlayScene::DrawEnemies(int handle, bool is_draw_collider)
{
	if (is_draw_collider <= 0) return; // �`�悵�Ȃ�
	for (auto& enemy : enemies)
	{
		// �G�̓����蔻���`��
		if (is_draw_collider)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // �������ɐݒ�
			DrawCircle((int)enemy.x, (int)enemy.y, CHARACTER_SIZE / 2, GetColor(0, 0, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �u�����h���[�h�����ɖ߂�
			continue;
		}
		// �G�̉摜��`��
		DrawExtendGraph((int)(enemy.x - CHARACTER_SIZE / 2), (int)(enemy.y - CHARACTER_SIZE / 2),
			(int)(enemy.x + CHARACTER_SIZE / 2) + 1, (int)(enemy.y + CHARACTER_SIZE / 2) + 1,
			handle, TRUE);
	}
}

void PlayScene::DrawBackground()
{
	// �w�i��`��
	DrawBox(0, 0, WINDOW_WIDTH, GROUND_Y, GetColor(0, 191, 255), TRUE); // ��
	DrawBox(0, GROUND_Y, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(34, 139, 34), TRUE); // �n��
}

void PlayScene::DrawScore()
{
	// �X�R�A��`��
	int scoreWidth = GetDrawFormatStringWidthToHandle(scoreFont, "%.3f", score);
	DrawFormatStringToHandle(WINDOW_WIDTH - scoreWidth, 30, GetColor(255, 255, 255), scoreFont, "%.3f", score);
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