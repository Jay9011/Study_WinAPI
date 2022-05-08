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

	//m_vecKey[(int)KEY::LEFT].eState;	// LEFT 키의 상태
	//m_vecKey[(int)KEY::LEFT].bPrev;	// LEFT 키의 이전 눌림 상태
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기
	HWND hWnd = GetFocus();

	// 윈도우 포커싱 중일 때 키 이벤트 동작
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)	// 키가 눌려있다
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려 있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이번 프레임에 눌렀다.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else // 키가 안눌려있다.
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에 눌려 있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에도 안눌려있었다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}
	}

	// 윈도우 포커싱 해제 상태
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
