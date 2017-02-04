#pragma once

#include "FCamera.h"

class FSphereCamera : public FCamera
{
public:
	FSphereCamera();

	~FSphereCamera();

	FMatrix GetInverseRotationMatrix()
	{
		FMatrix mat(GetRotation());
		return mat.GetTranspose();
	}

	FMatrix GetInverseTranslationMatrix()
	{
		FMatrix mat;

		FVector location = -GetLocation();
		mat.SetTranslation(location);

		return mat;
	}

	// View Projection Matrix 구하기, 현재는 View만...
	FMatrix GetViewMatrix();
	FMatrix GetProjectionMatrix();

	void CommitListener();

	float m_fNear;
	float m_fFar;
	float m_fFOV;
	float m_fScreenRadio;

	FVector4 m_vLook;
	FVector4 m_vUp;
private:
	std::vector<IInputListener *> m_pListenerList;
};

struct VS_CONSTANT_BUFFER
{
	FMatrix WorldViewProjection;
	float Fov;
	float Far;
	float ScreenRatio;
	float padding;
};