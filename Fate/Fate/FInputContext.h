#pragma once

#include <Windows.h>

class IInputContext
{
public:
	virtual bool Initialize(HWND hWindow) = 0;
	virtual void Finalize() = 0;
	virtual void Process() = 0;

	virtual HWND GetWindowHandle() = 0;
};