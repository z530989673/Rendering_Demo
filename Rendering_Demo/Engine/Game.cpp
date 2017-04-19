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
	Timer::Start();
	LightManager::Instance();

	//temp for test

	LightManager::Instance()->SetAmbientLightColor(0.9f, 0.9f, 0.9f);

	// add a box in the scene
	GameObject* go = new GameObject();
	RenderingComponent* rc = RenderingComponent::CreateStandardBox();
	rc->Prepare();
	go->AddComponent(rc);
	go->SetParent(GameObject::ROOTNODE);


	//add a camera
	XMFLOAT4 pos = XMFLOAT4(3.0f, 3.0f, -3.0f, 0.0f);
	XMFLOAT4 target = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	XMFLOAT4 up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
	GameObject* camera = CameraManager::Instance()->CreateCamera(pos, target, up, XM_PI / 2, 0.1f, 100);
	CameraComponent* cc = camera->GetComponent<CameraComponent>();
	CameraManager::Instance()->SetMainCamera(cc);
	ControllerComponent* ctlc = new ControllerComponent();
	camera->AddComponent(ctlc);

	// add a directional light
	XMFLOAT4 lightPos = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	Light::LIGHTTYPE lightType = Light::LIGHTTYPE::Directional;
	XMFLOAT4 lightDir = XMFLOAT4(-2.0f, -1.0f, -1.0f, 0.0f);
	LightManager::Instance()->CreateLight(lightPos, lightType, lightDir);

	// add a spot light
	XMFLOAT4 spotLightPos = XMFLOAT4(-0.0f, 1.5f, -1.6f, 0.0f);
	Light::LIGHTTYPE spotLightType = Light::LIGHTTYPE::Point;
	XMFLOAT4 spotLightDir = XMFLOAT4(-2.0f, -1.0f, -1.0f, 0.0f);
	XMFLOAT4 spotLightColor = XMFLOAT4(3.0f, 3.0f, 0.0f, 0.0f);
	LightManager::Instance()->CreateLight(spotLightPos, spotLightType, spotLightDir, true, spotLightColor);
}

void Game::Update()
{
	Timer::Update();
	InputManager::Instance()->Update();
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
