#include "FInputManager.h"

#include "FDirectInputContext.h"
#include "FMouseListener.h"

FInputManager::FInputManager()
{
	m_ContextList.push_back(new FDirectInputContext());

	m_ListenerList.push_back(new FMouseListener());
}

void FInputManager::Initialize(HWND hWindow)
{
	for (IInputContext* pContext : m_ContextList)
	{
		pContext->Initialize(hWindow);
	}
}

void FInputManager::Process()
{
	for (IInputContext* pContext : m_ContextList)
	{
		pContext->Process();
	}

	// Forward Event Processing
	for (IInputListener* pListener : m_ListenerList)
	{
		for (auto& pair : m_EventInstanceList)
		{
			pListener->Preprocess(pair.first, pair.second);
		}
	}

	// Deferred Event Processing
	for (IInputListener* pListener : m_ListenerList)
	{
		pListener->Postprocess();
	}

	m_EventInstanceList.clear();
}