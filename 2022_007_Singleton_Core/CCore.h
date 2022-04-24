#pragma once

/*
*	싱글톤 패턴
*		: 객체의 생성을 1개로 제한
*	어디서든 쉽게 접근 가능해야 한다.
*/
class CCore
{
private:
	// 지역
	// 전역
	// 정적 ( 데이터 영역 )
	//	1. 함수 안에
	//	2. 파일
	//	3. 클래스 안에 -> 클래스 내부에서만 접근 가능, 클래스 메모리에 포함되지 않는다 ( 데이터 영역에 존재한다 )
	// 외부
	static CCore* g_pInst; // 정적 멤버 ( 데이터 영역 )
	
public:
	// 정적 멤버함수, 인스턴스 없이 호출 가능. this가 없다.(일반 멤버 접근이 불가능하다.), 정적 멤버는 접근 가능
	static CCore* GetInstance()
	{
		// 최초 호출 된 경우 새로운 인스턴스를 만들어서 주소를 반환해준다.
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}

		// 2번 이상 호출 된 경우, 이미 만들어진 인스턴스 주소를 반환해준다.
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

