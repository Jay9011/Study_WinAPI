#pragma once
class CCore
{
public:
	static CCore* GetInst()
	{
		// ���� ����� �ʱ�ȭ�� "�� �� ��"�� �ʱ�ȭ �ȴ�.
		static CCore core;

		return &core;
	}

private:
	CCore();
	~CCore();
};

