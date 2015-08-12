#include "Game.h"

Game* Game::m_instance = nullptr;

bool Game::InitGame(HINSTANCE hInst, HWND hWnd)
{

	renderer = D3D11Renderer::Instance();
	g_hInst = hInst;
	g_hWnd = hWnd;
	GetClientRect(g_hWnd, &g_rect);

	return renderer->Init(g_hWnd);
}

void Game::Start()
{
	//temp for test

	// add a game object in the scene
	GameObject* go = new GameObject();
	RenderingComponent* rc = new RenderingComponent();
	rc->Prepare();
	go->AddComponent(rc);
	go->parent = GameObject::ROOTNODE;

	//add a camera
	GameObject* camera = new GameObject();
	XMFLOAT4 pos = XMFLOAT4(0.0f, 1.0f, -2.0f, 0.0f);
	XMFLOAT4 target = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	XMFLOAT4 up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	CameraComponent* cc = new CameraComponent(pos, target, up, XM_PIDIV2, 0.1, 100);
	camera->AddComponent(cc);
	camera->parent = GameObject::ROOTNODE;

	CameraManager::Instance()->SetMainCamera(cc); 
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

Game::Game()
{
}

Game::~Game()
{
}
