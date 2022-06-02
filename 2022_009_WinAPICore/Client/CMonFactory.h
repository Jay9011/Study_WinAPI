#pragma once
class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
	END,
};

class CMonFactory
{
public:
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);

private:
	CMonFactory() = default;
	~CMonFactory() = default;
};

