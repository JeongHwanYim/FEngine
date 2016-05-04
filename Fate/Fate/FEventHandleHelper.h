#pragma once

#include "FInputListener.h"
#include <functional>

class FMouseHandleHelper
{
	FMouseHandleHelper(IInputListener* pListener, unsigned int eType);
};

class FEventHandlerHelper
{
	FEventHandlerHelper(IInputListener* pListener, unsigned int eType);
};