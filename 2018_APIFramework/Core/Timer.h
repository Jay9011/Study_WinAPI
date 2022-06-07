#pragma once
#include "../Game.h"

class CTimer
{
private:
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTime;
	float m_fDeltaTime;
	float m_fFPS;
	float m_fFPS_Time;
	int   m_iFrameMax;
	int   m_iFrame;

public:
	bool Init();
	void Update();

public:
	float GetDeltaTime() const { return m_fDeltaTime; }
	float GetFPS() const       { return m_fFPS; }

	DECLARE_SINGLE(CTimer)
};

