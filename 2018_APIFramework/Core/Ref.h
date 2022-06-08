#pragma once
#include "../Game.h"
class CRef
{
protected:
	int m_iRef;
	
public:
	void AddRef() { ++m_iRef; };
	int  GetRef() const { return m_iRef; };
	int  Release()
	{
		if (--m_iRef == 0)
		{
			delete this;
			return 0;
		}
		return m_iRef;
	};

protected:
	CRef();
	virtual ~CRef() = 0;

};

