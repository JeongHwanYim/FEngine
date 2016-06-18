#pragma once

#include "FObject.h"

class FCamera : public FObject
{
public:
	FCamera() : FObject(nullptr)
		, m_fNear(150.0f)
		, m_fFar(450.0f)
		, m_fFOV(90.0f)
		, m_fScreenRadio(4.0f/3.0f)
		, m_vLook(4, 0.0f, 0.0f, 1.0f, 0.0f)
		, m_vUp(4, 1.0f, 0.0f, 0.0f, 0.0f)
	{
		FObject::m_scale = FVector(3, 1.0f, 1.0f, 1.0f);
		FObject::m_location = FVector(3, 0.f, 0.f, 0.f);
		FObject::m_direction = FRotator(3, 0.0f, 0.0f, 0.0f);
	}

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
};