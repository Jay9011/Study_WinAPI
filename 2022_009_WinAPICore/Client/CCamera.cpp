#include "pch.h"
#include "CCamera.h"

#include "Core.h"
#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(.5f)
	, m_eEffect(CAM_EFFECT::NONE)
	, m_pVeilTex(nullptr)
	, m_fEffectDuration(0.f)
	, m_fCurTime(0.f)
{
	
}

CCamera::~CCamera() = default;

void CCamera::init()
{
	Vec2 vResolution = Core::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

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

void CCamera::render(HDC _dc)
{
	if (CAM_EFFECT::NONE == m_eEffect)
		return;

	// �ð� ���� ���� üũ
	m_fCurTime += fDT;

	// ���� �ð��� ȿ�� �ִ� �ð��� �Ѿ ���
	if (m_fEffectDuration < m_fCurTime)
	{
		// ȿ�� ����
		m_eEffect = CAM_EFFECT::NONE;
		return;
	}

	float fRatio = 0.f;	// ȿ�� ���� ����
	fRatio = m_fCurTime / m_fEffectDuration;

	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		iAlpha = int(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == m_eEffect)
	{
		iAlpha = int(255.f * (1.f - fRatio));
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;				// alpha ü�ο� ��ϵ� �ҽ� ����
	bf.SourceConstantAlpha = iAlpha;// ��� pixel �� ����Ǵ� ���� alpha

	AlphaBlend(_dc
		, 0, 0
		, m_pVeilTex->Width(), m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, m_pVeilTex->Width(), m_pVeilTex->Height()
		, bf);

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
