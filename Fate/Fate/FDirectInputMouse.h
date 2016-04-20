#pragma once

#include "FInputDevice.h"
#include "FMouseEnum.h"
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
	typedef void(FDirectInputMouse::*MemberFuncPtr)();
	__forceinline void Bind(unsigned int nFTLKey, MemberFuncPtr func)
	{
		m_MouseBindMap[nFTLKey] = func;
		m_MouseList.push_back(nFTLKey);
	}

	void XAxisHandle();
	void YAxisHandle();
	void ZAxisHandle();
	
	void LButtonUpHandle();
	void LButtonDownHandle();

	void RButtonUpHandle();
	void RButtonDownHandle();

	void WheelClickHandle();
private:
	FDirectInputContext* m_pOwner;

	LPDIRECTINPUTDEVICE8 m_pDIMouse; // The mouse device

	DIMOUSESTATE fDIMouseState;

	MemberFuncPtr m_MouseBindMap[FMouseEnum::FMOUSE_ENUM_END];
	std::vector<unsigned int> m_MouseList;
};