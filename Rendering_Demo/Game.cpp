#include "Game.h"

bool Game::initGame()
{
	return render->InitDevice(g_hWnd);
}

void Game::Update()
{
	render->Render();
}

void Game::exit()
{
	render->CleanupDevice();
}

Game::Game(HINSTANCE hInst, HWND hWnd)
{
	render = new D3D11Render();
	g_hInst = hInst;
	g_hWnd = hWnd;
}


Game::~Game()
{
}
