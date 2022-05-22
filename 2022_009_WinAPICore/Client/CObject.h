#pragma once

class CCollider;

class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	void CreateCollider();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	Vec2 GetPos() const { return m_vPos; }

	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetScale() const { return m_vScale; }
	
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() const { return m_strName; }

	CCollider* GetCollider() const { return m_pCollider; }

private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;
};