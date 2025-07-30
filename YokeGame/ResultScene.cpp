// ResultScene.cpp
#include <DxLib.h>
#include "Global.h"
#include "ResultScene.h"

int ResultScene:: bgImage = -1;

ResultScene::ResultScene( )
{
}

void ResultScene::Init()
{
	isFinished = false;

	if( bgImage == -1 )
		bgImage = LoadGraph( "image/Result.png" );
}

void ResultScene::Update( float deltaTime )
{
	if( CheckHitKey( KEY_INPUT_SPACE ) )
	{
		isFinished = true;
	}
}

void ResultScene::Draw()
{
	DrawGraph( 0, 0, bgImage, TRUE );
}

