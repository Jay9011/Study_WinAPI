#pragma once
#include "../Game.h"

class CObj
{
protected:
	string   m_strTag;
	POSITION m_tPos;
	_SIZE    m_tSize;

public:
	string GetTag() const               { return m_strTag; }
	void   SetTag(const string& strTag) { m_strTag = strTag; }
	
	POSITION GetPos() const               { return m_tPos; }
	void     SetPos(const POSITION& tPos) { m_tPos = tPos; }
	void     SetPos(float x, float y)     { m_tPos.x = x; m_tPos.y = y; }

	_SIZE GetSize() const             { return m_tSize; }
	void  SetSize(const _SIZE& tSize) { m_tSize = tSize; }
	void  SetSize(float x, float y)   { m_tSize.x = x; m_tSize.y = y; }

protected:
	CObj();
	virtual ~CObj();

// =========== 레퍼런스 카운터 ===========
protected:
	int m_iRef;

public:
	void AddRef() { ++m_iRef; }
	int  Release()
	{
		--m_iRef;
		if (m_iRef == 0)
		{
			delete this;
			return 0;
		}
		return m_iRef;
	}
};

