#include "FDirectInputKeyboard.h"
#include "FDirectInputContext.h"
#include <memory>
#include "FInputManager.h"

FDirectInputKeyboard::FDirectInputKeyboard(FDirectInputContext* pOwner)
: m_pOwner(pOwner)
{
	ZeroMemory(m_KeyBindMap, sizeof(m_KeyBindMap));
	ZeroMemory(fPrevKeyboardState, sizeof(fPrevKeyboardState));

	BindAll();
}

bool FDirectInputKeyboard::Initialize()
{
	HRESULT hCreateDeviceResult = m_pOwner->GetDInputInstance()->CreateDevice(GUID_SysKeyboard, &m_pDIKeyboard, NULL);

	if (m_pDIKeyboard != NULL)
	{
		HRESULT hSetDataFormatResult = m_pDIKeyboard->SetDataFormat(&c_dfDIKeyboard);
		HRESULT hSetCooperativeLevelResult = m_pDIKeyboard->SetCooperativeLevel(
			m_pOwner->GetWindowHandle(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
			);
		HRESULT result = m_pDIKeyboard->Acquire();

		if (FAILED(result))
		{
			OutputDebugString(TEXT("¹º°¡ ÀÌ»óÇØ"));
		}
	}
	else
	{
//		MessageBox("DirectInput Keyboard initialization Failed!");
		return false;
	}

	return true;
	// --- End of DirectInput initialize
}

void FDirectInputKeyboard::InputHandle()
{
	HRESULT hDeviceStateResult = m_pDIKeyboard->GetDeviceState(sizeof(fDIKeyboardState), (void *)&fDIKeyboardState);

	if (FAILED(hDeviceStateResult))
	{
		m_pDIKeyboard->Acquire();
		m_pDIKeyboard->GetDeviceState(sizeof(fDIKeyboardState), (void *)&fDIKeyboardState);
	}

	for (unsigned int nFTLKey : m_KeyList)
	{
		if (IsKeyPressed(nFTLKey) == true)
		{
			FInputManager::GetManager()->RegistEvent(nFTLKey, 1);
			// Event Handle
		}
		if (IsKeyReleased(nFTLKey) == true)
		{
			FInputManager::GetManager()->RegistEvent(nFTLKey, 0);
			// Event Handle
		}
	}

	std::memcpy(fPrevKeyboardState, fDIKeyboardState, sizeof(fPrevKeyboardState));
}

void FDirectInputKeyboard::BindAll()
{
	Bind(FInputDeviceEnum::FKEY_0, DIK_0);
	Bind(FInputDeviceEnum::FKEY_1, DIK_1);
	Bind(FInputDeviceEnum::FKEY_2, DIK_2);
	Bind(FInputDeviceEnum::FKEY_3, DIK_3);
	Bind(FInputDeviceEnum::FKEY_4, DIK_4);
	Bind(FInputDeviceEnum::FKEY_5, DIK_5);
	Bind(FInputDeviceEnum::FKEY_6, DIK_6);
	Bind(FInputDeviceEnum::FKEY_7, DIK_7);
	Bind(FInputDeviceEnum::FKEY_8, DIK_8);
	Bind(FInputDeviceEnum::FKEY_9, DIK_9);

	Bind(FInputDeviceEnum::FKEY_NUMPAD_0, DIK_NUMPAD0);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_1, DIK_NUMPAD1);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_2, DIK_NUMPAD2);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_3, DIK_NUMPAD3);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_4, DIK_NUMPAD4);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_5, DIK_NUMPAD5);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_6, DIK_NUMPAD6);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_7, DIK_NUMPAD7);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_8, DIK_NUMPAD8);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_9, DIK_NUMPAD9);

	Bind(FInputDeviceEnum::FKEY_A, DIK_A);
	Bind(FInputDeviceEnum::FKEY_B, DIK_B);
	Bind(FInputDeviceEnum::FKEY_C, DIK_C);
	Bind(FInputDeviceEnum::FKEY_D, DIK_D);
	Bind(FInputDeviceEnum::FKEY_E, DIK_E);
	Bind(FInputDeviceEnum::FKEY_F, DIK_F);
	Bind(FInputDeviceEnum::FKEY_G, DIK_G);
	Bind(FInputDeviceEnum::FKEY_H, DIK_H);
	Bind(FInputDeviceEnum::FKEY_I, DIK_I);
	Bind(FInputDeviceEnum::FKEY_J, DIK_J);
	Bind(FInputDeviceEnum::FKEY_K, DIK_K);
	Bind(FInputDeviceEnum::FKEY_L, DIK_L);
	Bind(FInputDeviceEnum::FKEY_M, DIK_M);
	Bind(FInputDeviceEnum::FKEY_N, DIK_N);
	Bind(FInputDeviceEnum::FKEY_O, DIK_O);
	Bind(FInputDeviceEnum::FKEY_P, DIK_P);
	Bind(FInputDeviceEnum::FKEY_Q, DIK_Q);
	Bind(FInputDeviceEnum::FKEY_R, DIK_R);
	Bind(FInputDeviceEnum::FKEY_S, DIK_S);
	Bind(FInputDeviceEnum::FKEY_T, DIK_T);
	Bind(FInputDeviceEnum::FKEY_U, DIK_U);
	Bind(FInputDeviceEnum::FKEY_V, DIK_V);
	Bind(FInputDeviceEnum::FKEY_W, DIK_W);
	Bind(FInputDeviceEnum::FKEY_X, DIK_X);
	Bind(FInputDeviceEnum::FKEY_Y, DIK_Y);
	Bind(FInputDeviceEnum::FKEY_Z, DIK_Z);

	Bind(FInputDeviceEnum::FKEY_ESCAPE, DIK_ESCAPE);
	Bind(FInputDeviceEnum::FKEY_F1, DIK_F1);
	Bind(FInputDeviceEnum::FKEY_F2, DIK_F2);
	Bind(FInputDeviceEnum::FKEY_F3, DIK_F3);
	Bind(FInputDeviceEnum::FKEY_F4, DIK_F4);
	Bind(FInputDeviceEnum::FKEY_F5, DIK_F5);
	Bind(FInputDeviceEnum::FKEY_F6, DIK_F6);
	Bind(FInputDeviceEnum::FKEY_F7, DIK_F7);
	Bind(FInputDeviceEnum::FKEY_F8, DIK_F8);
	Bind(FInputDeviceEnum::FKEY_F9, DIK_F9);
	Bind(FInputDeviceEnum::FKEY_F10, DIK_F10);
	Bind(FInputDeviceEnum::FKEY_F11, DIK_F11);
	Bind(FInputDeviceEnum::FKEY_F12, DIK_F12);
	Bind(FInputDeviceEnum::FKEY_PRINTSCREEN, DIK_SYSRQ);
	Bind(FInputDeviceEnum::FKEY_SCROLLLOCK, DIK_SCROLL);
	Bind(FInputDeviceEnum::FKEY_PAUSEBREAK, DIK_PAUSE);

	Bind(FInputDeviceEnum::FKEY_TAB, DIK_TAB);
	Bind(FInputDeviceEnum::FKEY_CAPSLOCK, DIK_CAPITAL);
	Bind(FInputDeviceEnum::FKEY_LEFT_SHIFT, DIK_LSHIFT);
	Bind(FInputDeviceEnum::FKEY_LEFT_CTRL, DIK_LCONTROL);
	Bind(FInputDeviceEnum::FKEY_LEFT_ALT, DIK_LALT);
	Bind(FInputDeviceEnum::FKEY_RIGHT_SHIFT, DIK_RSHIFT);
	Bind(FInputDeviceEnum::FKEY_RIGHT_CTRL, DIK_RCONTROL);
	Bind(FInputDeviceEnum::FKEY_RIGHT_ALT, DIK_RALT);
	Bind(FInputDeviceEnum::FKEY_SPACE, DIK_SPACE);
	Bind(FInputDeviceEnum::FKEY_BACKSPACE, DIK_BACK);
	Bind(FInputDeviceEnum::FKEY_ENTER, DIK_RETURN);

	Bind(FInputDeviceEnum::FKEY_INSERT, DIK_INSERT);
	Bind(FInputDeviceEnum::FKEY_DELETE, DIK_DELETE);
	Bind(FInputDeviceEnum::FKEY_HOME, DIK_HOME);
	Bind(FInputDeviceEnum::FKEY_END, DIK_END);
	Bind(FInputDeviceEnum::FKEY_PAGEUP, DIK_PGUP);
	Bind(FInputDeviceEnum::FKEY_PAGEDOWN, DIK_PGDN);

	Bind(FInputDeviceEnum::FKEY_ARROW_UP, DIK_UP);
	Bind(FInputDeviceEnum::FKEY_ARROW_DOWN, DIK_DOWN);
	Bind(FInputDeviceEnum::FKEY_ARROW_LEFT, DIK_LEFT);
	Bind(FInputDeviceEnum::FKEY_ARROW_RIGHT, DIK_RIGHT);

	Bind(FInputDeviceEnum::FKEY_NUMPAD_0, DIK_NUMPAD0);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_1, DIK_NUMPAD1);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_2, DIK_NUMPAD2);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_3, DIK_NUMPAD3);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_4, DIK_NUMPAD4);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_5, DIK_NUMPAD5);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_6, DIK_NUMPAD6);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_7, DIK_NUMPAD7);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_8, DIK_NUMPAD8);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_9, DIK_NUMPAD9);

	Bind(FInputDeviceEnum::FKEY_NUMPAD_SLASH, DIK_NUMPADSLASH);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_STAR, DIK_NUMPADSTAR);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_MINUS, DIK_NUMPADMINUS);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_PLUS, DIK_NUMPADPLUS);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_DOT, DIK_NUMPADPERIOD);

	Bind(FInputDeviceEnum::FKEY_NUMLOCK, DIK_NUMLOCK);
	Bind(FInputDeviceEnum::FKEY_NUMPAD_ENTER, DIK_NUMPADENTER);
}