#pragma once

#include "FMath.h"

class FObject
{
public:
	FObject(FObject* pParent) : m_pParent(pParent)
	{}

	FObject* GetParent() const { return m_pParent; }
	inline FMatrix LocalToWorld() const;

	FVector GetScale() const { return m_scale; }
	FVector GetLocation() const { return m_location; }
	FRotator GetDirection() const { return m_direction; }
public:
	FObject* m_pParent;

	FVector m_scale;
	FVector m_location;
	FRotator m_direction;
};

FMatrix FObject::LocalToWorld() const
{
	FMatrix mat;

	mat.SetScale(GetScale());
	mat.SetRotation(GetDirection());
	mat.SetTranslation(GetLocation());

	FObject* pParent = GetParent();
	while (pParent != nullptr)
	{
		mat *= pParent->LocalToWorld();
	}

	return mat;
}