#pragma once
#include <iostream>
#include <cmath>

class Vector3
{
public:
	Vector3();
	Vector3(double x, double y, double z);
	
	/*
	fixit:
        Компилятор сам сгенерирует за вас ровно такой же конструктор копирования и деструктор.
        Их явно писать не нужно.
        
        Если вам нужно выделать память в куче, например, то конструктор копирования и деструктор необходимо
        написать самостоятельно.
	*/
	Vector3(const Vector3& other);
	~Vector3();

	/*
	fixit: оператор присваивания, если нужно просто спорировать поля класса также с помощью оператора =,
	компилятор и сам сгенерирует. лучше убрать самописный.
	*/
	const Vector3& operator=(const Vector3& other);
	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other) const;
	Vector3& operator-=(const Vector3& other);
	/*
	для полноты можно дописать неконстантный метод invert ... в пару к унарному минусу
	*/
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
    /*
    fixit: вы не предоствили способа обратиться к компонентам вектора снаружи класса.
    нужно либо делать методы вроде 
    float x() const
    {
        return x;
    }
    float& x()
    {
        return x;
    }
    либо просто сделать поля публичными.
    Второй вариант проще.
    Первый, например, удобен, если вы хотите посчитать статистику обращения к компонентам класса.
    Либо если у вас во внутреннем представлении все в метрах, а наружу вы хотите отдавать либо миллиметры, либо
    дюймы и т.п.
    Но это достаточно редкие сценарии.
    */
	double x_;
	double y_;
	double z_;
};


