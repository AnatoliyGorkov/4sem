#include "Vector2.h"
#include <limits>
#include <algorithm>
#include <cmath>

Vector2::Vector2() :
	x(0),
	y(0)
{}

Vector2::Vector2(float x, float y) :
	x(x),
	y(y)
{}

Vector2 Vector2::operator+(const Vector2 & other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 & Vector2::operator+=(const Vector2 & other)
{
	x += other.x;
	y += other.y;
	return *this;
}


Vector2 Vector2::operator-(const Vector2 & other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 & Vector2::operator-=(const Vector2 & other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::invert()
{
	x = -x;
	y = -y;
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(float k) const
{
	return Vector2(k * x, k * y);
}

float Vector2::operator*(const Vector2 & other) const
{
	return x * other.x + y * other.y;
}

float Vector2::operator^(const Vector2 & other) const
{
	return x * other.y - y * other.x;
}

float Vector2::squareLen() const
{
	return (*this) * (*this);
}

float Vector2::len() const
{
	return std::sqrt(squareLen());
}

Vector2 & Vector2::norm()
{
	float len = (*this).len();
	if (almostEqual(len, 0.0))
		return (*this);
	x /= len;
	y /= len;
	return (*this);
}

Vector2 & Vector2::rotate(float angle)
{
	float cosA = std::cos(angle);
	float sinA = std::sin(angle);
	float x_, y_;
	x_ = x * cosA - y * sinA;
	y_ = x * sinA + y * cosA;
	x = x_;
	y = y_;
	return *this;
}

Vector2 Vector2::getRotated(float angle) const
{
	Vector2 tmp = *this;
	tmp.rotate(angle);
	return tmp;
}

float Vector2::angle(const Vector2 & other) const
{
	float len1 = (*this).len();
	float len2 = other.len();
	if (almostEqual(len1, 0.0) || almostEqual(len2, 0.0))	//same question as in rotate()
		return 0;
	return std::acos((*this) * other / len1 / len2);
}

Vector2 operator*(float k, const Vector2 & v)
{
	return Vector2(v * k);
}

std::ostream & operator<<(std::ostream & stream, const Vector2 & v)
{
	stream << "(" << v.x << " " << v.y << ")";
	return stream;
}

std::istream & operator>>(std::istream & stream, Vector2 & v)
{
	stream >> v.x >> v.y;
	return stream;
}

bool almostEqual(float lhs, float rhs)
{
	return std::abs(lhs - rhs) <= std::numeric_limits<float>::epsilon() * std::max(std::abs(lhs), std::abs(rhs));
}