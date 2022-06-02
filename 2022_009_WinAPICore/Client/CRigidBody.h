#pragma once
class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2     m_vForce;		// ũ��, ����
	Vec2     m_vAccel;		// ���ӵ� 
	float    m_fMass;		// ����
	float    m_fFriction;	// ������

	Vec2     m_vVelocity;	// �ӵ� ( ũ�� : �ӷ�, ���� )
	float    m_fMaxSpeed;	// �ִ� �ӷ�

	// F = M * A
	// V += A * DT

public:
	void  AddForce(Vec2 _vF)       { m_vForce += _vF; }
	void  SetMass(float _fMass)    { m_fMass = _fMass; }
	float GetMass() const          { return m_fMass; }
	void  SetVelocity(Vec2 _v)     { m_vVelocity = _v; }
	void  AddVelocity(Vec2 _v)     { m_vVelocity += _v; }
	void  SetMaxVelocity(float _f) { m_fMaxSpeed = _f; }

private:
	void Move();
	
public:
	void finalupdate();

public:
	CRigidBody();
	virtual ~CRigidBody();
	
	friend class CObject;
};
