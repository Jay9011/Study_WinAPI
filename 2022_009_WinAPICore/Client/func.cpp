#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)_pAI;
	evn.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(evn);
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	// Animation 의 이름을 저장한다. (데이터 직렬화)
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	// 문자열 길이 저장
	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	// 문자 저장 (문자 길이만큼 저장)
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	// 문자열 길이 불러오기
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);
	// 문자 불러오기 (문자열 길이만큼 로드)
	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}
