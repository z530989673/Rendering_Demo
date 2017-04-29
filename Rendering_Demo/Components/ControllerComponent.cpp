#include "ControllerComponent.h"

void ControllerComponent::Update()
{
	if (InputManager::Instance()->GetKeyHold('W'))
	{
		gameObject->MoveForward(m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('S'))
	{
		gameObject->MoveBackward(m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('A'))
	{
		gameObject->MoveLeft(m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('D'))
	{
		gameObject->MoveRight(m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('Q'))
	{
		gameObject->MoveDown(m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('E'))
	{
		gameObject->MoveUp(m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold(VK_UP))
	{
		gameObject->RotateX(-m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold(VK_DOWN))
	{
		gameObject->RotateX(m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold(VK_LEFT))
	{
		gameObject->RotateY(-m_moveSpeed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold(VK_RIGHT))
	{
		gameObject->RotateY(m_moveSpeed * Timer::GetDeltaTime());
	}
}


ControllerComponent::ControllerComponent()
{
}


ControllerComponent::~ControllerComponent()
{
}
