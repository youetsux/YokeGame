// TitleScene.cpp
#include <DxLib.h>
#include "Global.h"
#include "TitleScene.h"


int TitleScene:: bgImage = -1;

TitleScene::TitleScene()
{
	
}

void TitleScene::Init()
{
	isFinished = false;

	if( bgImage == -1 )
		bgImage = LoadGraph( "image/Title.png" );
}

void TitleScene::Update( float deltaTime )
{
	if( CheckHitKey( KEY_INPUT_SPACE ) )
	{
		isFinished = true;
	}
}

void TitleScene::Draw()
{
	DrawGraph( 0, 0, bgImage, TRUE );
}
