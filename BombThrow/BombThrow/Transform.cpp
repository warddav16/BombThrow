#include "Transform.h"


Transform::Transform(GameObject* gO) : ComponentBase(gO)
{
	m_position = D3DXVECTOR3(.0f, 0.f, 0.f);
	m_scale = D3DXVECTOR3(1.f, 1.f, 1.f);
	D3DXQuaternionIdentity(&m_rotation);
}


Transform::~Transform(void)
{
}

D3DXMATRIX Transform::GetTransformMatrix()
{
	D3DXMATRIX rotationMatrix, translationMatrix, scaleMatrix;
	D3DXMatrixRotationQuaternion(&rotationMatrix, &m_rotation);
	D3DXMatrixTranslation(&translationMatrix, m_position.x, m_position.y, m_position.z);
	D3DXMatrixScaling(&scaleMatrix, m_scale.x, m_scale.y, m_scale.z);
	return rotationMatrix * translationMatrix * scaleMatrix;
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
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);
	D3DXQuaternionNormalize(&m_rotation, &m_rotation);
}