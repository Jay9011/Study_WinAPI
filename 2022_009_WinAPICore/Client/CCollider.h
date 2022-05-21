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

	CObject* m_pOwner;	// collider�� �����ϰ� �ִ� ������Ʈ

	Vec2 m_vOffsetPos;	// ������Ʈ�κ��� ������� ��ġ
	Vec2 m_vFinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	
	Vec2 m_vScale;		// �浹ü�� ũ��

	UINT m_iID;			// �浹ü ������ ID ��
	UINT m_iCol;

public:
	void finalupdate();
	void render(HDC _dc);

	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther);		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);	// �浹�� ���۵� ���
	void OnCollisionExit(CCollider* _pOther);	// �浹�� ��� ���

	Vec2 GetFinalPos()		  const { return m_vFinalPos; }
	Vec2 GetOffsetPos()		  const { return m_vOffsetPos; }
	void SetOffsetPos(Vec2 _vPos)	{ m_vOffsetPos = _vPos; }
	Vec2 GetScale()			  const { return m_vScale; }
	void SetScale(Vec2 _vScale)		{ m_vScale = _vScale; }

	UINT GetID() { return m_iID; }

	/*
	*  Operator
	*/
	CCollider& operator = (CCollider& _origin) = delete;

	friend class CObject;
};

