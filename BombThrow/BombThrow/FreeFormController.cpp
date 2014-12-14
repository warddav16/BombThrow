#include "FreeFormController.h"

#include "GameObject.h"
#include "InputManager.h"
#include "Transform.h"

const float SPEED = 5.f;
const float ROT_SPEED = 1.f;

FreeFormController::FreeFormController(GameObject* gO) : CustomBehavior(gO)
{

}

FreeFormController::~FreeFormController(void)
{

}

void FreeFormController::Update(float delta)
{
	if(InputManager::Instance().GetKey(KeyCode::W))
	{
		m_gameObject->GetTransform()->Translate(
			m_gameObject->GetTransform()->Forward() * SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::S))
	{
		m_gameObject->GetTransform()->Translate(
			-m_gameObject->GetTransform()->Forward() * SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::A))
	{
		m_gameObject->GetTransform()->Translate(
			-m_gameObject->GetTransform()->Right() * SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::D))
	{
		m_gameObject->GetTransform()->Translate(
			m_gameObject->GetTransform()->Right() * SPEED * delta);
	}



	if(InputManager::Instance().GetKey(KeyCode::LEFT_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(
			m_gameObject->GetTransform()->Up(), -ROT_SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::RIGHT_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(
			m_gameObject->GetTransform()->Up(), ROT_SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::DOWN_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(
			m_gameObject->GetTransform()->Right(), ROT_SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::UP_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(
			m_gameObject->GetTransform()->Right(), -ROT_SPEED * delta);
	}
}
