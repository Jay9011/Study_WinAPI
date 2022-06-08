#pragma once
#include "Game.h"

class CCore
{
private:
	static CCore* instance;
	
public:
	static CCore* GetInst()
	{
		if (instance == nullptr)
			instance = new CCore();
		
		return instance;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(instance)
	}
	
private:
	CCore();
	~CCore();

private:
	HINSTANCE   m_hInst;
	HWND        m_hWnd;
	RESOULUTION m_tRS;
	static bool m_bLoop;

public:
	bool Init(HINSTANCE hInst);
	int  Run();
	
private:
	void Logic();
	void Input(float fDeltaTime);
	int  Update(float fDeltaTime);
	int  LateUpdate(float fDeltaTime);

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	ATOM MyRegisterClass();
	BOOL Create();
	
};

