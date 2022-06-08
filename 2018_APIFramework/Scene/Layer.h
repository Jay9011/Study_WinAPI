#pragma once
#include "../Game.h"

class CLayer
{
private:
	class CScene* m_pScene;
	
	string	m_strTag;
	int		m_iZOrder;

	list<class CObj*> m_ObjList;

public:
	void   SetTag(const string& strTag) { m_strTag = strTag; }
	string GetTag() const               { return m_strTag; }
	
	void   SetZOrder(int iZOrder)       { m_iZOrder = iZOrder; }
	int    GetZOrder() const            { return m_iZOrder; }

	void    SetScene(class CScene* pScene) { m_pScene = pScene; }
	CScene* GetScene() const               { return m_pScene; }

private:
	CLayer();

public:
	~CLayer();

	friend class CScene;
};

