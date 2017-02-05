#pragma once

#include <vector>
#include "FObject.h"

class IInputListener;

class FCamera : public FObject
{
public:
	FCamera();

	~FCamera();

	// View Projection Matrix ���ϱ�, ����� View��...
	virtual FMatrix GetViewMatrix();
	FMatrix GetProjectionMatrix();
	
	void CommitListener();

	float m_fNear;
	float m_fFar;
	float m_fFOV;
	float m_fScreenRatio;

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