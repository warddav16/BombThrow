#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

#include "ComponentBase.h"

class Transform : ComponentBase
{
public:
	Transform(GameObject* gO);
	~Transform(void);

	D3DXVECTOR3 GetPosition() { return m_position; }
	D3DXQUATERNION GetRotation() { return m_rotation; }

	void SetPosition(D3DXVECTOR3 vec) { m_position = D3DXVECTOR3(vec); }
	void SetScale(D3DXVECTOR3 scale) { m_scale = D3DXVECTOR3(scale); }

	void SetX(float x) { m_position.x = x; }
	void SetY(float y) { m_position.y = y; }
	void SetZ(float z) { m_position.z = z; }
	void Translate(D3DXVECTOR3 vec) { m_position += vec; }
	void Rotate(D3DXVECTOR3 vec, float angle);
	void SetRotation(D3DXQUATERNION quat) { m_rotation = quat; }
	D3DXMATRIX GetTransformMatrix();
	D3DXVECTOR3 Up();
	D3DXVECTOR3 Forward();
	D3DXVECTOR3 Right();

private:
	Transform() {}
	D3DXVECTOR3 m_position;
	D3DXQUATERNION m_rotation;
	D3DXVECTOR3 m_scale;
};

