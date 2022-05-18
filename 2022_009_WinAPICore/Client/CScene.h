#pragma once

// ���漱��
class CObject;

class CScene
{
public:
	CScene();
	virtual ~CScene();

private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;	// Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Enter() = 0;	// �ش� Scene �� ���� �� ȣ��
	virtual void Exit()  = 0;	// �ش� Scene �� Ż�� �� ȣ��

	void update();
	void finalupdate();
	void render(HDC _dc);

	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
};

