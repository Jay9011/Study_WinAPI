#pragma once
#include "CObject.h"
class CUI :
    public CObject
{
private:
    CUI*         m_pParentUI;
    vector<CUI*> m_vecChildUI;

    Vec2 m_vFinalPos;

    bool m_bCamAffected;// UI �� ī�޶� ������ �޴� ����
    bool m_bMouseOn;    // UI ���� ���콺�� �ִ��� ����
    bool m_bLbtnDown;   // UI �� ���� ��ư�� �������� �ִ���

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
          CUI*          GetParent()   const { return m_pParentUI; }
          void          AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    const vector<CUI*>& GetChildUI()  const { return m_vecChildUI; }
          Vec2          GetFinalPos() const { return m_vFinalPos; }
          bool          IsMouseOn()   const { return m_bMouseOn; }
          bool          IsLbtnDown()  const { return m_bLbtnDown; }

    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;
private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    ~CUI() override;
    CUI* Clone() override = 0;

    friend class CUIMgr;
};

