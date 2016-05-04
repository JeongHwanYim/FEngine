#pragma once

#include "FInputDeviceEnum.h"
#include "FInputListener.h"
#include <vector>

class FMouseListener : public IInputListener
{
public:
	virtual void Preprocess(unsigned int eType, long Argument);
	virtual void Postprocess();
private:
	std::vector < std::pair<unsigned int, long> > queue;

public:
	virtual void XAxisHandle(long Argument) {}
	virtual void YAxisHandle(long Argument) {}
	virtual void ZAxisHandle(long Argument) {}

	virtual void LButtonUpHandle(long Argument) {}
	virtual void LButtonDownHandle(long Argument) {}

	virtual void RButtonUpHandle(long Argument) {}
	virtual void RButtonDownHandle(long Argument) {}

	virtual void WheelClickHandle(long Argument) {}
};

void FMouseListener::Preprocess(unsigned int eType, long Argument)
{
	if (eType > FInputDeviceEnum::FMOUSE_ENUM_BEGIN && eType < FInputDeviceEnum::FMOUSE_ENUM_END)
	{
		queue.push_back(std::make_pair(eType, Argument));
	}
}

void FMouseListener::Postprocess()
{
	for (auto& pair : queue)
	{
		switch (pair.first)
		{
		case FInputDeviceEnum::FMOUSE_X_AXIS:
			XAxisHandle(pair.second);
			break;
		case FInputDeviceEnum::FMOUSE_Y_AXIS:
			YAxisHandle(pair.second);
			break;
		case FInputDeviceEnum::FMOUSE_Z_AXIS:
			ZAxisHandle(pair.second);
			break;
		case FInputDeviceEnum::FMOUSE_LBUTTON_UP:
			LButtonUpHandle(pair.second);
			break;
		case FInputDeviceEnum::FMOUSE_LBUTTON_DOWN:
			LButtonDownHandle(pair.second);
			break;
		case FInputDeviceEnum::FMOUSE_RBUTTON_UP:
			RButtonUpHandle(pair.second);
			break;
		case FInputDeviceEnum::FMOUSE_RBUTTON_DOWN:
			RButtonDownHandle(pair.second);
			break;
		case FInputDeviceEnum::FMOUSE_WHEEL_CLICK:
			WheelClickHandle(pair.second);
			break;
		}
	}

	queue.clear();
}