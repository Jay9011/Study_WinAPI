#pragma once

class CObject;

class CCollider
{
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

private:
	static UINT g_iNextID;

	CObject* m_pOwner;	// collider를 소유하고 있는 오브젝트

	Vec2 m_vOffsetPos;	// 오브젝트로부터 상대적인 위치
	Vec2 m_vFinalPos;	// finalupdate 에서 매 프레임마다 계산
	
	Vec2 m_vScale;		// 충돌체의 크기

	UINT m_iID;			// 충돌체 고유한 ID 값

public:
	void finalupdate();
	void render(HDC _dc);

	void SetOffsetPos(Vec2 _vPos)	{ m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale)		{ m_vScale = _vScale; }
	Vec2 GetOffsetPos() const { return m_vOffsetPos; }
	Vec2 GetScale()		const { return m_vScale; }

	/*
	*  Operator
	*/
	CCollider& operator = (CCollider& _origin) = delete;

	friend class CObject;
};

