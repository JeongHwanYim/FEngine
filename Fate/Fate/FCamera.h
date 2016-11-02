#pragma once

#include "FObject.h"

class FMouseListener;

class FCamera : public FObject
{
public:
	FCamera();

	~FCamera();

	FMatrix GetInverseRotationMatrix()
	{
		FMatrix mat;

		FRotator direction = -GetDirection();
		mat.SetRotation(direction);

		return mat;
	}

	FMatrix GetInverseTranslationMatrix()
	{
		FMatrix mat;

		FVector location = -GetLocation();
		mat.SetTranslation(location);

		return mat;
	}

	FMatrix GetProjectionMatrix()
	{
		FMatrix mat;

		mat *= GetInverseTranslationMatrix();
		mat *= GetInverseRotationMatrix();
		
		return mat;
	}

	float m_fNear;
	float m_fFar;
	float m_fFOV;
	float m_fScreenRadio;

	FVector4 m_vLook;
	FVector4 m_vUp;
private:
	FMouseListener* m_pSphereMouseListener;
};

struct VS_CONSTANT_BUFFER
{
	FMatrix WorldViewProjection;
	float Fov;
	float Far;
	float padding[2];
};