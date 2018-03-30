#pragma once
#include <iostream>

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	Vector2 operator+(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2& operator-=(const Vector2& other);
	Vector2& invert();
	Vector2 operator-() const;
	Vector2 operator*(float k) const;


	float operator*(const Vector2& other) const;	//scalar
	float operator^(const Vector2& other) const;	//vector

	float squareLen() const;
	float len() const;
	Vector2& norm();
	Vector2& rotate(float angle);	//(angle is received in radians) rotates itself
	Vector2 getRotated(float angle) const;	//(angle is received in radians) returns rotated Vector2
	float angle(const Vector2& other) const;	//return angle (in radians) between the vectors, if one of vectors is 0, 0 is returned

};

bool almostEqual(float lhs, float rhs);	//used for comparison of floats
Vector2 operator*(float k, const Vector2& v);
std::ostream& operator<<(std::ostream& stream, const Vector2& v);	//output format: (x y z)
std::istream& operator>>(std::istream& stream, Vector2& v);