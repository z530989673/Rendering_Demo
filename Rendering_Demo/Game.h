#pragma once

#include "D3D11Render.h"

class Game
{
public:
	Game(HINSTANCE hInst, HWND hWnd);
	~Game();

	bool initGame();

	void Update();

	void exit();

private:
	D3D11Render*			render; 
	HINSTANCE               g_hInst;
	HWND                    g_hWnd;
};

