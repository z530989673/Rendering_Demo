#include "Game.h"

bool Game::InitGame()
{
	return renderer->Init(g_hWnd);
}

void Game::Start()
{
	//temp for test
	//EffectManager::Instance()->AddRenderingEffect(EffectManager::Instance()->defaultEffect);

	GameObject* go = new GameObject();
	RenderingComponent* rc = new RenderingComponent();
	rc->Prepare();
	go->AddComponent(rc);

	go->parent = GameObject::ROOTNODE;

}

void Game::Update()
{
	GameObject::ROOTNODE->Update();
	renderer->Draw();
}

void Game::ExitGame()
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
