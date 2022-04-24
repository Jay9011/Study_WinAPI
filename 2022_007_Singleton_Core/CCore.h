#pragma once

/*
*	�̱��� ����
*		: ��ü�� ������ 1���� ����
*	��𼭵� ���� ���� �����ؾ� �Ѵ�.
*/
class CCore
{
private:
	// ����
	// ����
	// ���� ( ������ ���� )
	//	1. �Լ� �ȿ�
	//	2. ����
	//	3. Ŭ���� �ȿ� -> Ŭ���� ���ο����� ���� ����, Ŭ���� �޸𸮿� ���Ե��� �ʴ´� ( ������ ������ �����Ѵ� )
	// �ܺ�
	static CCore* g_pInst; // ���� ��� ( ������ ���� )
	
public:
	// ���� ����Լ�, �ν��Ͻ� ���� ȣ�� ����. this�� ����.(�Ϲ� ��� ������ �Ұ����ϴ�.), ���� ����� ���� ����
	static CCore* GetInstance()
	{
		// ���� ȣ�� �� ��� ���ο� �ν��Ͻ��� ���� �ּҸ� ��ȯ���ش�.
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}

		// 2�� �̻� ȣ�� �� ���, �̹� ������� �ν��Ͻ� �ּҸ� ��ȯ���ش�.
		return g_pInst;
	}

	static void Release()
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}

private:
	CCore();
	~CCore();
};

