#pragma once

class IInputListener
{
public:
	virtual void Preprocess(unsigned int eType, long Argument) = 0;
	virtual void Postprocess() = 0;
};