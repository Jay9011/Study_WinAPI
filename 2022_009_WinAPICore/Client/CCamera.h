#pragma once
class CCamera
{
	SINGLE(CCamera)
private:
	Vec2     m_vLookAt;		// ī�޶� ���� ��ġ
	Vec2     m_vPrevLookAt;	// ī�޶� ���� ���� ������ ��ġ
	Vec2     m_vCurLookAt;	// ���� ��ġ�� ���� ��ġ ���� ��ġ
	Vec2     m_vDiff;		// �ػ� �߽���ġ�� ī�޶� LookAt ���� ���� ��
	
	CObject* m_pTargetObj;	// ī�޶��� Ÿ�� ������Ʈ
	float    m_fTime;		// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float    m_fSpeed;		// Ÿ���� ���󰡴� �ӵ�
	float    m_fAccTime;	// ���� �ð�

public:
	void update();

	Vec2 GetLookAt()                  { return m_vCurLookAt; }
	void SetLookAt(Vec2 _vLook)       
	{ 
		m_vLookAt  = _vLook; 
		m_fSpeed   = (m_vLookAt - m_vPrevLookAt).Length() / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos)  { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	
private:
	void CalDiff();

};

