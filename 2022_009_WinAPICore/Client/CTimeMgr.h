#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_liPrevCount;
	LARGE_INTEGER	m_liCurCount;
	LARGE_INTEGER	m_liFrequency;
	
	// FPS
	// 1 프레임당 시간 (DeltaTime)
	double			m_dDT;	// 프레임 간의 시간 값
	double			m_dAcc;	// 지금까지 걸린 시간 누적
	UINT			m_iCallCount;	// 호출 횟수 누적
	UINT			m_iFPS;			// 초당 호출 횟수

public:
	void init();
	void update();

	double	GetDT() { return m_dDT; }
	float	GetfDT() { return (float)m_dDT; }
};

