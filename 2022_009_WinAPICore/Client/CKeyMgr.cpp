#include "pch.h"
#include "CKeyMgr.h"

#include "Core.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,	// LEFT,
	VK_RIGHT,	// RIGHT,
	VK_UP,		// UP,
	VK_DOWN,	// DOWN,
	'Q',		// Q, 
	'W',		// W, 
	'E',		// E, 
	'R',		// R, 
	'T',		// T, 
	'Y',		// Y, 
	'U',		// U, 
	'I',		// I, 
	'O',		// O, 
	'P',		// P,
	'A',		// A, 
	'S',		// S, 
	'D',		// D, 
	'F',		// F, 
	'G',		// G,
	'Z',		// Z, 
	'X',		// X, 
	'C',		// C, 
	'V',		// V, 
	'B',		// B,
	VK_MENU,	// ALT,
	VK_CONTROL,	// CTRL,
	VK_SHIFT,	// LSHIFT,
	VK_SPACE,	// SPACE,
	VK_RETURN,	// ENTER,
	VK_ESCAPE,	// ESC,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

	//m_vecKey[(int)KEY::LEFT].eState;	// LEFT Ű�� ����
	//m_vecKey[(int)KEY::LEFT].bPrev;	// LEFT Ű�� ���� ���� ����
}

void CKeyMgr::update()
{
	// ������ ��Ŀ�� �˾Ƴ���
	HWND hWnd = GetFocus();

	// ������ ��Ŀ�� ���� �� Ű �̺�Ʈ ����
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)	// Ű�� �����ִ�
			{
				if (m_vecKey[i].bPrevPush)
				{
					// �������� ���� �־���.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// �̹� �����ӿ� ������.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else // Ű�� �ȴ����ִ�.
			{
				if (m_vecKey[i].bPrevPush)
				{
					// ������ ���� �־���.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// �������� �ȴ����־���.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}
	}

	// ������ ��Ŀ�� ���� ����
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevPush = false;

			if (   KEY_STATE::TAP  == m_vecKey[i].eState 
				|| KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}

}