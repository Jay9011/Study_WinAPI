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
	// UI ���� ��Ŀ�� ���¸� �����Ѵ�.
	CUI* GetFocusedUI();
	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�� ��ȯ�Ѵ�.
	CUI* GetTargetUI(CUI* _pParentUI);
};

