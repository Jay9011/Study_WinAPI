#pragma once
#include "CUI.h"

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

class CBtnUI :
    public CUI
{
private:
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;

public:
    void MouseOn() override;
    void MouseLBtnDown() override;
    void MouseLBtnUp() override;
    void MouseLBtnClicked() override;

    void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) 
    { 
        m_pFunc  = _pFunc; 
        m_param1 = _param1;
        m_param2 = _param2;
    }

public:
    CBtnUI();
    ~CBtnUI() override;
    CLONE(CBtnUI)
};

