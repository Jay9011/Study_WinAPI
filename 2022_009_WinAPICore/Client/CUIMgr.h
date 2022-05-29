#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr)
private:
	CUI* m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI);
private:
	// UI 들의 포커싱 상태를 갱신한다.
	CUI* GetFocusedUI();
	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아 반환한다.
	CUI* GetTargetUI(CUI* _pParentUI);
};

