#pragma once

class CRes
{
public:
	CRes();
	virtual ~CRes();

	const wstring& GetKey() const { return m_strKey; }
	const wstring& GetRelativePath() const { return m_strRelativePath; }

	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

private:
	wstring m_strKey;			// 리소스 키
	wstring m_strRelativePath;	// 리소스 상대경로

};

