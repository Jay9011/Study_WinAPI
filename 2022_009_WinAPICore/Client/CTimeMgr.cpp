#include "pch.h"
#include "CTimeMgr.h"

#include "Core.h"

CTimeMgr::CTimeMgr()
	: m_liPrevCount{}
	, m_liCurCount{}
	, m_liFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_liPrevCount);
	
	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_liFrequency);

}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_liCurCount);

	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구함.
	m_dDT = (double)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (double)m_liFrequency.QuadPart;
	
	// 이전 카운트 값을 현재 카운트로 갱신 (다음번에 계산을 하기 위해)
	m_liPrevCount = m_liCurCount;
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT;	// DT 누적

	// 1초에 한 번
	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		// 윈도우 타이틀바에 현재 프레임과 프레임간의 시간 출력
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,    DT : %f", m_iFPS, m_dDT);
		SetWindowText(Core::GetInst()->GetMainHWnd(), szBuffer);
	}
}
