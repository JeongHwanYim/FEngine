#include "FCamera.h"
#include "FCameraMouseListener.h"
#include "FCameraKeyboardListener.h"
#include "FInputManager.h"

#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

FCamera::FCamera() : FObject(nullptr)
, m_fNear(150.0f)
, m_fFar(450.0f)
, m_fFOV(90.0f)
, m_fScreenRatio(4.0f / 3.0f)
, m_vLook(4, 0.0f, 0.0f, 1.0f, 0.0f)
, m_vUp(4, 0.0f, 1.0f, 0.0f, 0.0f)
{
	SetTranslation(FVector(3, 0.f, 0.f, 0.f));
	SetRotation(FRotator(3, 0.0f, 0.0f, 0.0f));
	
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

FMatrix FCamera::GetViewMatrix()
{
	FMatrix mat;

#define DX_MODULE_TEST 0
#if DX_MODULE_TEST
	FVector4 vDefaultLookahead = FVector4(4, 0.0f, 0.0f, 1.0f, 0.0f);
	FVector4 vDefaultLookUp = FVector4(4, 0.0f, 1.0f, 0.0f, 0.0f);

	mat *= GetInverseRotationMatrix();

	FVector4 vLook = mat.multiply(vDefaultLookahead);
	FVector4 vUp = mat.multiply(vDefaultLookUp);

	FVector cameraPos = GetLocation();
	FVector cameraTarget = GetLocation() + FVector(3, vLook.V[0], vLook.V[1], vLook.V[2]);
	FVector4 cameraUp = vUp;


	D3DXMATRIX d3dViewMat;

	D3DXVECTOR3 EyePos = D3DXVECTOR3(cameraPos.V[0], cameraPos.V[1], cameraPos.V[2]);
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(cameraTarget.V[0], cameraTarget.V[1], cameraTarget.V[2]);
	D3DXVECTOR3 UpVec = D3DXVECTOR3(cameraUp.V[0], cameraUp.V[1], cameraUp.V[2]);

	D3DXMatrixLookAtLH(&d3dViewMat, &EyePos, &TargetPos, &UpVec);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat.M[i][j] = d3dViewMat.m[i][j];
		}
	}
#else
	FVector4 vDefaultLookahead = FVector4(4, 0.0f, 0.0f, 1.0f, 0.0f);
	FVector4 vDefaultLookUp = FVector4(4, 0.0f, 1.0f, 0.0f, 0.0f);

	mat *= GetInverseRotationMatrix();

	FVector4 vLook = mat.multiply(vDefaultLookahead);
	FVector4 vUp = mat.multiply(vDefaultLookUp);
	
	Normalize(vLook);
	
	FVector4 vRight = CrossProduct(vUp, vLook);
	Normalize(vRight);

	vUp = CrossProduct(vLook, vRight);

	FVector4 vPos = FVector4::transVector4(GetLocation());

	FVector4 vResLook(4, vLook.V[0], vLook.V[1], vLook.V[2], DotProductScalar(-vPos, vLook));
	FVector4 vResUp(4, vUp.V[0], vUp.V[1], vUp.V[2], DotProductScalar(-vPos, vUp));
	FVector4 vResRight(4, vRight.V[0], vRight.V[1], vRight.V[2], DotProductScalar(-vPos, vRight));

	mat.Set(0, vResRight);
	mat.Set(1, vResUp);
	mat.Set(2, vResLook);

	mat = mat.GetTranspose();
	/*
	void MakeMatrix(D3DXMATRIX* pmatView, D3DXVECTOR3 @vEye, D3DXVECTOR3 @vAt, D3DXVECTOR3 @vUp)
	{
	D3DXMatrixIdentity(pmatView);

	D3DXVECTOR3 vRight = D3DXVECTOR3(1.f, 0.f, 0.f);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.f, 1.f, 0.f);
	D3DXVECTOR3 vLook = D3DXVECTOR3(0.f, 0.f, 1.f);
	D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);

	vLook = @vAt - @vEye;

	vRight = D3DXVec3Cross(@vUp, vLook)

	vUp = D3DXVec3Cross(vLook, vRight)

	vPos = @vEye;




	}
	*/

//	mat *= GetInverseRotationMatrix();
//

#endif
	return mat;
}

FMatrix FCamera::GetProjectionMatrix()
{
	FMatrix mat;
	//mat.Set(3, FVector4(4, 0.3f, 0.0f, 0.0f, 1.0f));
	//mat = mat.GetTranspose();
	//return mat;
	FLOAT width = 2 * m_fScreenRatio;
	FLOAT projectionDist = 1 / tan(m_fFOV * acos(-1) / 180 / 2);
	FLOAT horizonFOV = 2 * atan(m_fScreenRatio * (1 / projectionDist));

	mat.M[0][0] = 1 / (m_fScreenRatio * tan(m_fFOV * acos(-1) / 180 / 2));
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
	mat.M[3][3] = 1;

	mat = mat.GetTranspose();
	return mat;
}

void FCamera::CommitListener()
{
	for (auto pListener : m_pListenerList)
	{
		pListener->Commit(this);
	}
}