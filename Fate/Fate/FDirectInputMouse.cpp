#include "FDirectInputMouse.h"
#include "FDirectInputContext.h"

#include "FInputManager.h"

FDirectInputMouse::FDirectInputMouse(FDirectInputContext* pOwner)
: m_pOwner(pOwner)
{
	ZeroMemory(&fDIMouseState, sizeof(fDIMouseState));

	BindAll();
}

bool FDirectInputMouse::Initialize()
{
	m_pOwner->GetDInputInstance()->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL);

	if (m_pDIMouse != NULL)
	{
		m_pDIMouse->SetDataFormat(&c_dfDIMouse);
		m_pDIMouse->SetCooperativeLevel(
			m_pOwner->GetWindowHandle(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
			);
		m_pDIMouse->Acquire();
	}
	else
	{
		//		MessageBox("DirectInput Keyboard initialization Failed!");
		return false;
	}

	return true;
	// --- End of DirectInput initialize
}

void FDirectInputMouse::InputHandle()
{
	HRESULT hDeviceStateResult = m_pDIMouse->GetDeviceState(sizeof(fDIMouseState), (void *)&fDIMouseState);
	if (FAILED(hDeviceStateResult))
	{
		m_pDIMouse->Acquire();
		m_pDIMouse->GetDeviceState(sizeof(fDIMouseState), (void *)&fDIMouseState);
	}

	if (fDIMouseState.lX != 0)
	{
		FInputManager::GetManager()->RegistEvent(FInputDeviceEnum::FMOUSE_X_AXIS, fDIMouseState.lX);
		// FMOUSE_X_AXIS
	}

	if (fDIMouseState.lY != 0)
	{
		FInputManager::GetManager()->RegistEvent(FInputDeviceEnum::FMOUSE_Y_AXIS, fDIMouseState.lY);
		// FMOUSE_Y_AXIS
	}

	if (fDIMouseState.lZ != 0)
	{
		FInputManager::GetManager()->RegistEvent(FInputDeviceEnum::FMOUSE_Z_AXIS, fDIMouseState.lZ);
		// FMOUSE_Z_AXIS
	}

	unsigned int keyMapped[] =
	{
		FInputDeviceEnum::FMOUSE_LBUTTON_UP,	//0
		FInputDeviceEnum::FMOUSE_LBUTTON_DOWN,	//1
		FInputDeviceEnum::FMOUSE_RBUTTON_UP,	//2
		FInputDeviceEnum::FMOUSE_RBUTTON_DOWN,	//3
		0,										//4
		FInputDeviceEnum::FMOUSE_WHEEL_CLICK,	//5
		0,										//6
		0,										//7
	};

	for (int i = 0; 2 * i < _countof(keyMapped); ++i)
	{
		TCHAR str[256];
		if (IsKeyPressed(i) == true)
		{
			FInputManager::GetManager()->RegistEvent(keyMapped[2 * i], 0);
			swprintf_s(str, TEXT("%d번째 버튼 press\n"), i);
			OutputDebugString(str);
			// 2*i 번째 이벤트 실행
		}

		if (IsKeyReleased(i) == true)
		{
			FInputManager::GetManager()->RegistEvent(keyMapped[2 * i + 1], 0);
			swprintf_s(str, TEXT("%d번째 버튼 release\n"), i);
			OutputDebugString(str);
			// 2*i+1 번째 이벤트 실행
		}
	}
	std::memcpy(&fPrevMouseState, &fDIMouseState, sizeof(fPrevMouseState));
}

void FDirectInputMouse::BindAll()
{
	//마우스는 입력의 수가 매우 적기 때문에 바인드하지 않는다.
}
