#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;		// ���� ���� ��� ��ǥ
	Vec2	vSlice;		// �� �������� �̹��� ũ��
	float	fDuration;	// �����ð�
	Vec2	vOffSet;
};

class CAnimation
{
private:
	wstring		m_strName;
	CAnimator*	m_pAnimator;
	
	CTexture*			m_pTex;		// Animation �� ����ϴ� �ؽ�ó
	vector<tAnimFrm>	m_vecFrm;	// ��� ������ ����
	int					m_iCurFrm;	// ���� ������
	float				m_fAccTime;	// �ð� ����
	bool				m_bFinish;	// ��� ���� ���� ����

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

