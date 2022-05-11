#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_liPrevCount;
	LARGE_INTEGER	m_liCurCount;
	LARGE_INTEGER	m_liFrequency;
	
	// FPS
	// 1 �����Ӵ� �ð� (DeltaTime)
	double			m_dDT;	// ������ ���� �ð� ��
	double			m_dAcc;	// ���ݱ��� �ɸ� �ð� ����
	UINT			m_iCallCount;	// ȣ�� Ƚ�� ����
	UINT			m_iFPS;			// �ʴ� ȣ�� Ƚ��

public:
	void init();
	void update();

	double	GetDT() { return m_dDT; }
	float	GetfDT() { return (float)m_dDT; }
};

