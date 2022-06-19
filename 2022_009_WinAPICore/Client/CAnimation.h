#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;		// 시작 좌측 상단 좌표
	Vec2	vSlice;		// 한 프레임의 이미지 크기
	float	fDuration;	// 유지시간
	Vec2	vOffSet;
};

class CAnimation
{
private:
	wstring		m_strName;
	CAnimator*	m_pAnimator;
	
	CTexture*			m_pTex;		// Animation 이 사용하는 텍스처
	vector<tAnimFrm>	m_vecFrm;	// 모든 프레임 정보
	int					m_iCurFrm;	// 현재 프레임
	float				m_fAccTime;	// 시간 누적
	bool				m_bFinish;	// 재생 끝에 도달 여부

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

public:
	const wstring& GetName() const { return m_strName; }
	bool IsFinish() const { return m_bFinish; }
	
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false; 
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	UINT GetMaxFrame() const { return (UINT)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

