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
	float      m_fDuration;
	float      m_fCurTime;
};


class CCamera
{
	SINGLE(CCamera)
private:
	Vec2       m_vLookAt;		// 카메라가 보는 위치
	Vec2       m_vPrevLookAt;	// 카메라가 보는 이전 프레임 위치
	Vec2       m_vCurLookAt;	// 이전 위치와 현재 위치 보정 위치
	Vec2       m_vDiff;			// 해상도 중심위치와 카메라 LookAt 간의 차이 값

	CObject*   m_pTargetObj;	// 카메라의 타겟 오브젝트
	float      m_fTime;			// 타겟을 따라가는데 걸리는 시간
	float      m_fSpeed;		// 타겟을 따라가는 속도
	float      m_fAccTime;		// 누적 시간

	// 등가속 운동을 위한 변수
	float	   m_fSpeed0;		// 최초 속도
	float	   m_fAccSpeed;		// 시간당 속도

	CAM_EFFECT m_eEffect;			// 카메라 효과
	CTexture*  m_pVeilTex;			// 카메라 가림막 텍스처 (검은색)
	float      m_fEffectDuration;	// 효과 진행 예정 시간
	float      m_fCurTime;			// 현재 효과 진행 시간

	vector<tCamEffect> m_vecCamEffect;	// 카메라 효과 벡터

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
		if (0.f == _fDuration)
			assert(0);

		m_eEffect = CAM_EFFECT::FADE_IN;
		m_fEffectDuration = _fDuration;
		m_fCurTime = 0;
	}
	void FadeOut(float _fDuration)
	{
		if (0.f == _fDuration)
			assert(0);
		
		m_eEffect = CAM_EFFECT::FADE_OUT;
		m_fEffectDuration = _fDuration;
		m_fCurTime = 0;
	}

private:
	void CalDiff();

};

