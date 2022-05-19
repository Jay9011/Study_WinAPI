#pragma once

class Core
{
	SINGLE(Core);
private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�
	HDC		m_hdc;			// ���� �����쿡 Draw �� DC

	HBITMAP	m_hBit;
	HDC		m_memDC;

	// ���� ����ϴ� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

	HWND  GetMainHWnd()		const { return m_hWnd; }
	HDC	  GetMainDC()		const { return m_hdc; }
	POINT GetResolution()	const { return m_ptResolution; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) const { return m_arrBrush[(UINT)_eType]; }
	HPEN   GetPen  (PEN_TYPE _eType)   const { return m_arrPen[(UINT)_eType]; }

private:
	void CreateBrushPen();
};

