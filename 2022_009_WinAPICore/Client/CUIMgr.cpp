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

		// �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�.
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

				// ���� ��ư�� ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetTargetUI(CUI* _pParentUI)
{
	CUI* pTargetUI = nullptr;
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�. ( Level ��ȸ �� ��� )
	static list<CUI*>   queue;
	static vector<CUI*> vecNoneTarget;
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())	// Queue �� �� �� ���� Level ��ȸ�� ����Ѵ�.
	{
		// 1-1. Queue ���� �� ������ �ϳ��� ������.
		CUI* pUI = queue.front();
		queue.pop_front();

		// 1-2. Queue���� ������ UI �� TargetUI ���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������, �� ���� ������ �ڽ� UI �̴�.
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
		
		// 1-2. ���� �����Ϳ��� �ڽ��� �־��ٸ�, ��� �ڽĵ��� Queue �� �ִ´�. ( ������ ����, ��� �θ��� �ڽ����� ���� Level ��ȸ )
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// ���� ��ư�� ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
