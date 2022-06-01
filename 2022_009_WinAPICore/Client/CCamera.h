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

	// 카메라 이펙트
	CTexture*          m_pVeilTex;		// 카메라 가림막 텍스처 (검은색)
	list<tCamEffect> m_listCamEffect;	// 카메라 효과 리스트

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

