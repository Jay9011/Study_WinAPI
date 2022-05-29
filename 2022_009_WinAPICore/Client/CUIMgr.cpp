#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다.
		pUI = GetTargetUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLBtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{
				pUI->MouseLBtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLBtnClicked();
				}

				// 왼쪽 버튼을 떼면, 눌렸던 체크를 다시 해제한다.
				pUI->m_bLbtnDown = false;
			}
		}
	}
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
