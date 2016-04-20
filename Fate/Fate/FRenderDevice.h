#pragma once

#include <Windows.h>

class IRenderDevice
{
public:
	virtual bool Initialize(HWND hWindow) = 0;
	virtual void RenderFrame() = 0;
	virtual void Finalize() = 0;
};