#include "Transform.h"


Transform::Transform(GameObject* gO) : ComponentBase(gO)
{
	m_position = D3DXVECTOR3(.0f, 0.f, 0.f);
	m_rotation = D3DXQUATERNION(.0f, 0.f, .0f, .0f);
}


Transform::~Transform(void)
{
}

D3DXMATRIX Transform::GetTransformMatrix()
{
	D3DXMATRIX rotationMatrix, translationMatrix;
	D3DXMatrixRotationQuaternion(&rotationMatrix, &m_rotation);
	D3DXMatrixTranslation(&translationMatrix, m_position.x, m_position.y, m_position.z);
	return translationMatrix * rotationMatrix;
}

D3DXVECTOR3 Transform::Up()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationQuaternion(&rotationMatrix, &m_rotation);
	D3DXVECTOR3 up = D3DXVECTOR3(rotationMatrix._21, rotationMatrix._22, rotationMatrix._23);
	D3DXVec3Normalize(&up, &up);
	return up;
}

D3DXVECTOR3 Transform::Forward()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationQuaternion(&rotationMatrix, &m_rotation);
	D3DXVECTOR3 forward = D3DXVECTOR3(rotationMatrix._31, rotationMatrix._32, rotationMatrix._33);
	D3DXVec3Normalize(&forward, &forward);
	return forward;
}

D3DXVECTOR3 Transform::Right()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationQuaternion(&rotationMatrix, &m_rotation);
	D3DXVECTOR3 right = D3DXVECTOR3(rotationMatrix._11, rotationMatrix._12, rotationMatrix._13);
	D3DXVec3Normalize(&right, &right);
	return right;
}

void Transform::Rotate(D3DXVECTOR3 vec, float angle)
{
	D3DXQUATERNION rot;
	D3DXQuaternionRotationAxis(&rot, &vec, angle);
	m_rotation += rot;
}