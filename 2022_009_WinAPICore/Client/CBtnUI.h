#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
private:

public:
    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();

public:
    CBtnUI();
    ~CBtnUI() override;
    CLONE(CBtnUI)
};

