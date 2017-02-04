#pragma once

#include "FInputDeviceEnum.h"
#include "FInputListener.h"
#include <vector>
#include "FMath.h"

class FObject;

class FCameraKeyboardListener : public IInputListener
{
public:
	virtual void Preprocess(unsigned int eType, long Argument);
	virtual void Postprocess();
private:
	std::vector < std::pair<unsigned int, long> > queue;
	FVector m_vTranslation;
	float m_fSensivity = 1.0f;

public:
	virtual void OnKeyHandle(unsigned int eType, long Argument);

	virtual void Commit(FObject* pObj);
};

inline void FCameraKeyboardListener::Preprocess(unsigned int eType, long Argument)
{
	if (eType > FInputDeviceEnum::FKEY_ENUM_BEGIN && eType < FInputDeviceEnum::FKEY_ENUM_END)
	{
		queue.push_back(std::make_pair(eType, Argument));
	}
}

inline void FCameraKeyboardListener::Postprocess()
{
	for (auto& pair : queue)
	{
		OnKeyHandle(pair.first, pair.second);
	}

	queue.clear();
}