#pragma once
class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2     m_vForce;		// 크기, 방향
	Vec2     m_vAccel;		// 가속도
	Vec2     m_vAccelA;		// 추가 가속도
	float    m_fMass;		// 무게
	float    m_fFriction;	// 마찰력

	Vec2     m_vVelocity;	// 속도 ( 크기 : 속력, 방향 )
	Vec2     m_vMaxVelocity;// 최대 속도

	// F = M * A
	// V += A * DT

public:
	void  AddForce(Vec2 _vF)          { m_vForce += _vF; }
	float GetMass()             const { return m_fMass; }
	void  SetMass(float _fMass)       { m_fMass = _fMass; }
	Vec2  GetVelocity()         const { return m_vVelocity; }
	void  SetVelocity(Vec2 _v)        { m_vVelocity = _v; }
	void  AddVelocity(Vec2 _v)        { m_vVelocity += _v; }
	Vec2  GetMaxVelocity()      const { return m_vMaxVelocity; }
	void  SetMaxVelocity(Vec2 _v)     { m_vMaxVelocity = _v; }
	float GetSpeed()			      { return m_vVelocity.Length(); }
	void  SetAccelAlpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }

private:
	void Move();
	
public:
	void finalupdate();

public:
	CRigidBody();
	virtual ~CRigidBody();
	
	friend class CObject;
};

