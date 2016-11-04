#include "FCameraMouseListener.h"
#include "FCamera.h"

void FCameraMouseListener::Postprocess()
{
	FMouseListener::Postprocess();


}

void FCameraMouseListener::Commit(FObject* pObj)
{
	FCamera *pCamera = (FCamera *)pObj;

	FVector4 vLookVec = pCamera->m_vLook;
	FVector4 vUpVec = pCamera->m_vUp;

	pCamera->m_LocVecMatrix.SetRotation(m_Rotator);

	FVector4 vCommitedLookVec = pCamera->m_LocVecMatrix.multiply(vLookVec);
	FVector4 vCommmitedUpVec = pCamera->m_LocVecMatrix.multiply(vUpVec);

	m_Rotator = FRotator();

}