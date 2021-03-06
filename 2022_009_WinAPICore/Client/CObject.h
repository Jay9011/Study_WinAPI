#pragma once
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	bool		m_bAlive;	// 삭제예정 flag

	/* === === === === === === === === === ===
			컴포넌트
	=== === === === === === === === === === */
	CCollider*  m_pCollider;
	CAnimator*  m_pAnimator;
	CRigidBody* m_pRigidBody;
	CGravity*   m_pGravity;

public:
	virtual void start() {};	// Scene 이 시작되기 직전에 호출되는 함수
	virtual void update() = 0;
	virtual void finalupdate();

	virtual void render(HDC _dc);
	void component_render(HDC _dc);

	

	/* === === === === === === === === ===
			Collider 관련
	=== === === === === === === === === === */
	void CreateCollider();
	CCollider* GetCollider() const { return m_pCollider; }
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	
	/* === === === === === === === === ===
			Animator 관련
	=== === === === === === === === === === */
	void CreateAnimator();
	CAnimator* GetAnimator() { return m_pAnimator; }
	

	/* === === === === === === === === ===
			RigidBody 관련
	=== === === === === === === === === === */
	void CreateRigidBody();
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

	/* === === === === === === === === ===
			Gravity 관련
	=== === === === === === === === === === */
	void CreateGravity();
	CGravity* GetGravity() { return m_pGravity; }

	
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

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();
	virtual CObject* Clone() = 0;

	friend class CEventMgr;
};