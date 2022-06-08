#pragma once

typedef struct _tagResolution
{
	UINT iW;
	UINT iH;
} RESOULUTION, *PRESOLUTION;

using POSITION = struct _tagPosition
{
	float x;
	float y;
	
	_tagPosition():x(0.0f),y(0.0f){}
	_tagPosition(float _x,float _y):x(_x),y(_y){}
	_tagPosition(const POINT& _pt):x((float)_pt.x),y((float)_pt.y){}
	void operator=(const _tagPosition& _pos)
	{
		x = _pos.x;
		y = _pos.y;
	}
	void operator=(const POINT& pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}
	void operator=(const float f[2])
	{
		x = f[0];
		y = f[1];
	}
	
	//========== + ==========
	_tagPosition operator+(const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator+(const POINT& pos)
	{
		_tagPosition tPos;
		tPos.x = x + (float)pos.x;
		tPos.y = y + (float)pos.y;
		return tPos;
	}

	_tagPosition operator+(const float f[2])
	{
		_tagPosition tPos;
		tPos.x = x + f[0];
		tPos.y = y + f[1];
		return tPos;
	}
	
	_tagPosition operator+(const float f)
	{
		_tagPosition tPos;
		tPos.x = x + f;
		tPos.y = y + f;
		return tPos;
	}

	//========== - ==========
	_tagPosition operator-(const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}

	_tagPosition operator-(const POINT& pos)
	{
		_tagPosition tPos;
		tPos.x = x - (float)pos.x;
		tPos.y = y - (float)pos.y;
		return tPos;
	}

	_tagPosition operator-(const float f[2])
	{
		_tagPosition tPos;
		tPos.x = x - f[0];
		tPos.y = y - f[1];
		return tPos;
	}

	_tagPosition operator-(const float f)
	{
		_tagPosition tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}

	//========== * ==========
	_tagPosition operator*(const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator*(const POINT& pos)
	{
		_tagPosition tPos;
		tPos.x = x * (float)pos.x;
		tPos.y = y * (float)pos.y;
		return tPos;
	}

	_tagPosition operator*(const float f[2])
	{
		_tagPosition tPos;
		tPos.x = x * f[0];
		tPos.y = y * f[1];
		return tPos;
	}

	_tagPosition operator*(const float f)
	{
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;
		return tPos;
	}
	
	//========== / ==========
	_tagPosition operator/(const _tagPosition& pos)
	{
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator/(const POINT& pos)
	{
		_tagPosition tPos;
		tPos.x = x / (float)pos.x;
		tPos.y = y / (float)pos.y;
		return tPos;
	}

	_tagPosition operator/(const float f[2])
	{
		_tagPosition tPos;
		tPos.x = x / f[0];
		tPos.y = y / f[1];
		return tPos;
	}

	_tagPosition operator/(const float f)
	{
		_tagPosition tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}
};
using PPOSITION = POSITION *;
using _SIZE = POSITION;
using _PSIZE = POSITION *;