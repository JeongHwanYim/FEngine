#include "FDirectInputMouse.h"
#include "FDirectInputContext.h"

FDirectInputMouse::FDirectInputMouse(FDirectInputContext* pOwner)
: m_pOwner(pOwner)
{
	ZeroMemory(m_MouseBindMap, sizeof(m_MouseBindMap));
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

}

void FDirectInputMouse::BindAll()
{
	Bind(FMouseEnum::FMOUSE_X_AXIS, &FDirectInputMouse::XAxisHandle);
	Bind(FMouseEnum::FMOUSE_Y_AXIS, &FDirectInputMouse::YAxisHandle);
	Bind(FMouseEnum::FMOUSE_Z_AXIS, &FDirectInputMouse::ZAxisHandle);

	Bind(FMouseEnum::FMOUSE_LBUTTON_UP, &FDirectInputMouse::LButtonUpHandle);
	Bind(FMouseEnum::FMOUSE_LBUTTON_DOWN, &FDirectInputMouse::LButtonDownHandle);

	Bind(FMouseEnum::FMOUSE_RBUTTON_UP, &FDirectInputMouse::RButtonUpHandle);
	Bind(FMouseEnum::FMOUSE_RBUTTON_DOWN, &FDirectInputMouse::RButtonDownHandle);
	
	Bind(FMouseEnum::FMOUSE_WHEEL_CLICK, &FDirectInputMouse::WheelClickHandle);
}

void FDirectInputMouse::XAxisHandle()
{

}

void FDirectInputMouse::YAxisHandle()
{

}

void FDirectInputMouse::ZAxisHandle()
{

}

void FDirectInputMouse::LButtonUpHandle()
{

}

void FDirectInputMouse::LButtonDownHandle()
{

}

void FDirectInputMouse::RButtonUpHandle()
{

}

void FDirectInputMouse::RButtonDownHandle()
{

}

void FDirectInputMouse::WheelClickHandle()
{

}