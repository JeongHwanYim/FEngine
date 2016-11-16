#include "FCamera.h"
#include "FCameraMouseListener.h"
#include "FCameraKeyboardListener.h"
#include "FInputManager.h"

FCamera::FCamera() : FObject(nullptr)
, m_fNear(150.0f)
, m_fFar(450.0f)
, m_fFOV(90.0f)
, m_fScreenRadio(4.0f / 3.0f)
, m_vLook(4, 0.0f, 0.0f, 1.0f, 0.0f)
, m_vUp(4, 0.0f, 1.0f, 0.0f, 0.0f)
{
	FObject::m_scale = FVector(3, 1.0f, 1.0f, 1.0f);

	m_LocVecMatrix.SetTranslation(FVector(3, 0.f, 0.f, 0.f));
	m_LocVecMatrix.SetRotation(FRotator(3, 0.0f, 0.0f, 0.0f));
	
//	m_pListenerList.push_back(new FCameraMouseListener());
//	m_pListenerList.push_back(new FCameraKeyboardListener());

	for (auto pListener : m_pListenerList)
	{
		FInputManager::GetManager()->AddListener(pListener);
	}
}

FCamera::~FCamera()
{
	for (auto pListener : m_pListenerList)
	{
		FInputManager::GetManager()->AddListener(pListener);
	}
	m_pListenerList.clear();
}

FMatrix FCamera::GetViewMatrix()
{
	FMatrix mat;

	mat *= GetInverseTranslationMatrix();
	mat *= GetInverseRotationMatrix();

	return mat;
}

FMatrix FCamera::GetProjectionMatrix()
{
	FMatrix mat;

	FLOAT width = 2 * m_fScreenRadio;
	FLOAT projectionDist = 1 / tan(m_fFOV * acos(-1) / 180 / 2);
	FLOAT horizonFOV = 2 * atan(m_fScreenRadio * (1 / projectionDist));

	mat.M[0][0] = 1 / (m_fScreenRadio * tan(m_fFOV * acos(-1) / 180 / 2));
	mat.M[0][1] = 0;
	mat.M[0][2] = 0;
	mat.M[0][3] = 0;

	mat.M[1][0] = 0;
	mat.M[1][1] = 1 / tan(m_fFOV  * acos(-1) / 180 / 2);
	mat.M[1][2] = 0;
	mat.M[1][3] = 0;

	mat.M[2][0] = 0;
	mat.M[2][1] = 0;
	mat.M[2][2] = m_fFar / (m_fFar - m_fNear);
	mat.M[2][3] = 1;

	mat.M[3][0] = 0;
	mat.M[3][1] = 0;
	mat.M[3][2] = - m_fNear * m_fFar / (m_fFar - m_fNear);
	mat.M[3][3] = 0;

	return mat;
}

void FCamera::CommitListener()
{
	for (auto pListener : m_pListenerList)
	{
		pListener->Commit(this);
	}
}