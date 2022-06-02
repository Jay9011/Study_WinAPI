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
	float fSpeed = m_vVelocity.Length();	// 이동 속력

	if (0.f != fSpeed)
	{
		//Vec2 vDir = m_vVelocity;
		//vDir.Normalize();					// 이동 방향

		Vec2 vPos = m_pOwner->GetPos();		// 오브젝트의 현재 위치

		vPos += m_vVelocity * fDT;			// 이동

		m_pOwner->SetPos(vPos);		// 오브젝트의 위치를 이동한 위치로 설정
	}

}

void CRigidBody::finalupdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();
	
	if (0.f != fForce)
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float fAccel = fForce / m_fMass;
	
		// 가속도
		m_vAccel = m_vForce * fAccel;

		// 속도
		m_vVelocity += m_vAccel * fDT;
	}
	
	// 마찰력에 의한 반대 방향으로의 가속도
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();
		
		Vec2 vFriction = vFricDir * m_fFriction * fDT;
		if (m_vVelocity.Length() < vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}
	
	// 속도 제한 검사
	if(m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;	// 속도 제한
	}
	
	// 속도에 따른 이동
	Move();
	
	// 힘 초기화
	m_vForce = Vec2(0.f, 0.f);
}
