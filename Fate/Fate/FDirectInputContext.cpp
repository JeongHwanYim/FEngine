#include "FDirectInputContext.h"
#include "FDirectInputKeyboard.h"
#include "FDirectInputMouse.h"

bool FDirectInputContext::Initialize(HWND hWindow)
{
	m_hWindow = hWindow;

	DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void **)&m_pDI,
		NULL
		);

	if (m_pDI == NULL)
	{
//		MessageBox(TEXT("DirectInput Connection Creation Failed!"));
		return false;
	}

	m_DeviceList.push_back(new FDirectInputKeyboard(this));
	m_DeviceList.push_back(new FDirectInputMouse(this));
	
	bool bInitSuccess = true;
	
	for (IInputDevice* pDevice : m_DeviceList)
	{
		bool bInit = pDevice->Initialize();
		if (bInit == false)
		{
			bInitSuccess = false;
			break;
		}
	}
	
	return bInitSuccess;
}

void FDirectInputContext::Finalize()
{

}

void FDirectInputContext::Process()
{
	for (IInputDevice* pDevice : m_DeviceList)
	{
		pDevice->InputHandle();
	}
}