#pragma once

#include "FMouseListener.h"
#include "Windows.h"
#include <cmath>
#include "FMath.h"

class FCameraMouseListener : public FMouseListener
{
public:
	FCameraMouseListener()
		:  m_fRotateSensivity(0.5f)
	{}

public:
	virtual void XAxisHandle(long Argument)
	{
		m_Rotator.V[0] -= Argument * m_fRotateSensivity;
	}
	virtual void YAxisHandle(long Argument)
	{
		m_Rotator.V[1] -= Argument * m_fRotateSensivity;
	}

	virtual void LButtonUpHandle(long Argument) {}
	virtual void LButtonDownHandle(long Argument) {}

	virtual void RButtonUpHandle(long Argument) {}
	virtual void RButtonDownHandle(long Argument) {}

	virtual void WheelClickHandle(long Argument) {}

	virtual void Postprocess();

	virtual void Commit(FObject* pObj);
private:
	FRotator m_Rotator;

	float m_fRotateSensivity;
};