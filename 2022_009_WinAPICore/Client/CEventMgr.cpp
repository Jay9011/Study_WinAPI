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
	//  Dead Object 처리
	// === === === === ===
	// 이전 프레임에서 등록해둔 Dead Object들을 삭제한다.
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// === === === ===
	//   Event 처리
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
		// 삭제 예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_event.lParam;
		if (!pDeadObj->IsDead())
		{
			pDeadObj->SetDead();
			// Object 를 Dead 상태로 변경
			m_vecDead.push_back(pDeadObj);
		}
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		// Scene 변경
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_event.lParam);
		// 포커스 UI 해제 ( 이전 Scene의 UI를 가리키고 있기 때문 )
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
