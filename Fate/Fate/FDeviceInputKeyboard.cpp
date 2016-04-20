#include "FDirectInputKeyboard.h"
#include "FDirectInputContext.h"

FDirectInputKeyboard::FDirectInputKeyboard(FDirectInputContext* pOwner)
: m_pOwner(pOwner)
{
	ZeroMemory(m_KeyBindMap, sizeof(m_KeyBindMap));

	BindAll();
}

bool FDirectInputKeyboard::Initialize()
{
	m_pOwner->GetDInputInstance()->CreateDevice(GUID_SysKeyboard, &m_pDIKeyboard, NULL);

	if (m_pDIKeyboard != NULL)
	{
		m_pDIKeyboard->SetDataFormat(&c_dfDIKeyboard);
		m_pDIKeyboard->SetCooperativeLevel(
			m_pOwner->GetWindowHandle(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
			);
		m_pDIKeyboard->Acquire();
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
	for (unsigned int nFTLKey : m_KeyList)
	{
		if (IsKeyPressed(nFTLKey) == true)
		{
			// Event Handle
		}
	}
}

void FDirectInputKeyboard::BindAll()
{
	Bind(FKeyboardEnum::FKEY_0, DIK_0);
	Bind(FKeyboardEnum::FKEY_1, DIK_1);
	Bind(FKeyboardEnum::FKEY_2, DIK_2);
	Bind(FKeyboardEnum::FKEY_3, DIK_3);
	Bind(FKeyboardEnum::FKEY_4, DIK_4);
	Bind(FKeyboardEnum::FKEY_5, DIK_5);
	Bind(FKeyboardEnum::FKEY_6, DIK_6);
	Bind(FKeyboardEnum::FKEY_7, DIK_7);
	Bind(FKeyboardEnum::FKEY_8, DIK_8);
	Bind(FKeyboardEnum::FKEY_9, DIK_9);

	Bind(FKeyboardEnum::FKEY_NUMPAD_0, DIK_NUMPAD0);
	Bind(FKeyboardEnum::FKEY_NUMPAD_1, DIK_NUMPAD1);
	Bind(FKeyboardEnum::FKEY_NUMPAD_2, DIK_NUMPAD2);
	Bind(FKeyboardEnum::FKEY_NUMPAD_3, DIK_NUMPAD3);
	Bind(FKeyboardEnum::FKEY_NUMPAD_4, DIK_NUMPAD4);
	Bind(FKeyboardEnum::FKEY_NUMPAD_5, DIK_NUMPAD5);
	Bind(FKeyboardEnum::FKEY_NUMPAD_6, DIK_NUMPAD6);
	Bind(FKeyboardEnum::FKEY_NUMPAD_7, DIK_NUMPAD7);
	Bind(FKeyboardEnum::FKEY_NUMPAD_8, DIK_NUMPAD8);
	Bind(FKeyboardEnum::FKEY_NUMPAD_9, DIK_NUMPAD9);

	Bind(FKeyboardEnum::FKEY_A, DIK_A);
	Bind(FKeyboardEnum::FKEY_B, DIK_B);
	Bind(FKeyboardEnum::FKEY_C, DIK_C);
	Bind(FKeyboardEnum::FKEY_D, DIK_D);
	Bind(FKeyboardEnum::FKEY_E, DIK_E);
	Bind(FKeyboardEnum::FKEY_F, DIK_F);
	Bind(FKeyboardEnum::FKEY_G, DIK_G);
	Bind(FKeyboardEnum::FKEY_H, DIK_H);
	Bind(FKeyboardEnum::FKEY_I, DIK_I);
	Bind(FKeyboardEnum::FKEY_J, DIK_J);
	Bind(FKeyboardEnum::FKEY_K, DIK_K);
	Bind(FKeyboardEnum::FKEY_L, DIK_L);
	Bind(FKeyboardEnum::FKEY_M, DIK_M);
	Bind(FKeyboardEnum::FKEY_N, DIK_N);
	Bind(FKeyboardEnum::FKEY_O, DIK_O);
	Bind(FKeyboardEnum::FKEY_P, DIK_P);
	Bind(FKeyboardEnum::FKEY_Q, DIK_Q);
	Bind(FKeyboardEnum::FKEY_R, DIK_R);
	Bind(FKeyboardEnum::FKEY_S, DIK_S);
	Bind(FKeyboardEnum::FKEY_T, DIK_T);
	Bind(FKeyboardEnum::FKEY_U, DIK_U);
	Bind(FKeyboardEnum::FKEY_V, DIK_V);
	Bind(FKeyboardEnum::FKEY_W, DIK_W);
	Bind(FKeyboardEnum::FKEY_X, DIK_X);
	Bind(FKeyboardEnum::FKEY_Y, DIK_Y);
	Bind(FKeyboardEnum::FKEY_Z, DIK_Z);

	Bind(FKeyboardEnum::FKEY_ESCAPE, DIK_ESCAPE);
	Bind(FKeyboardEnum::FKEY_F1, DIK_F1);
	Bind(FKeyboardEnum::FKEY_F2, DIK_F2);
	Bind(FKeyboardEnum::FKEY_F3, DIK_F3);
	Bind(FKeyboardEnum::FKEY_F4, DIK_F4);
	Bind(FKeyboardEnum::FKEY_F5, DIK_F5);
	Bind(FKeyboardEnum::FKEY_F6, DIK_F6);
	Bind(FKeyboardEnum::FKEY_F7, DIK_F7);
	Bind(FKeyboardEnum::FKEY_F8, DIK_F8);
	Bind(FKeyboardEnum::FKEY_F9, DIK_F9);
	Bind(FKeyboardEnum::FKEY_F10, DIK_F10);
	Bind(FKeyboardEnum::FKEY_F11, DIK_F11);
	Bind(FKeyboardEnum::FKEY_F12, DIK_F12);
	Bind(FKeyboardEnum::FKEY_PRINTSCREEN, DIK_SYSRQ);
	Bind(FKeyboardEnum::FKEY_SCROLLLOCK, DIK_SCROLL);
	Bind(FKeyboardEnum::FKEY_PAUSEBREAK, DIK_PAUSE);

	Bind(FKeyboardEnum::FKEY_TAB, DIK_TAB);
	Bind(FKeyboardEnum::FKEY_CAPSLOCK, DIK_CAPITAL);
	Bind(FKeyboardEnum::FKEY_LEFT_SHIFT, DIK_LSHIFT);
	Bind(FKeyboardEnum::FKEY_LEFT_CTRL, DIK_LCONTROL);
	Bind(FKeyboardEnum::FKEY_LEFT_ALT, DIK_LALT);
	Bind(FKeyboardEnum::FKEY_RIGHT_SHIFT, DIK_RSHIFT);
	Bind(FKeyboardEnum::FKEY_RIGHT_CTRL, DIK_RCONTROL);
	Bind(FKeyboardEnum::FKEY_RIGHT_ALT, DIK_RALT);
	Bind(FKeyboardEnum::FKEY_SPACE, DIK_SPACE);
	Bind(FKeyboardEnum::FKEY_BACKSPACE, DIK_BACK);
	Bind(FKeyboardEnum::FKEY_ENTER, DIK_RETURN);

	Bind(FKeyboardEnum::FKEY_INSERT, DIK_INSERT);
	Bind(FKeyboardEnum::FKEY_DELETE, DIK_DELETE);
	Bind(FKeyboardEnum::FKEY_HOME, DIK_HOME);
	Bind(FKeyboardEnum::FKEY_END, DIK_END);
	Bind(FKeyboardEnum::FKEY_PAGEUP, DIK_PGUP);
	Bind(FKeyboardEnum::FKEY_PAGEDOWN, DIK_PGDN);

	Bind(FKeyboardEnum::FKEY_ARROW_UP, DIK_UP);
	Bind(FKeyboardEnum::FKEY_ARROW_DOWN, DIK_DOWN);
	Bind(FKeyboardEnum::FKEY_ARROW_LEFT, DIK_LEFT);
	Bind(FKeyboardEnum::FKEY_ARROW_RIGHT, DIK_RIGHT);

	Bind(FKeyboardEnum::FKEY_NUMPAD_0, DIK_NUMPAD0);
	Bind(FKeyboardEnum::FKEY_NUMPAD_1, DIK_NUMPAD1);
	Bind(FKeyboardEnum::FKEY_NUMPAD_2, DIK_NUMPAD2);
	Bind(FKeyboardEnum::FKEY_NUMPAD_3, DIK_NUMPAD3);
	Bind(FKeyboardEnum::FKEY_NUMPAD_4, DIK_NUMPAD4);
	Bind(FKeyboardEnum::FKEY_NUMPAD_5, DIK_NUMPAD5);
	Bind(FKeyboardEnum::FKEY_NUMPAD_6, DIK_NUMPAD6);
	Bind(FKeyboardEnum::FKEY_NUMPAD_7, DIK_NUMPAD7);
	Bind(FKeyboardEnum::FKEY_NUMPAD_8, DIK_NUMPAD8);
	Bind(FKeyboardEnum::FKEY_NUMPAD_9, DIK_NUMPAD9);

	Bind(FKeyboardEnum::FKEY_NUMPAD_SLASH, DIK_NUMPADSLASH);
	Bind(FKeyboardEnum::FKEY_NUMPAD_STAR, DIK_NUMPADSTAR);
	Bind(FKeyboardEnum::FKEY_NUMPAD_MINUS, DIK_NUMPADMINUS);
	Bind(FKeyboardEnum::FKEY_NUMPAD_PLUS, DIK_NUMPADPLUS);
	Bind(FKeyboardEnum::FKEY_NUMPAD_DOT, DIK_NUMPADPERIOD);

	Bind(FKeyboardEnum::FKEY_NUMLOCK, DIK_NUMLOCK);
	Bind(FKeyboardEnum::FKEY_NUMPAD_ENTER, DIK_NUMPADENTER);
}