#pragma once

#include "FMath.h"

class FObject
{
public:
	FObject(FObject* pParent) : m_pParent(pParent)
	{}

	FObject* GetParent() const { return m_pParent; }
	inline FMatrix LocalToWorld() const;

	inline FVector GetLocation() const
	{
		FVector vec(3, m_LocVecMatrix.M[3][0], m_LocVecMatrix.M[3][1], m_LocVecMatrix.M[3][2]);
		return vec;
	}
	inline FMatrix GetRotation() const
	{
		FMatrix mat(m_LocVecMatrix);
		mat.M[3][0] = 0.0f;
		mat.M[3][1] = 0.0f;
		mat.M[3][2] = 0.0f;

		return mat;
	}

	inline void SetRotation(const FRotator& Rotator) { m_LocVecMatrix.SetRotation(Rotator); }

	inline void SetTranslation(FVector trans) { m_LocVecMatrix.Set(3, FVector4::transVector4(-trans)); }
	inline FMatrix GetMatrix() const{ return m_LocVecMatrix; }

	inline FMatrix GetInverseRotationMatrix()
	{
		FMatrix mat(GetRotation());
		return mat.GetTranspose();
	}

	inline FMatrix GetInverseTranslationMatrix()
	{
		FMatrix mat;

		FVector location = -GetLocation();
		mat.Set(3, -location);

		return mat;
	}

private:
	FObject* m_pParent;

	FMatrix m_LocVecMatrix;
};

FMatrix FObject::LocalToWorld() const
{
	FMatrix mat;

//	mat.SetScale(GetScale());
	mat *= GetMatrix(); 

	FObject* pParent = GetParent();
	while (pParent != nullptr)
	{
		mat *= pParent->LocalToWorld();
	}

	return mat;
}