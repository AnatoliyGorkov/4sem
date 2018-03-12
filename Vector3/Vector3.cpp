#include "Vector3.h"
#include <limits>
#include <algorithm>
#include <cmath>

Vector3::Vector3() :
	x(0),
	y(0),
	z(0)
{}

Vector3::Vector3(double x, double y, double z) :
	x(x),
	y(y),
	z(z)

{}

Vector3 Vector3::operator+(const Vector3 & other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 & Vector3::operator+=(const Vector3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}


Vector3 Vector3::operator-(const Vector3 & other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 & Vector3::operator-=(const Vector3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3& Vector3::invert()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(double k) const
{
	return Vector3(k * x, k * y, k * z);
}

double Vector3::operator*(const Vector3 & other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::operator^(const Vector3 & other) const
{
	return Vector3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

double Vector3::squareLen() const
{
	return (*this) * (*this);
}

double Vector3::len() const
{
	return std::sqrt(squareLen());
}

Vector3 & Vector3::norm()
{
	double len = (*this).len();
	if (almostEqual(len, 0.0))
		return (*this);
	x /= len;
	y /= len;
	z /= len;
	return (*this);
}

Vector3 & Vector3::rotate(double angle, const Vector3 & axis)
{
	if (almostEqual(axis.len(), 0.0))
		return *this;
	Vector3 axisNorm = axis;
	axisNorm.norm();
	double cosA = std::cos(angle);
	double sinA = std::sin(angle);
	/*
	double x_, y_, z_;

	x_ = (cosA + (1 - cosA) * axisNorm.x * axisNorm.x) * x +
		((1 - cosA) * axisNorm.x * axisNorm.y - sinA * axisNorm.z) * y +
		((1 - cosA) * axisNorm.x * axisNorm.z + sinA * axisNorm.y) * z;

	y_ = ((1 - cosA) * axisNorm.y * axisNorm.x + sinA * axisNorm.z) * x +
		(cosA + (1 - cosA) * axisNorm.y * axisNorm.y) * y +
		((1 - cosA) * axisNorm.y * axisNorm.z - sinA * axisNorm.x) * z;

	z_ = ((1 - cosA) * axisNorm.z * axisNorm.x - sinA * axisNorm.y) * x +
		((1 - cosA) * axisNorm.z * axisNorm.y + sinA * axisNorm.x) * y +
		(cosA + (1 - cosA) * axisNorm.z * axisNorm.z) * z;

	x = x_;
	y = y_;
	z = z_;
	*/

	Vector3 self = *this;
	Vector3 a = self - axisNorm * (axisNorm * self);
	Vector3 b = a ^ axisNorm;
	Vector3 delta = a * cosA + b * sinA - a;
	self += delta;
	*this = self;

	return *this;
}

Vector3 Vector3::getRotated(double angle, const Vector3 & axis) const
{
	Vector3 tmp = *this;
	tmp.rotate(angle, axis);
	return tmp;
}

double Vector3::angle(const Vector3 & other) const
{
	double len1 = (*this).len();
	double len2 = other.len();
	if (almostEqual(len1, 0.0) || almostEqual(len2, 0.0))	//same question as in rotate()
		return 0;
	return std::acos((*this) * other / len1 / len2);
}

Vector3 operator*(double k, const Vector3 & v)
{
	return Vector3(v * k);
}

std::ostream & operator<<(std::ostream & stream, const Vector3 & v)
{
	stream << "(" << v.x << " " << v.y << " " << v.z << ")";
	return stream;
}

std::istream & operator>>(std::istream & stream, Vector3 & v)
{
	stream >> v.x >> v.y >> v.z;
	return stream;
}

bool almostEqual(double lhs, double rhs)
{
	return std::abs(lhs - rhs) <= std::numeric_limits<double>::epsilon() * std::max(std::abs(lhs), std::abs(rhs));
}
