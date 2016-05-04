#pragma once

#include "FInputDevice.h"
#include "FInputDeviceEnum.h"
#include <dinput.h>
#include <vector>

class FDirectInputContext;

class FDirectInputKeyboard : public IInputDevice
{
public:
	FDirectInputKeyboard(FDirectInputContext* m_pOwner);

	virtual bool Initialize();
	virtual void InputHandle();

	virtual void BindAll();
private:
	__forceinline void Bind(unsigned int nFTLKey, unsigned int nOtherKey)
	{
		m_KeyBindMap[nFTLKey] = nOtherKey;
		m_KeyList.push_back(nFTLKey);
	}
	__forceinline unsigned int GetOtherKey(unsigned int nFTLKey) { return m_KeyBindMap[nFTLKey]; }
	__forceinline bool IsKeyPressed(unsigned int nFTLKey)
	{
		const byte keyPressedMask = 0x80;

		unsigned int nOtherKey = GetOtherKey(nFTLKey);
		byte nCurState = fDIKeyboardState[nOtherKey];
		byte nPrevState = fPrevKeyboardState[nOtherKey];

		bool bCurPressed = (nCurState & keyPressedMask) != 0;
		bool bPrevPressed = (nPrevState & keyPressedMask) != 0;

		return (bCurPressed == true) && (bPrevPressed == false);
	}
	__forceinline bool IsKeyReleased(unsigned int nFTLKey)
	{
		const byte keyPressedMask = 0x80;

		unsigned int nOtherKey = GetOtherKey(nFTLKey);
		byte nCurState = fDIKeyboardState[nOtherKey];
		byte nPrevState = fPrevKeyboardState[nOtherKey];

		bool bCurPressed = (nCurState & keyPressedMask) != 0;
		bool bPrevPressed = (nPrevState & keyPressedMask) != 0;

		return (bCurPressed == false) && (bPrevPressed == true);
	}
private:
	FDirectInputContext* m_pOwner;

	LPDIRECTINPUTDEVICE8 m_pDIKeyboard; // The keyboard device

	unsigned int m_KeyBindMap[FInputDeviceEnum::FKEY_ENUM_END];
	std::vector< unsigned int > m_KeyList;
	byte fPrevKeyboardState[256];
	byte fDIKeyboardState[256];
};