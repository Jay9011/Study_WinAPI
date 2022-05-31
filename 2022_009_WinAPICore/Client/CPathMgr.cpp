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
	GetCurrentDirectory(255, m_szContentPath);		// ���� ����
	int iLen = (int)wcslen(m_szContentPath);	// ���ڿ� ����
	/*
	* ���� ������ �̵�
	*/
	for (int i = iLen - 1; 0 <= i; --i)	// �� �ڿ������� Ž��
	{
		if ('\\' == m_szContentPath[i])	// ��θ� ��Ÿ���� ���ڸ� ã�Ҵٸ�
		{
			m_szContentPath[i] = '\0';	// NULL���ڷ� �ٲپ� ���ڿ��� ���̶�� �˷���.
			break;						// ���� ��� ���ڸ� ���� �ʿ� ���� �ϳ��� �ٲ��ִ� ������ ���� ������ �̵���ų �� �ִ�.
		}
	}
	
	/*
	* + bin\\content\\ ���� ���ҽ� ã��
	*/
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\\0");	// Ȥ�ö� �ڿ� ���ڿ��� �������� �� �����Ƿ� NULL���ڷ� ��������ش�.

	//SetWindowText(Core::GetInst()->GetMainHWnd(), m_szContentPath);	// Window Ÿ��Ʋ�ٿ� ���� Current ��� ���̱�
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();
	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);

	return strRelativePath;
}
