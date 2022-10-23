#pragma once


struct Vec2
{
public:
	float x;
	float y;

public:
	bool IsZero()
	{
		if (0.f == x && 0.f == y)
			return true;
		return false;
	}

	float Length()
	{
		return (float)sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float length = Length();

		assert(length != 0.f);
		x /= length;
		y /= length;

		return *this;
	}

	Vec2& Vec2_abs()
	{
		x = abs(x);
		y = abs(y);
		return *this;
	}

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

	Vec2 operator + (float _f)
	{
		return (Vec2(x + _f, y + _f));
	}

	Vec2 operator - (float _f)
	{
		return (Vec2(x - _f, y - _f));
	}

	Vec2 operator * (float _f)
	{
		return (Vec2(x * _f, y * _f));
	}

	Vec2 operator / (float _f)
	{
		assert(!(0.f == x || 0.f == y) || !(0.f == _f));
		return (Vec2(x / _f, y / _f));
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


// 전역 함수
Vec2 Vec2_abs(const Vec2& _origin)
{
	return Vec2(abs(_origin.x), abs(_origin.y));
}