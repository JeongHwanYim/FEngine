#include "FCameraKeyboardListener.h"
#include "FObject.h"
void FCameraKeyboardListener::OnKeyHandle(unsigned int eType, long Argument)
{
	switch (eType)
	{
	case FKEY_W:
		if (Argument == 1)
		{
			m_vTranslation.V[1] += 5.0f * m_fSensivity;
		}
		else
		{
			m_vTranslation.V[1] -= 5.0f * m_fSensivity;
		}
		break;
	case FKEY_S:
		if (Argument == 1)
		{
			m_vTranslation.V[1] -= 5.0f * m_fSensivity;
		}
		else
		{
			m_vTranslation.V[1] += 5.0f * m_fSensivity;
		}
		break;
	case FKEY_A:
		if (Argument == 1)
		{
			m_vTranslation.V[0] -= 5.0f * m_fSensivity;
		}
		else
		{
			m_vTranslation.V[0] += 5.0f * m_fSensivity;
		}
		break;
	case FKEY_D:
		if (Argument == 1)
		{
			m_vTranslation.V[0] += 5.0f * m_fSensivity;
		}
		else
		{
			m_vTranslation.V[0] -= 5.0f * m_fSensivity;
		}
		break;
	}
}

void FCameraKeyboardListener::Commit(FObject* pObj)
{
	pObj->SetTranslation(m_vTranslation);
}