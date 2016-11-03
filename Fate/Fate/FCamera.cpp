#include "FCamera.h"
#include "FSphereCameraMouseListener.h"
#include "FInputManager.h"

FCamera::FCamera() : FObject(nullptr)
, m_fNear(150.0f)
, m_fFar(450.0f)
, m_fFOV(90.0f)
, m_fScreenRadio(4.0f / 3.0f)
, m_vLook(4, 0.0f, 0.0f, 1.0f, 0.0f)
, m_vUp(4, 1.0f, 0.0f, 0.0f, 0.0f)
{
	FObject::m_scale = FVector(3, 1.0f, 1.0f, 1.0f);
	FObject::m_location = FVector(3, 0.f, 0.f, 0.f);
	FObject::m_direction = FRotator(3, 0.0f, 0.0f, 0.0f);

	m_pSphereMouseListener = new FSphereCameraMouseListener();
	FInputManager::GetManager()->AddListener(m_pSphereMouseListener);
}

FCamera::~FCamera()
{
	FInputManager::GetManager()->RemoveListener(m_pSphereMouseListener);
}