#pragma once
#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject
{
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	bool		m_bAlive;	// �������� flag

	/* === === === === === === === === === ===
			������Ʈ
	=== === === === === === === === === === */
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;


public:
	virtual void update() = 0;
	virtual void finalupdate();

	virtual void render(HDC _dc);
	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

	/* === === === === === === === === ===
			Collider ����
	=== === === === === === === === === === */
	void CreateCollider();
	CCollider* GetCollider() const { return m_pCollider; }
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	/* === === === === === === === === ===
			Animator ����
	=== === === === === === === === === === */
	void CreateAnimator();
	CAnimator* GetAnimator() { return m_pAnimator; }

	/* === === === === === === === === ===
			Get / Set
	=== === === === === === === === === === */
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	Vec2 GetPos() const { return m_vPos; }

	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetScale() const { return m_vScale; }
	
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() const { return m_strName; }

	bool IsDead() const { return !m_bAlive; }

private:
	void SetDead() { m_bAlive = false; }

	friend class CEventMgr;
};