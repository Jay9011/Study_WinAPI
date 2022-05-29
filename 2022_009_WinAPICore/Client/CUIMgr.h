#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr)
private:

public:
	void update();

private:
	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아 반환한다.
	CUI* GetTargetUI(CUI* _pParentUI);

};

