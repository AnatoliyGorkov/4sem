#include "Vector3.h"

Vector3::Vector3():
	x_(0),
	y_(0),
	z_(0)
{}

Vector3::Vector3(double x, double y, double z):
	x_(x),
	y_(y),
	z_(z)

{}

Vector3::Vector3(const Vector3 & other):
	x_(other.x_),
	y_(other.y_),
	z_(other.z_)
{}

Vector3::~Vector3()
{}

const Vector3 & Vector3::operator=(const Vector3 & other)
{
	x_ = other.x_;
	y_ = other.y_;
	z_ = other.z_;
	return *this;
}

Vector3 Vector3::operator+(const Vector3 & other) const
{
	return Vector3(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector3 & Vector3::operator+=(const Vector3 & other)
{
	x_ += other.x_;
	y_ += other.y_;
	z_ += other.z_;
	return *this;
}

Vector3 Vector3::operator-(const Vector3 & other) const
{
	return Vector3(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vector3 & Vector3::operator-=(const Vector3 & other)
{
	x_ -= other.x_;
	y_ -= other.y_;
	z_ -= other.z_;
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x_, -y_, -z_);
}

Vector3 Vector3::operator*(double k) const
{
	return Vector3(k * x_, k * y_, k * z_);
}

double Vector3::operator*(const Vector3 & other) const
{
	return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

Vector3 Vector3::operator^(const Vector3 & other) const
{
	return Vector3(y_ * other.z_ - z_ * other.y_,
					z_ * other.x_ - x_ * other.z_,
					x_ * other.y_ - y_ * other.x_);
}

double Vector3::squareLen() const
{
	return (*this) * (*this);
}

double Vector3::len() const
{
	return std::sqrt((*this).squareLen());
}

Vector3 & Vector3::norm()
{
	double len = (*this).len();
	if (len == 0)
		return (*this);
	x_ /= len;
	y_ /= len;
	z_ /= len;
	return (*this);
}

Vector3 & Vector3::rotate(double angle, const Vector3 & axis)
{
	if (axis.len() == 0)	//How we can choose eps value to compare with (shouldn't compare double with 0)?
		return *this;
	double x, y, z;
	double cosA = std::cos(angle);
	double sinA = std::sin(angle);
	x = (cosA + (1 - cosA) * axis.x_ * axis.x_) * x_ +
		((1 - cosA) * axis.x_ * axis.y_ - sinA * axis.z_) * y_ +
		((1 - cosA) * axis.x_ * axis.z_ + sinA * axis.y_) * z_;

	y = ((1 - cosA) * axis.y_ * axis.x_ + sinA * axis.z_) * x_ +
		(cosA + (1 - cosA) * axis.y_ * axis.y_) * y_ +
		((1 - cosA) * axis.y_ * axis.z_ - sinA * axis.x_) * z_;

	z = ((1 - cosA) * axis.z_ * axis.x_ - sinA * axis.y_) * x_ +
		((1 - cosA) * axis.z_ * axis.y_ + sinA * axis.x_) * y_ +
		(cosA + (1 - cosA) * axis.z_ * axis.z_) * z_;
	x_ = x;
	y_ = y;
	z_ = z;
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
	if (len1 == 0 || len2 == 0)	//same question as in rotate()
		return 0;
	return std::acos((*this) * other / len1 / len2);
}

Vector3 operator*(double k, const Vector3 & v)
{
	return Vector3(v * k);
}

std::ostream & operator<<(std::ostream & stream, const Vector3 & v)
{
	stream << "(" << v.x_ << " " << v.y_ << " " << v.z_ << ")";
	return stream;
}

std::istream & operator>>(std::istream & stream, Vector3 & v)
{
	stream >> v.x_ >> v.y_ >> v.z_;
	return stream;
}