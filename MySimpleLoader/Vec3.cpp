#include <iostream>
#include <math.h> 
#include "Vec3.h"

Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}
Vec3::Vec3(float _x, float _y, float _z)	//Normal Constructor
{
	x = _x;
	y = _y;
	z = _z;
}

Vec3::Vec3(const Vec3& _vecB)		//Copy Constructor
{
	x = _vecB.x;
	y = _vecB.y;
	z = _vecB.z;
}

float Vec3::getX() const	//Getter for non-member function
{
	return x;
}

float Vec3::getY() const	//Getter for non-member function
{
	return y;
}

float Vec3::getZ() const	//Getter for non-member function
{
	return z;
}

Vec3 Vec3::operator+(const Vec3& _vecB)		//Overloaded Add Operator
{
	Vec3 vecC(this->x + _vecB.x, this->y + _vecB.y, this->z + _vecB.z);
	return vecC;
}

Vec3 Vec3::operator-(const Vec3& _vecB)		//Overloaded Sub Operator
{
	Vec3 vecC(this->x - _vecB.x, this->y - _vecB.y, this->z - _vecB.z);
	return vecC;
}

Vec3 Vec3::operator*(const float _scalar)		//Overloaded Scalar Mult Operator
{
	Vec3 vecC(this->x * _scalar, this->y * _scalar, this->z * _scalar);
	return vecC;
}

Vec3 Vec3::operator/(const float _scalar)		//Overloaded Scalar Div Operator
{
	Vec3 vecC(this->x / _scalar, this->y / _scalar, this->z / _scalar);
	return vecC;
}

Vec3 operator*(const int _scalar, const Vec3& _vec)		//Free Function (non-member) to allow scalarLHS*vectorRHS
{
	Vec3 vecC(_vec.getX() * _scalar, _vec.getY() * _scalar, _vec.getZ() * _scalar);
	return vecC;
}

Vec3 Vec3::normalize()
{
	Vec3 normalized(0, 0, 0);
	normalized = *this/this->getLength();
	return normalized; 
}



Vec3 Vec3::crossProduct(const Vec3& _vecB)
{
	float i;
	float j;
	float k; 
	i = (this->y * _vecB.z) - (this->z * _vecB.y);
	j = (this->z * _vecB.x) - (this->x * _vecB.z);
	k = (this->x * _vecB.y) - (this->y * _vecB.x);
	Vec3 vecC(i, j, k);
	return vecC;

}

float Vec3::getLength() const		//Get Length
{
	return sqrt((x*x) + (y*y) + (z*z));	
}

float Vec3::dotProduct(const Vec3& _vecB) const		//Get Dot Product
{
	return ((this->x * _vecB.x) + (this->y * _vecB.y) + (this->z * _vecB.z));
}



void Vec3::display()
{
	std::cout << x << " " << y << " " << z << std::endl;
}


