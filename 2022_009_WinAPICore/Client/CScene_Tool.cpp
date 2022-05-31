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
		LoadTile(L"tile\\Test.tile");
	}
}

void CScene_Tool::Enter()
{
	// 타일 생성
	CreateTile(5, 5);

	// UI 하나 만들어보기
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

	// Camera Look 지정
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

	ofn.lStructSize = sizeof(OPENFILENAME);			// 구조체 크기
	ofn.hwndOwner = Core::GetInst()->GetMainHWnd();	// 최상위 부모 윈도우 핸들

	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";	// 사용 가능한 필터 리스트
	ofn.nFilterIndex = 0;							// 처음 자동 지정되는 필터 Index

	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.nMaxFile = sizeof(szName);					// 저장 가능한 최종 경로 최대 길이 크기
	ofn.lpstrFile = szName;							// 최종 경로가 들어있는 포인터 주소

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();	// 파일 저장하는 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn))	// 파일 저장 창 열기
	{
		// 저장 버튼으로 반환된 경우
		SaveTile(szName);
	}
	else
	{
		// 취소 버튼으로 반환된 경우
	}

}

void CScene_Tool::SaveTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 커널 오브젝트
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	
	// 파일 열기 실패
	assert(pFile);

	// 데이터 저장
	// 타일 가로세로 갯수 저장	
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일들의 데이터를 개별적으로 저장
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
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

			// Tool Scene 확인
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