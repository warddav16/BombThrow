#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

class Transform
{
public:
	Transform(void);
	~Transform(void);

	D3DXVECTOR3 GetPosition() { return m_position; }
	D3DXQUATERNION GetRotation() { return m_rotation; }

	void SetTransform(D3DXVECTOR3 vec) { m_position = D3DXVECTOR3(m_position); }
	void SetX(float x) { m_position.x = x; }
	void SetY(float y) { m_position.y = y; }
	void SetZ(float z) { m_position.z = z; }
	void Translate(D3DXVECTOR3 vec) { m_position += vec; }
	void SetRotation(D3DXQUATERNION quat) { m_rotation = quat; }
	D3DXMATRIX GetTransformMatrix();

private:
	D3DXVECTOR3 m_position;
	D3DXQUATERNION m_rotation;
};

