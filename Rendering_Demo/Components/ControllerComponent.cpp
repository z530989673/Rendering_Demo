#include "ControllerComponent.h"

void ControllerComponent::Update()
{
	if (InputManager::Instance()->GetKeyHold('W'))
	{
		gameObject->MoveForward(m_speed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('S'))
	{
		gameObject->MoveBackward(m_speed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('A'))
	{
		gameObject->MoveLeft(m_speed * Timer::GetDeltaTime());
	}
	if (InputManager::Instance()->GetKeyHold('D'))
	{
		gameObject->MoveRight(m_speed * Timer::GetDeltaTime());
	}
}


ControllerComponent::ControllerComponent()
{
}


ControllerComponent::~ControllerComponent()
{
}
