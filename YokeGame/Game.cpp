// Game.cpp
#include <DxLib.h>
#include "Global.h"
#include "Game.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"


Game::Game() : currentIndex( 0 )
{
	scenes.push_back( new TitleScene() );
    scenes.push_back( new PlayScene() );
    scenes.push_back( new ResultScene() );
}

Game::~Game()
{
	for( auto scene : scenes )
	{
		delete scene;
	}
	scenes.clear();
}

void Game::Run()
{
	SetGraphMode( WINDOW_WIDTH, WINDOW_HEIGHT, 32 );
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)
		return;

	SetDrawScreen(DX_SCREEN_BACK);

	scenes[currentIndex]->Init();
	int prevTime = GetNowCount();

	while( ProcessMessage() != -1 )
	{
		ClearDrawScreen();
		int now = GetNowCount();
		float deltaTime = (now - prevTime) / 1000.0f;
		prevTime = now;

		scenes[currentIndex]->Update( deltaTime );
		scenes[currentIndex]->Draw();

		if( scenes[currentIndex]->IsFinished() )
		{
			currentIndex = (currentIndex + 1) % scenes.size();
			scenes[currentIndex]->Init();
		}
		WaitTimer(16); // 1ƒ~ƒŠ•b‘Ò‹@
		ScreenFlip();
	}

	DxLib_End();
}
