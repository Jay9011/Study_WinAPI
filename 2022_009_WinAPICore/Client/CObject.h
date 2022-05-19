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

	void SetPos  (Vec2 _vPos)   { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetPos()   const { return m_vPos; }
	Vec2 GetScale() const { return m_vScale; }

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

private:
	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;
};