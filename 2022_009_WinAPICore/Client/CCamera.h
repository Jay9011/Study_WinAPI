#pragma once

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT eEffect;
	float      fDuration;
	float      fCurTime;
};


class CCamera
{
	SINGLE(CCamera)
private:
	Vec2       m_vLookAt;		// ī�޶� ���� ��ġ
	Vec2       m_vPrevLookAt;	// ī�޶� ���� ���� ������ ��ġ
	Vec2       m_vCurLookAt;	// ���� ��ġ�� ���� ��ġ ���� ��ġ
	Vec2       m_vDiff;			// �ػ� �߽���ġ�� ī�޶� LookAt ���� ���� ��

	CObject*   m_pTargetObj;	// ī�޶��� Ÿ�� ������Ʈ
	float      m_fTime;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float      m_fSpeed;		// Ÿ���� ���󰡴� �ӵ�
	float      m_fAccTime;		// ���� �ð�

	// ��� ��� ���� ����
	float	   m_fSpeed0;		// ���� �ӵ�
	float	   m_fAccSpeed;		// �ð��� �ӵ�

	// ī�޶� ����Ʈ
	CTexture*          m_pVeilTex;		// ī�޶� ������ �ؽ�ó (������)
	list<tCamEffect> m_listCamEffect;	// ī�޶� ȿ�� ����Ʈ

public:
	void init();
	void update();
	void render(HDC _dc);

	Vec2 GetLookAt()                  { return m_vCurLookAt; }
	void SetLookAt(Vec2 _vLook)       
	{ 
		m_vLookAt   = _vLook; 
		m_fSpeed0   = 2 * (m_vLookAt - m_vPrevLookAt).Length() / m_fTime;
		m_fSpeed    = (m_vLookAt - m_vPrevLookAt).Length() / m_fTime;
		m_fAccTime  = 0.f;
		m_fAccSpeed = m_fSpeed0;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos)  { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	
	
	/* === === === === === === === === ===
				Camera Effect
	=== === === === === === === === === */
	void FadeIn(float _fDuration)
	{
		if (0.f == _fDuration) assert(0);

		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);
	}
	void FadeOut(float _fDuration)
	{
		if (0.f == _fDuration) assert(0);
		
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;
		
		m_listCamEffect.push_back(ef);
	}

private:
	void CalDiff();

};

