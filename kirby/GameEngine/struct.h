#pragma once


struct Vec2
{
public:
	float x;
	float y;

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

public:
	Vec2& operator = (Vec2 _v)
	{
		x = _v.x;
		y = _v.y;
		return *this;
	}

	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
		return *this;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return (Vec2(x + _vOther.x, y + _vOther.y));
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return (Vec2(x - _vOther.x, y - _vOther.y));
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return (Vec2(x * _vOther.x, y * _vOther.y));
	}

	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y) || !(0.f == x || 0.f == y));
		return (Vec2(x / _vOther.x, y / _vOther.y));
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	void operator *= (Vec2 _vOther)
	{
		x *= _vOther.x;
		y *= _vOther.y;
	}

	void operator /= (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y) || !(0.f == x || 0.f == y));
		x /= _vOther.x;
		y /= _vOther.y;
	}
};