#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::IDLE)
	, m_iDir(PLAYER_DIRECTION::DOWN)
	, m_iPrevDir(PLAYER_DIRECTION::DOWN)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	// RegidBody Setting
	CreateRigidBody();

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");
	CreateAnimator();
	
	GetAnimator()->CreateAnimation(L"IDLE_UP"   , pTex, Vec2(0.f, 130.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  1);
	GetAnimator()->CreateAnimation(L"IDLE_DOWN" , pTex, Vec2(0.f,   0.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  3);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT" , pTex, Vec2(0.f,  65.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  3);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 195.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  3);
	
	GetAnimator()->CreateAnimation(L"WALK_UP"   , pTex, Vec2(0.f, 390.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);
	GetAnimator()->CreateAnimation(L"WALK_DOWN" , pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);
	GetAnimator()->CreateAnimation(L"WALK_LEFT" , pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);

	GetAnimator()->Play(L"IDLE_DOWN", true);

	// Gravity Setting
	CreateGravity();
}

CPlayer::~CPlayer() = default;

void CPlayer::update()
{
	update_move();
	update_state();
	update_animation();

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}
	
	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	// 컴포넌트(충돌체, etc...) 가 있는 경우 렌더
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::update_state()
{
	if (KEY_TAP(KEY::W))
	{
		m_iDir = PLAYER_DIRECTION::UP;
		m_eCurState = PLAYER_STATE::WALK;
	}
	else if (KEY_TAP(KEY::S))
	{
		m_iDir = PLAYER_DIRECTION::DOWN;
		m_eCurState = PLAYER_STATE::WALK;
	}
	else if (KEY_TAP(KEY::A))
	{
		m_iDir = PLAYER_DIRECTION::LEFT;
		m_eCurState = PLAYER_STATE::WALK;
	}
	else if (KEY_TAP(KEY::D))
	{
		m_iDir = PLAYER_DIRECTION::RIGHT;
		m_eCurState = PLAYER_STATE::WALK;
	}
	
	if (0.f == GetRigidBody()->GetSpeed())
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();
	
	if (KEY_HOLD(KEY::W))
	{
		pRigid->AddForce(Vec2(0.f, -200.f));
	}
	if (KEY_HOLD(KEY::S))
	{
		pRigid->AddForce(Vec2(0.f, 200.f));
	}

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}

	if (KEY_TAP(KEY::W))
	{
		pRigid->AddVelocity(Vec2(0.f, -100.f));
	}
	if (KEY_TAP(KEY::S))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}

	if (KEY_TAP(KEY::A))
	{
		pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
		return;

	// 상태 변경에 따라 애니메이션 전환
	switch (m_eCurState)
	{ 
	case PLAYER_STATE::IDLE:
		switch (m_iDir)
		{
		case PLAYER_DIRECTION::UP:
			GetAnimator()->Play(L"IDLE_UP", true);
			break;
		case PLAYER_DIRECTION::DOWN:
			GetAnimator()->Play(L"IDLE_DOWN", true);
			break;
		case PLAYER_DIRECTION::LEFT:
			GetAnimator()->Play(L"IDLE_LEFT", true);
			break;
		case PLAYER_DIRECTION::RIGHT:
			GetAnimator()->Play(L"IDLE_RIGHT", true);
			break;
		}
		break;
	case PLAYER_STATE::WALK:
		switch (m_iDir)
		{
		case PLAYER_DIRECTION::UP:
			GetAnimator()->Play(L"WALK_UP", true);
			break;
		case PLAYER_DIRECTION::DOWN:
			GetAnimator()->Play(L"WALK_DOWN", true);
			break;
		case PLAYER_DIRECTION::LEFT:
			GetAnimator()->Play(L"WALK_LEFT", true);
			break;
		case PLAYER_DIRECTION::RIGHT:
			GetAnimator()->Play(L"WALK_RIGHT", true);
			break;
		}
		break;
	case PLAYER_STATE::ATTCK:
		break;
	case PLAYER_STATE::DEAD:
		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}
