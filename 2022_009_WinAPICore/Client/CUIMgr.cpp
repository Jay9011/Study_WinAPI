#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. Focused UI 확인 ( 현재 포커싱 된 UI 를 찾는다. )
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. Focused UI 내에서, 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다.
	CUI* pTargetUI = GetTargetUI(m_pFocusedUI);
	
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLBtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLBtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLBtnClicked();
			}

			// 왼쪽 버튼을 떼면, 눌렸던 체크를 다시 해제한다.
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// 포커싱 해제를 요청하거나 이미 포커싱중인 경우
	if (nullptr == _pUI || m_pFocusedUI == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	
	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
			break;
	}

	// vector 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);

}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI 를 받아두고 변경되었는지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)	// 왼쪽 클릭이 발생하지 않은 경우, 기존 Focused UI 그대로 리턴한다.
		return pFocusedUI;

	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// 이번에 Focus 된 UI가 없이 클릭만 동작했다.
	if (vecUI.end() == targetiter)
		return nullptr;

	pFocusedUI = (CUI*)*targetiter;

	// vector 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetUI(CUI* _pParentUI)
{
	CUI* pTargetUI = nullptr;
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. 부모 UI 포함, 모든 자식들을 검사한다. ( Level 순회 를 사용 )
	static list<CUI*>   queue;
	static vector<CUI*> vecNoneTarget;
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())	// Queue 가 빌 때 까지 Level 순회를 사용한다.
	{
		// 1-1. Queue 제일 앞 데이터 하나를 꺼낸다.
		CUI* pUI = queue.front();
		queue.pop_front();

		// 1-2. Queue에서 꺼내온 UI 가 TargetUI 인지 확인
		// 타겟 UI 둘 중, 더 우선순위가 높은 기준은, 더 낮은 계측의 자식 UI 이다.
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		// 1-2. 꺼낸 데이터에게 자식이 있었다면, 모든 자식들을 Queue 에 넣는다. ( 조건이 없는, 모든 부모의 자식을에 대한 Level 순회 )
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// 왼쪽 버튼을 떼면, 눌렸던 체크를 다시 해제한다.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
