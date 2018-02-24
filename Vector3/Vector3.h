#pragma once
#include <iostream>
#include <cmath>

class Vector3
{
public:
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const Vector3& other);
	~Vector3();

	const Vector3& operator=(const Vector3& other);
	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other) const;
	Vector3& operator-=(const Vector3& other);
	Vector3 operator-() const;
	Vector3 operator*(double k) const;
	friend Vector3 operator*(double k, const Vector3& v);

	double operator*(const Vector3& other) const;	//scalar
	Vector3 operator^(const Vector3& other) const;	//vector

	double squareLen() const;
	double len() const;
	Vector3& norm();
	Vector3& rotate(double angle, const Vector3& axis);	//(angle is received in radians) rotates itself
	Vector3 getRotated(double angle, const Vector3& axis) const;	//(angle is received in radians) returns rotated Vector3
	double angle(const Vector3& other) const;	//return angle (in radians) between the vectors, if one of vectors is 0, 0 is returned
	friend std::ostream& operator<<(std::ostream& stream, const Vector3& v);	//output format: (x y z)
	friend std::istream& operator>>(std::istream& stream, Vector3& v);


private:
	double x_;
	double y_;
	double z_;
};


