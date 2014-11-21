#include "Transform.h"


Transform::Transform(void)
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