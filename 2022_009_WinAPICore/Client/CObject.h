#pragma once

class CCollider;

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

	CCollider* m_pCollider;

	bool		m_bAlive;	// 삭제예정 flag

public:
	virtual void update() = 0;
	virtual void finalupdate() final;

	virtual void render(HDC _dc);
	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

	/* === === === === === === === === ===
			Collider 관련
	=== === === === === === === === === === */
	void CreateCollider();
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}
	CCollider* GetCollider() const { return m_pCollider; }

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