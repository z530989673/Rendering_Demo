#pragma once

#include "D3D11Renderer.h"

#include "Includes.h"

#include "Objects/GameObject.h"
#include "EffectManager.h"
#include "Components/RenderingComponent.h"

class Game
{
public:
	Game(HINSTANCE hInst, HWND hWnd);
	~Game();

	bool InitGame();
	void Start();
	void Update();
	void ExitGame();

private:
	D3D11Renderer*			renderer; 
	HINSTANCE               g_hInst;
	HWND                    g_hWnd;
};

