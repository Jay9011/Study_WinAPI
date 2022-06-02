#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "AI.h"
#include "CState.h"

#include "CUIMgr.h"

CEventMgr::CEventMgr() = default;
CEventMgr::~CEventMgr() = default;

void CEventMgr::update()
{
	// === === === === ===
	//  Dead Object ó��
	// === === === === ===
	// ���� �����ӿ��� ����ص� Dead Object���� �����Ѵ�.
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// === === === ===
	//   Event ó��
	// === === === ===
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _event)
{
	switch (_event.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// ���� ���� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_event.lParam;
		if (!pDeadObj->IsDead())
		{
			pDeadObj->SetDead();
			// Object �� Dead ���·� ����
			m_vecDead.push_back(pDeadObj);
		}
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		// Scene ����
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_event.lParam);
		// ��Ŀ�� UI ���� ( ���� Scene�� UI�� ����Ű�� �ֱ� ���� )
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
		break;
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		// lParam : AI
		// wParam : Next Type
		AI* pAI = (AI*)_event.lParam;
		MON_STATE eNextState = (MON_STATE)_event.wParam;
		pAI->ChangeState(eNextState);
	}
		break;
	default:
		break;
	}
}
