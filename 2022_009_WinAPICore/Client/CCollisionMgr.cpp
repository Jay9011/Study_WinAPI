#include "pch.h"
#include "CCollisionMgr.h"

CCollisionMgr::CCollisionMgr()
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::update()
{
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 더 큰 값을 열(비트)로 사용. 해야 한 면만 사용해서 체크할 수 있다.
}