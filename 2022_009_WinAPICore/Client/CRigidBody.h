#pragma once
class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2     m_vForce;		// 크기, 방향
	Vec2     m_vAccel;		// 가속도 
	float    m_fMass;		// 무게
	float    m_fFriction;	// 마찰력

	Vec2     m_vVelocity;	// 속도 ( 크기 : 속력, 방향 )
	float    m_fMaxSpeed;	// 최대 속력

	// F = M * A
	// V += A * DT

public:
	void  AddForce(Vec2 _vF)       { m_vForce += _vF; }
	float GetMass() const          { return m_fMass; }
	void  SetMass(float _fMass)    { m_fMass = _fMass; }
	void  SetVelocity(Vec2 _v)     { m_vVelocity = _v; }
	void  AddVelocity(Vec2 _v)     { m_vVelocity += _v; }
	void  SetMaxVelocity(float _f) { m_fMaxSpeed = _f; }
	float GetSpeed()			   { return m_vVelocity.Length(); }

private:
	void Move();
	
public:
	void finalupdate();

public:
	CRigidBody();
	virtual ~CRigidBody();
	
	friend class CObject;
};

