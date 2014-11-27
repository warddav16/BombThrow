#include "FreeFormController.h"

#include "GameObject.h"
#include "InputManager.h"
#include "Transform.h"

const float SPEED = 5.f;
const float ROT_SPEED = .01f;

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
		m_gameObject->GetTransform()->Translate(D3DXVECTOR3(0,0,1) * SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::S))
	{
		m_gameObject->GetTransform()->Translate(D3DXVECTOR3(0,0,-1) * SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::A))
	{
		m_gameObject->GetTransform()->Translate(D3DXVECTOR3(-1,0,0) * SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::D))
	{
		m_gameObject->GetTransform()->Translate(D3DXVECTOR3(1,0,0) * SPEED * delta);
	}



	if(InputManager::Instance().GetKey(KeyCode::LEFT_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(D3DXVECTOR3(0,1,0), -ROT_SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::RIGHT_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(D3DXVECTOR3(0,1,0), ROT_SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::DOWN_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(D3DXVECTOR3(1,0,0), ROT_SPEED * delta);
	}

	if(InputManager::Instance().GetKey(KeyCode::UP_ARROW))
	{
		m_gameObject->GetTransform()->Rotate(D3DXVECTOR3(1,0,0), -ROT_SPEED * delta);
	}
}
