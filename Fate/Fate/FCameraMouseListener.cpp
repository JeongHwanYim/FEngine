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

	pCamera->SetRotation(m_Rotator);

	FVector4 vCommitedLookVec = pCamera->GetMatrix().multiply(vLookVec);
	FVector4 vCommmitedUpVec = pCamera->GetMatrix().multiply(vUpVec);

	//√ ±‚»≠
	m_Rotator = FRotator();
}