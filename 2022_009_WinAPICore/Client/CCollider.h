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
	UINT m_iCol;

	bool m_bActive;		// 충돌체 활성화 여부

public:
	void finalupdate();
	void render(HDC _dc);

	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther);		// 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);	// 충돌이 시작된 경우
	void OnCollisionExit(CCollider* _pOther);	// 충돌을 벗어난 경우

	Vec2 GetFinalPos()		  const { return m_vFinalPos; }
	Vec2 GetOffsetPos()		  const { return m_vOffsetPos; }
	void SetOffsetPos(Vec2 _vPos)	{ m_vOffsetPos = _vPos; }
	Vec2 GetScale()			  const { return m_vScale; }
	void SetScale(Vec2 _vScale)		{ m_vScale = _vScale; }
	UINT GetID()			  const { return m_iID; }
	CObject* GetObj()		  const { return m_pOwner; }


	/*
	*  Operator
	*/
	CCollider& operator = (CCollider& _origin) = delete;

	friend class CObject;
};

