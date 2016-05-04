#pragma once

#include <vector>

#include "FInputContext.h"
#include "FInputListener.h"

class FInputManager
{
public:
	FInputManager();
	static FInputManager* GetManager()
	{
		extern FInputManager* gInputManager;
		return gInputManager;
	}

	void Initialize(HWND hWindow);
	void Finalize();

	void AddListener(IInputListener* pListener) { m_ListenerList.push_back(pListener); }

	void Process();

	void RegistEvent(unsigned int eType, long Argument) {
		m_EventInstanceList.push_back(std::make_pair(eType, Argument));
	}
private:
	std::vector< IInputContext * > m_ContextList;
	std::vector< IInputListener * > m_ListenerList;

	std::vector< std::pair< unsigned int, long > > m_EventInstanceList;
};