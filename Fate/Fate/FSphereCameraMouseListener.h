#pragma once

#include "FMouseListener.h"
#include <cmath>
#include <xnamath.h>

class FSphereCameraMouseListener : public FMouseListener
{
public:
	FSphereCameraMouseListener()
		: m_fRadius(10.0f), m_fTheta(0.0f), m_fPI(0.0f)
		, m_fRadiusSensivity(0.5f), m_fAngleSensivity(0.5f)
	{}

public:
	virtual void XAxisHandle(long Argument)
	{
		m_fTheta += Argument * m_fAngleSensivity;
		m_fTheta = fmod(m_fTheta, 360);
	}
	virtual void YAxisHandle(long Argument)
	{
		m_fPI += Argument * m_fAngleSensivity;
		m_fPI = fmod(m_fPI, 360);
	}
	virtual void ZAxisHandle(long Argument)
	{
		m_fRadius += Argument * m_fRadiusSensivity;
		m_fRadius = m_fRadius <= 0.1f ? 0.1f : m_fRadius >= 20 ? 20 : m_fRadius;
	}

	void Convert(float& x, float &y, float& z)
	{
		x = m_fRadius * std::sinf(m_fPI) * std::cosf(m_fTheta);
		y = m_fRadius * std::sinf(m_fPI) * std::sinf(m_fPI);
		z = m_fRadius * std::cosf(m_fPI);
	}

	virtual void LButtonUpHandle(long Argument) {}
	virtual void LButtonDownHandle(long Argument) {}

	virtual void RButtonUpHandle(long Argument) {}
	virtual void RButtonDownHandle(long Argument) {}

	virtual void WheelClickHandle(long Argument) {}
private:
	float m_fRadius;
	float m_fTheta;
	float m_fPI;

	float m_fRadiusSensivity;
	float m_fAngleSensivity;
};