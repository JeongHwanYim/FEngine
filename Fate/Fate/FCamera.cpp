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
	
	m_pListenerList.push_back(new FCameraMouseListener());
	m_pListenerList.push_back(new FCameraKeyboardListener());

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

FMatrix FCamera::GetProjectionMatrix()
{
	FMatrix mat;

	mat *= GetInverseTranslationMatrix();
	mat *= GetInverseRotationMatrix();

	return mat;
}

void FCamera::CommitListener()
{
	for (auto pListener : m_pListenerList)
	{
		pListener->Commit(this);
	}
}


FVector4 FCamera::GetLookVector()
{
	FMatrix mat = GetInverseRotationMatrix();
	FVector4 vec = m_vLook;

	FVector4 res;
	for (int i = 0; i < mat.NUM_ELEMENT; ++i)
	{
		for (int j = 0; j < vec.NUM_ELEMENT; ++j)
		{
			res.V[i] += vec.V[j] * mat.M[j][i];
		}
	}

	return vec;
}

FVector4 FCamera::GetUpVector()
{
	FMatrix mat = GetInverseRotationMatrix();
	FVector4 vec = m_vUp;

	FVector4 res;
	for (int i = 0; i < mat.NUM_ELEMENT; ++i)
	{
		for (int j = 0; j < vec.NUM_ELEMENT; ++j)
		{
			res.V[i] += vec.V[j] * mat.M[j][i];
		}
	}

	return vec;
}