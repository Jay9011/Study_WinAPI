#pragma once

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD		lParam;
	DWORD		rParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent;

public:
	void update();

};

