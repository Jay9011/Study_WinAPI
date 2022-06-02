#pragma once

class CTexture;

class Core
{
	SINGLE(Core);
private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�
	HDC		m_hdc;			// ���� �����쿡 Draw �� DC

	CTexture* m_pMemTex;

	// ���� ����ϴ� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU	m_hMenu;	// Tool Scene ������ ���

public:
	int  init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockingMenu();
	void DividieMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);
	
public:
	HWND  GetMainHWnd()		const { return m_hWnd; }
	HDC	  GetMainDC()		const { return m_hdc; }

	POINT  GetResolution()			   const { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) const { return m_arrBrush[(UINT)_eType]; }
	HPEN   GetPen  (PEN_TYPE _eType)   const { return m_arrPen[(UINT)_eType]; }

};

