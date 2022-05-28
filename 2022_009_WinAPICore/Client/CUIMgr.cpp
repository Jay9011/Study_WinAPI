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

		if (pUI->IsMouseOn())
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
		else
		{
			// ���� ��ư�� ����, ���ȴ� üũ�� �ٽ� �����Ѵ�.
			if (bLbtnAway)
			{
				pUI->MouseLBtnUp();
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
