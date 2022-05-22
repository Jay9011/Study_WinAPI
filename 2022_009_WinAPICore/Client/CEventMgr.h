#pragma once

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent;	// 한 번에 실행시킬 Event 모음
	vector<CObject*> m_vecDead;	// 삭제 예정 Object

public:
	void update();

private:
	void Excute(const tEvent& _event);

public:
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

};

