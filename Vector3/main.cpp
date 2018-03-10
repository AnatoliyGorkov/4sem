#include "Vector3.h"
const double pi = 3.141592653589793238462643383279502884;

int main()
{

	Vector3 a;
	std::cout << a << std::endl;
	std::cout << "Input new vector a" << std::endl;
	std::cin >> a;
	std::cout << a << std::endl;
	std::cout << "Input test complete" << std::endl;

	Vector3 b(1, 0, 0);
	std::cout << b << std::endl;
	std::cout << "Input new vector b" << std::endl;
	std::cin >> b;

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "a - b = " << a - b << std::endl;
	std::cout << "3 * a = " << 3 * a << std::endl;
	std::cout << "a * 2 = " << a * 2 << std::endl;
	std::cout << "-a = " << -a << std::endl << std::endl;

	Vector3 c = a;
	std::cout << "(c = a) = " << c << std::endl;
	c += b;
	std::cout << "(c += b) = " << c << std::endl;
	c -= b;
	std::cout << "(c -= b) = " << c << std::endl << std::endl;

	std::cout << "a * b = " << a * b << std::endl;
	std::cout << "a ^ b = " << (a ^ b) << std::endl;

	std::cout << "a.squareLen() = " << a.squareLen() << std::endl;
	std::cout << "a.len() = " << a.len() << std::endl;
	std::cout << "c = " << c << std::endl;
	c.norm();
	std::cout << "c.norm() = " << c << std::endl;
	Vector3 d, axis;
	std::cout << "Input new vector d" << std::endl;
	std::cin >> d;
	std::cout << "Input new vector axis" << std::endl;
	std::cin >> axis;
	d.rotate(pi / 2, axis);
	std::cout << "d (angle = pi/2) = " << d << std::endl;
	std::cout << "d (angle = -pi/2) = " << d.getRotated(-pi/2, axis) << std::endl;
	
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "angle a ^ b = " << a.angle(b) << std::endl << std::endl;
	a = b = c;
	std::cout << "a = b = c" << b << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "angle a ^ b = " << a.angle(b) << std::endl << std::endl;
	std::cout << "a * b = " << a * b << std::endl;
	return 0;
}