#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr)
private:

public:
	void update();

private:
	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�� ��ȯ�Ѵ�.
	CUI* GetTargetUI(CUI* _pParentUI);

};

