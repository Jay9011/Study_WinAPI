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
	// 1. Focused UI Ȯ�� ( ���� ��Ŀ�� �� UI �� ã�´�. )
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. Focused UI ������, �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�.
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

			// ���� ��ư�� ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// ��Ŀ�� ������ ��û�ϰų� �̹� ��Ŀ������ ���
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

	// vector ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);

}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI �� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)	// ���� Ŭ���� �߻����� ���� ���, ���� Focused UI �״�� �����Ѵ�.
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

	// �̹��� Focus �� UI�� ���� Ŭ���� �����ߴ�.
	if (vecUI.end() == targetiter)
		return nullptr;

	pFocusedUI = (CUI*)*targetiter;

	// vector ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
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
