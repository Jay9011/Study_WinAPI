#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr() = default;

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	
	// vector<CObject*>& 로 받아왔는데, 변수를 vector<CObject*>로만 담으면,
	// 복사되어 지역변수로 사용되어진다.
	// 만약 의도한대로 원본 그대로를 사용하고 싶다면,
	// 리턴 받은 형식인 vector<CObject*>&로 받아야 한다.
	const vector<CObject*>& vecLeft  = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		// 해당 Object에 충돌체가 없는 경우
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// 해당 Object에 충돌체가 없거나 자기 자신과의 충돌인 경우
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
				continue;

			// 두 Object 모두 충돌체가 있는 경우 충돌 검사
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// 충돌 됨
			}
			else
			{
				// 충돌 안됨
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{

	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 더 큰 값을 열(비트)로 사용. 해야 한 면만 사용해서 체크할 수 있다.

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}
