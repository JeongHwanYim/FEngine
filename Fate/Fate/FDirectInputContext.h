#pragma once

#include "FInputContext.h"
#include <dinput.h>
#include <vector>

class IInputDevice;

class FDirectInputContext : public IInputContext
{
public:
	virtual bool Initialize(HWND hWindow);
	virtual void Finalize();
	virtual void Process();

	virtual HWND GetWindowHandle() { return m_hWindow; }
	LPDIRECTINPUT8 GetDInputInstance() { return m_pDI; }

protected:
	__forceinline bool IsKeyDown() { return true; }
private:
	LPDIRECTINPUT8 m_pDI; // Root DirectInput Interface
	HWND m_hWindow;
	
	std::vector<IInputDevice *> m_DeviceList;
};