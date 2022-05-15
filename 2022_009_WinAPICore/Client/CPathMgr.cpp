#include "pch.h"
#include "CPathMgr.h"

#include "Core.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{

}

CPathMgr::~CPathMgr() = default;

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);		// 현재 폴더
	int iLen = (int)wcslen(m_szContentPath);	// 문자열 길이
	/*
	* 상위 폴더로 이동
	*/
	for (int i = iLen - 1; 0 <= i; --i)	// 맨 뒤에서부터 탐색
	{
		if ('\\' == m_szContentPath[i])	// 경로를 나타내는 문자를 찾았다면
		{
			m_szContentPath[i] = '\0';	// NULL문자로 바꾸어 문자열의 끝이라고 알려줌.
			break;						// 뒤의 모든 문자를 지울 필요 없이 하나만 바꿔주는 것으로 상위 폴더로 이동시킬 수 있다.
		}
	}
	
	/*
	* + bin\\content\\ 에서 리소스 찾기
	*/
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\\0");	// 혹시라도 뒤에 문자열이 남아있을 수 있으므로 NULL문자로 종료시켜준다.





	//SetWindowText(Core::GetInst()->GetMainHWnd(), m_szContentPath);	// Window 타이틀바에 현재 Current 경로 보이기
}
