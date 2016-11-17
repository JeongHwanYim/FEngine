#pragma once

#include <vector>
#include "FObject.h"

class IInputListener;

class FCamera : public FObject
{
public:
	FCamera();

	~FCamera();

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
	FMatrix ViewMatrix;
	FMatrix ProjectionMatrix;
	float Fov;
	float Far;
	float ScreenRatio;
	float padding;
};