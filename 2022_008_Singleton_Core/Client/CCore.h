#pragma once
class CCore
{
public:
	static CCore* GetInst()
	{
		// 정적 멤버의 초기화는 "단 한 번"만 초기화 된다.
		static CCore core;

		return &core;
	}

private:
	CCore();
	~CCore();
};

