#include "FSphereCameraMouseListener.h"
#include "FCamera.h"

void FSphereCameraMouseListener::Postprocess()
{
	FMouseListener::Postprocess();


}

void FSphereCameraMouseListener::Commit(FObject* pObj)
{
	FCamera *pCamera = (FCamera *)pObj;
	
	FVector4 vLookVec = pCamera->m_vLook;
	FVector4 vUpVec = pCamera->m_vUp;

	Convert(vLookVec.V[0], vLookVec.V[1], vLookVec.V[2]);
	Normalize(vLookVec);

	FVector4 vRightVec = CrossProduct(vUpVec, vLookVec);
	Normalize(vRightVec);

	vUpVec = CrossProduct(vRightVec, vLookVec);
	Normalize(vUpVec);

	FMatrix mat;
	
	mat.M[0][0] = vUpVec.V[0];
	mat.M[0][1] = vUpVec.V[1];
	mat.M[0][2] = vUpVec.V[2];
	mat.M[0][3] = vUpVec.V[3];

	mat.M[1][0] = vRightVec.V[0];
	mat.M[1][1] = vRightVec.V[1];
	mat.M[1][2] = vRightVec.V[2];
	mat.M[1][3] = vRightVec.V[3];

	mat.M[2][0] = vLookVec.V[0];
	mat.M[2][1] = vLookVec.V[1];
	mat.M[2][2] = vLookVec.V[2];
	mat.M[2][3] = vLookVec.V[3];
	
	pCamera->m_LocVecMatrix *= mat;
	pCamera->m_vLook = vLookVec;
	pCamera->m_vUp = vUpVec;

	m_fTheta = 0.0f;
	m_fPI = 0.0f;
}