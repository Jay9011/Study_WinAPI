#pragma once

class CTexture;

class Core
{
	SINGLE(Core);
private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution;	// 메인 윈도우 해상도
	HDC		m_hdc;			// 메인 윈도우에 Draw 할 DC

	CTexture* m_pMemTex;

	// 자주 사용하는 GDI Object
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

