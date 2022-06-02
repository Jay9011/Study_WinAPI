#pragma once

// ���漱��
class CObject;

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;	// Scene �̸�

	UINT m_iTileX;	// Ÿ�� ���� ����
	UINT m_iTileY;	// Ÿ�� ���� ����

	CObject* m_pPlayer;	// Player

public:
	virtual void Enter() = 0;	// �ش� Scene �� ���� �� ȣ��
	virtual void Exit()  = 0;	// �ش� Scene �� Ż�� �� ȣ��

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);


/*
	Object Control
*/
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	void RegisterPlayer(CObject* _pPlayer)            { m_pPlayer = _pPlayer; }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) const { return m_arrObj[(UINT)_eType]; }
		  vector<CObject*>& GetUIGroup()							{ return m_arrObj[(UINT)GROUP_TYPE::UI]; }

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);
	void render_tile(HDC _dc);

/*
	Get & Set
*/
	void  SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() const { return m_iTileX; }
	UINT GetTileY() const { return m_iTileY; }

	CObject* GetPlayer() const { return m_pPlayer; }

public:
	CScene();
	virtual ~CScene();

};

