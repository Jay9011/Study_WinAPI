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
	vector<tEvent> m_vecEvent;	// �� ���� �����ų Event ����
	vector<CObject*> m_vecDead;	// ���� ���� Object

public:
	void update();

private:
	void Excute(const tEvent& _event);

public:
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

};

