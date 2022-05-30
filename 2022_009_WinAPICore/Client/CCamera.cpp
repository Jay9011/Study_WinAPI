#include "pch.h"
#include "CCamera.h"

#include "Core.h"
#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(.5f)
{

}

CCamera::~CCamera() = default;

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���� ���
	CalDiff();
}

void CCamera::CalDiff()
{
	// ���� LookAt�� ���� Look �� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.
	
	m_fAccTime += fDT;
	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_fAccSpeed -= m_fSpeed0 / m_fTime * fDT;
			m_vCurLookAt = m_vPrevLookAt + (vLookDir.Normalize() * m_fAccSpeed * fDT);
		}

	}

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
