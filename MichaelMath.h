#pragma once
#include <iostream>
#include <cmath>

template <class t>
struct Vec2 {
	union {
		struct { t x, y; };
		struct { t u, v; };
		t raw[2];
	};

	Vec2() : x(0), y(0) {}
	Vec2(t _x, t _y) : x(_x), y(_y) {}
	inline Vec2<t> operator +(const Vec2<t>& b) const { return Vec2<t>(x + b.x, y + b.y); }
	inline Vec2<t> operator -(const Vec2<t>& b) const { return Vec2<t>(x - b.x, y - b.y); }
	inline Vec2<t> operator *(float f) const { return Vec2<t>(x * f, y * f); }	

	//Dot Product
	inline t operator *(const Vec2<t>& b) const { return x*b.x + y*b.y; }

	//Stream output
	template <class> friend std::ostream& operator<<(std::ostream& s, Vec2<t>& b);
};

template <class t>
struct Vec3 {
	union {
		struct { t x, y, z; };
		struct { t r, g, b; };
		t raw[3];
	};

	Vec3() : x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}
	inline Vec3<t> operator +(const Vec3<t>& b) const { return Vec3<t>(x + b.x, y + b.y, z + b.z); }
	inline Vec3<t> operator -(const Vec3<t>& b) const { return Vec3<t>(x - b.x, y - b.y, z - b.z); }
	inline Vec3<t> operator *(float f) const { return Vec3<t>(x * f, y * f, z * f); }

	//Dot Product
	inline float operator *(Vec3<t>& b) const { return x * b.x + y * b.y + z * b.z; }

	//Aka Distance
	inline float length() const { return std::sqrt(x * x + y * y + z * z); }

	Vec3<t>& normalize(t l = 1) { *this = (*this) * (l / length()); return *this; }

	Vec3<t> cross(Vec3<t>& b) const{
		t xOut = y * b.z - z * b.y;
		t yOut = z * b.x - x * b.z;
		t zOut = x * b.y - y * b.x;
		return Vec3<t>(xOut, yOut, zOut);
	}

	//Stream output
	template <class> friend std::ostream& operator<<(std::ostream& s, Vec3<t>& b);
};

template <class t>
struct Vec4 {
	union {
		struct { t x, y, z, w; };
		struct { t r, g, b, a; };
		t raw[3];
	};
	Vec4() : x(0), y(0), z(0), w(0) {}
	Vec4(t _x, t _y, t _z, t _w) : x(_x), y(_y), z(_z), w(_w) {}
	inline Vec4<t> operator +(const Vec4<t>& b) const { return Vec4<t>(x + b.x, y + b.y, z + b.z, w + b.w); }
	inline Vec4<t> operator -(const Vec4<t>& b) const { return Vec4<t>(x - b.x, y - b.y, z - b.z, w - b.w); }
	inline Vec4<t> operator *(float f) const { return Vec4<t>(x * f, y * f, z * f, w*f); }

	//Dot Product
	inline t operator *(Vec4<t>& b) const { return  x * b.x + y * b.y + z * b.z + w * b.w; }

	//Aka distance
	inline float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

	//Stream output
	template <class> friend std::ostream& operator<<(std::ostream& s, Vec4<t>& b);
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;


template <class t> std::ostream& operator<<(std::ostream & s, Vec2<t> & b)
{
	s << "(" << b.x << ", " << b.y << ")";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream & s, Vec3<t> & b)
{
	s << "(" << b.x << ", " << b.y << ", " << b.z << ")";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream & s, Vec4<t> & b)
{
	s << "(" << b.x << ", " << b.y << ", " << b.z << ", " << b.w << ")";
	return s;
}

template <class t> struct Mat3 
{
	t raw[9];
	Mat3() { raw[0] = 1; raw[1] = 0; raw[2] = 0; raw[3] = 0; raw[4] = 1; raw[5] = 0; raw[6] = 0; raw[7] = 0; raw[8] = 1; }
	//Mat3(t values[9]) { std::copy(std::begin(raw), std::end(raw), std:begin(values)); }
	inline Vec3<t> operator *(const Vec3<t>& v) const 
	{ 
		t xOut = raw[0] * v.x + raw[1] * v.y + raw[2] * v.z;
		t yOut = raw[3] * v.x + raw[4] * v.y + raw[5] * v.z;
		t zOut = raw[6] * v.x + raw[7] * v.y + raw[8] * v.z;
		return Vec3<t>(xOut, yOut, zOut);
	}
	void SetValues(t values[9])
	{
		for (int i = 0; i < 9; ++i)
		{
			raw[i] = values[i];
		}
	}

	void SetAsRotY(float angleRad)
	{
		raw[0] = std::cos(angleRad); raw[1] = 0; raw[2] = std::sin(angleRad);
		raw[3] = 0; raw[4] = 1; raw[5] = 0;
		raw[6] = -1.0f * std::sin(angleRad); raw[7] = 0; raw[8] = std::cos(angleRad);
	}
};
typedef Mat3<float> Mat3f;