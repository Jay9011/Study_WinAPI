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
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");
	CreateAnimator();

	// Animation 파일로 로드하기
	GetAnimator()->LoadAnimation(L"animation\\player_idle_up.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_down.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_up.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_down.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
	
	//GetAnimator()->CreateAnimation(L"IDLE_UP"   , pTex, Vec2(0.f, 130.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  1);
	//GetAnimator()->CreateAnimation(L"IDLE_DOWN" , pTex, Vec2(0.f,   0.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  3);
	//GetAnimator()->CreateAnimation(L"IDLE_LEFT" , pTex, Vec2(0.f,  65.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  3);
	//GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 195.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .5f,  3);

	//GetAnimator()->CreateAnimation(L"WALK_UP"   , pTex, Vec2(0.f, 390.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_DOWN" , pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_LEFT" , pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), .1f, 10);

	//// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"IDLE_UP")->Save(L"animation\\player_idle_up.anim");
	//GetAnimator()->FindAnimation(L"IDLE_DOWN")->Save(L"animation\\player_idle_down.anim");
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	//GetAnimator()->FindAnimation(L"WALK_UP")->Save(L"animation\\player_walk_up.anim");
	//GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\player_walk_down.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");

	// Gravity Setting
	CreateGravity();
}

CPlayer::~CPlayer() = default;

void CPlayer::update()
{
	update_move();
	update_state();
	update_animation();

	if (KEY_TAP(KEY::P))
	{
		SetPos(Vec2(640.f, 384.f));
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
	if (KEY_HOLD(KEY::W))
	{
		m_iDir = PLAYER_DIRECTION::UP;
		if(PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}
	else if (KEY_HOLD(KEY::S))
	{
		m_iDir = PLAYER_DIRECTION::DOWN;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}
	else if (KEY_HOLD(KEY::A))
	{
		m_iDir = PLAYER_DIRECTION::LEFT;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}
	else if (KEY_HOLD(KEY::D))
	{
		m_iDir = PLAYER_DIRECTION::RIGHT;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}
	
	if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	
	if (KEY_TAP(KEY::SPACE))
	{
		//CreateMissile();
		m_eCurState = PLAYER_STATE::JUMP;
		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -300.f));
		}
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
		if(pRigid->GetVelocity().y == 0.f)
			pRigid->AddVelocity(Vec2(0.f, -100.f));
	}
	if (KEY_TAP(KEY::S))
	{
		if (pRigid->GetVelocity().y == 0.f)
			pRigid->AddVelocity(Vec2(0.f, 100.f));
	}

	if (KEY_TAP(KEY::A))
	{
		if (pRigid->GetVelocity().x == 0.f)
			pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		if (pRigid->GetVelocity().x == 0.f)
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
	case PLAYER_STATE::JUMP:
		switch (m_iDir)
		{
		case PLAYER_DIRECTION::LEFT:
			GetAnimator()->Play(L"IDLE_LEFT", false);
			break;
		case PLAYER_DIRECTION::RIGHT:
			GetAnimator()->Play(L"IDLE_RIGHT", false);
			break;
		default:
			GetAnimator()->Play(L"IDLE_RIGHT", false);
			break;
		}
		break;
	case PLAYER_STATE::DEAD:
		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == _pOther->GetObj()->GetName())
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}
