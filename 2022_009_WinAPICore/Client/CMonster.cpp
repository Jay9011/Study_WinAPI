#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster() = default;

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	// ���� �������� �ð��� m_fSpeed ��ŭ �̵�
	vCurPos.x += fDT * m_fSpeed * (float)m_iDir;
	
	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	if (0.f < fDist)						// �ִ� �Ÿ��� �Ѿ ���
	{
		// ���� ����
		m_iDir *= -1;
		vCurPos.x += fDist * (float)m_iDir;	// �ʰ��� �Ÿ� ��ŭ �ǵ�����.
	}

	SetPos(vCurPos);
}
