#pragma once
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
/*
лучше писать ровно те инклюды, которые нужны в текущем файле.
например, limits вам в данном файле не нужно
*/

class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3();
	Vector3(double x, double y, double z);

	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other) const;
	Vector3& operator-=(const Vector3& other);
	Vector3& invert();
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
};

bool almostEqual(double lhs, double rhs);	//used for comparison of doubles

/*
fixit: вы сделали поля структуры x,y,z публичными и смысла объявлять кого-то друзьями уже нет.
можно просто вынести вынести их объявление вне структуры (рядом с almostEqual)
*/
