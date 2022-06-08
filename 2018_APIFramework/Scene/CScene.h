#pragma once
#include "../Game.h"

class CScene
{
protected:
	list<class CLayer*> m_LayerList;
	
public:
	class CLayer* CreateLayer(const string& strTag, int iZOrder = 0);
	
public:
	virtual bool Init();

	static bool LayerSort(class CLayer* pLayer1, class CLayer* pLayer2);
	

protected:
	CScene();
	virtual ~CScene() = 0;

	friend class CSceneManager;
};

