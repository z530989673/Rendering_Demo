#pragma once

#include "D3D11Renderer.h"

#include "Includes.h"

#include "Objects/GameObject.h"
#include "EffectManager.h"
#include "CameraManager.h"
#include "Components/RenderingComponent.h"
#include "Components/CameraComponent.h"

class D3D11Renderer;

class Game
{
public:
	static Game* Instance() {
		if (m_instance == nullptr)
			m_instance = new Game();
		return m_instance;
	}

	~Game();

	bool InitGame(HINSTANCE hInst, HWND hWnd);
	void Start();
	void Update();
	void ExitGame();
	RECT GetScreenRect(){ return g_rect; }

private:
	static Game* m_instance;
	D3D11Renderer*			renderer; 
	HINSTANCE               g_hInst;
	HWND                    g_hWnd;
	RECT					g_rect;
	Game();
};

