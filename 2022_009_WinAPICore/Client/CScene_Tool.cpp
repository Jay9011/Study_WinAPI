#include "pch.h"
#include "CScene_Tool.h"
#include "resource.h"

#include "Core.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

#include "CTile.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "CUIMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool() = default;

CScene_Tool::~CScene_Tool() = default;

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	if (KEY_TAP(KEY::LSHIFT))
	{
		//CUIMgr::GetInst()->SetFocusedUI(m_pUI);
		SaveTileData();
	}

	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}
}

void CScene_Tool::Enter()
{
	// Ÿ�� ����
	CreateTile(5, 5);

	// UI �ϳ� ������
	Vec2 vResolution = Core::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	//pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);

	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	CUI* pClonePanelUI = pPanelUI->Clone();
	pClonePanelUI->SetPos(pClonePanelUI->GetPos() + Vec2(-300.f, 0.f));
	((CBtnUI*)pClonePanelUI->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);

	AddObject(pClonePanelUI, GROUP_TYPE::UI);

	m_pUI = pClonePanelUI;

	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution * .5f);
}

void CScene_Tool::Exit()
{
	DeleteAll();
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = GetTileX();
		int iTileY = GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (   vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
			return;


		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
}

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);			// ����ü ũ��
	ofn.hwndOwner = Core::GetInst()->GetMainHWnd();	// �ֻ��� �θ� ������ �ڵ�

	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";	// ��� ������ ���� ����Ʈ
	ofn.nFilterIndex = 0;							// ó�� �ڵ� �����Ǵ� ���� Index

	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.nMaxFile = sizeof(szName);					// ���� ������ ���� ��� �ִ� ���� ũ��
	ofn.lpstrFile = szName;							// ���� ��ΰ� ����ִ� ������ �ּ�

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();	// ���� �����ϴ� �ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn))	// ���� ���� â ����
	{
		// ���� ��ư���� ��ȯ�� ���
		SaveTile(szName);
	}
	else
	{
		// ��� ��ư���� ��ȯ�� ���
	}

}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// Ŀ�� ������Ʈ
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	
	// ���� ���� ����
	assert(pFile);

	// ������ ����
	// Ÿ�� ���μ��� ���� ����	
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// ��� Ÿ�ϵ��� �����͸� ���������� ����
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);			// ����ü ũ��
	ofn.hwndOwner = Core::GetInst()->GetMainHWnd();	// �ֻ��� �θ� ������ �ڵ�

	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";	// ��� ������ ���� ����Ʈ
	ofn.nFilterIndex = 0;							// ó�� �ڵ� �����Ǵ� ���� Index

	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.nMaxFile = sizeof(szName);					// ���� ������ ���� ��� �ִ� ���� ũ��
	ofn.lpstrFile = szName;							// ���� ��ΰ� ����ִ� ������ �ּ�

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();	// ���� �����ϴ� �ʱ� ���
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}


// === === === === === === ===
//   Tile Count Window Proc
// === === === === === === ===
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// Tool Scene Ȯ��
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			//
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}