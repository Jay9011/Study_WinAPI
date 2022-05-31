#pragma once
#include "CUI.h"

class CScene;

typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);

typedef void(CScene::* SCENE_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
private:
    BTN_FUNC      m_pFunc;
    DWORD_PTR     m_param1;
    DWORD_PTR     m_param2;

    CScene*       m_pSceneInst;
    SCENE_MEMFUNC m_pSceneFunc;

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

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
    {
        m_pSceneInst = _pScene;
        m_pSceneFunc = _pSceneFunc;
    }

public:
    CBtnUI();
    ~CBtnUI() override;
    CLONE(CBtnUI)
};

