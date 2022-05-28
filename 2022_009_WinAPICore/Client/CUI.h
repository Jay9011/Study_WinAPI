#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    CUI*         m_pParentUI;
    vector<CUI*> m_vecChildUI;

    Vec2 m_vFinalPos;

    bool m_bCamAffected;// UI 가 카메라에 영향을 받는 유무
    bool m_bMouseOn;    // UI 위에 마우스가 있는지 여부
    bool m_bLbtnDown;   // UI 에 왼쪽 버튼이 눌린적이 있는지

public:
   
    /* === === === === === === === === ===
                 Mouse Event
     === === === === === === === === === */
    void MouseOnCheck();

    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();
    
    /* === === === === === === === === ===
                  Get / Set
     === === === === === === === === === */
    CUI* GetParent() const   { return m_pParentUI; }
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    Vec2 GetFinalPos() const { return m_vFinalPos; }
    bool IsMouseOn() const   { return m_bMouseOn; }
    
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;
private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

public:
    CUI(bool _bCamAff);
    ~CUI() override;
    CLONE(CUI);

    friend class CUIMgr;
};

