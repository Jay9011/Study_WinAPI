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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_liPrevCount);
	
	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_liFrequency);

}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_liCurCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ����.
	m_dDT = (double)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (double)m_liFrequency.QuadPart;
	
	// ���� ī��Ʈ ���� ���� ī��Ʈ�� ���� (�������� ����� �ϱ� ����)
	m_liPrevCount = m_liCurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;	// DT ����

	// 1�ʿ� �� ��
	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		// ������ Ÿ��Ʋ�ٿ� ���� �����Ӱ� �����Ӱ��� �ð� ���
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,    DT : %f", m_iFPS, m_dDT);
		SetWindowText(Core::GetInst()->GetMainHWnd(), szBuffer);
	}
}
