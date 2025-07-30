// main.cpp
#include <Windows.h>
#include "Game.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	Game game;
	game.Run();
	return 0;
}
