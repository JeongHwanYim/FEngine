#pragma once

class IInputDevice
{
public:
	virtual bool Initialize() = 0;
	virtual void InputHandle() = 0;

	virtual void BindAll() = 0;
};