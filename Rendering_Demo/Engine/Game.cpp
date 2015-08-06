#include "Game.h"

bool Game::initGame()
{
	return renderer->InitDevice(g_hWnd);
}

void Game::Update()
{
	GameObject::ROOTNODE.update();
	renderer->Draw();
}

void Game::exitGame()
{
	renderer->CleanupDevice();
}

Game::Game(HINSTANCE hInst, HWND hWnd)
{
	renderer = D3D11Renderer::Instance();
	g_hInst = hInst;
	g_hWnd = hWnd;
}


Game::~Game()
{
}
