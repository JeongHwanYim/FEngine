#pragma once

#include "FInputDevice.h"
#include "FInputDeviceEnum.h"
#include <dinput.h>
#include <vector>

class FDirectInputContext;

class FDirectInputMouse : public IInputDevice
{
public:
	FDirectInputMouse(FDirectInputContext* m_pOwner);

	virtual bool Initialize();
	virtual void InputHandle();

	virtual void BindAll();
private:
	__forceinline bool IsKeyPressed(unsigned int index)
	{
		const byte keyPressedMask = 0x80;

		byte nCurState = fDIMouseState.rgbButtons[index];
		byte nPrevState = fPrevMouseState.rgbButtons[index];

		bool bCurPressed = (nCurState & keyPressedMask) != 0;
		bool bPrevPressed = (nPrevState & keyPressedMask) != 0;

		return (bCurPressed == true) && (bPrevPressed == false);
	}
	__forceinline bool IsKeyReleased(unsigned int index)
	{
		const byte keyPressedMask = 0x80;

		byte nCurState = fDIMouseState.rgbButtons[index];
		byte nPrevState = fPrevMouseState.rgbButtons[index];

		bool bCurPressed = (nCurState & keyPressedMask) != 0;
		bool bPrevPressed = (nPrevState & keyPressedMask) != 0;

		return (bCurPressed == false) && (bPrevPressed == true);
	}

private:
	FDirectInputContext* m_pOwner;

	LPDIRECTINPUTDEVICE8 m_pDIMouse; // The mouse device

	DIMOUSESTATE fDIMouseState;
	DIMOUSESTATE fPrevMouseState;
};