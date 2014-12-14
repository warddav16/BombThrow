#include "Camera.h"

#include "GameObject.h"
#include "Transform.h"

Camera::Camera(GameObject* gO) : ComponentBase(gO)
{
	gO->SetCamera(this);
}


Camera::~Camera(void)
{
}

D3DXMATRIX Camera::GetViewMatrix()
{
	D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up = m_gameObject->GetTransform()->Up();

	// Setup the position of the camera in the world.
	position = m_gameObject->GetTransform()->GetPosition();;

	// Setup where the camera is looking by default.
	lookAt = m_gameObject->GetTransform()->Forward();

	D3DXMatrixRotationQuaternion(&rotationMatrix, &(m_gameObject->GetTransform()->GetRotation()));
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);

	return viewMatrix;
}