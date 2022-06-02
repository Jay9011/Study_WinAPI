#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFriction(100.f)
	, m_fMaxSpeed(200.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Move()
{
	float fSpeed = m_vVelocity.Length();	// �̵� �ӷ�

	if (0.f != fSpeed)
	{
		//Vec2 vDir = m_vVelocity;
		//vDir.Normalize();					// �̵� ����

		Vec2 vPos = m_pOwner->GetPos();		// ������Ʈ�� ���� ��ġ

		vPos += m_vVelocity * fDT;			// �̵�

		m_pOwner->SetPos(vPos);		// ������Ʈ�� ��ġ�� �̵��� ��ġ�� ����
	}

}

void CRigidBody::finalupdate()
{
	// ���� ũ��
	float fForce = m_vForce.Length();
	
	if (0.f != fForce)
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float fAccel = fForce / m_fMass;
	
		// ���ӵ�
		m_vAccel = m_vForce * fAccel;

		// �ӵ�
		m_vVelocity += m_vAccel * fDT;
	}
	
	// �����¿� ���� �ݴ� ���������� ���ӵ�
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();
		
		Vec2 vFriction = vFricDir * m_fFriction * fDT;
		if (m_vVelocity.Length() < vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}
	
	// �ӵ� ���� �˻�
	if(m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;	// �ӵ� ����
	}
	
	// �ӵ��� ���� �̵�
	Move();
	
	// �� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);
}