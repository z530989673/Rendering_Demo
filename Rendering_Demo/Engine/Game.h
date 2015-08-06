#pragma once

#include "D3D11Renderer.h"

#include "Includes.h"

class Game
{
public:
	Game(HINSTANCE hInst, HWND hWnd);
	~Game();

	bool initGame();
	void Update();
	void exitGame();

private:
	D3D11Renderer*			renderer; 
	HINSTANCE               g_hInst;
	HWND                    g_hWnd;
};

