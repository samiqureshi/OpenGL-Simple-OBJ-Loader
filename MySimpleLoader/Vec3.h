#ifndef VEC3_H
#define VEC3_H
//#include "Vec4.h"

class Vec3
{
public:
	Vec3();		//Default Constructor
	Vec3(float _x, float _y, float _z);	//Normal Constructor
	Vec3(const Vec3& _vecB);		//Copy Constructor
	Vec3 operator+(const Vec3& _vecB);	//Overloaded Add Operator
	Vec3 operator-(const Vec3& _vecB);	//Overloaded Sub Operator
	Vec3 operator*(const float _scalar);	//Overloaded Scalar Mult Operator
	Vec3 operator/(const float _scalar);	//Overloaded Scalar Div Operator
	Vec3 normalize();		//Return the normalized vector
	Vec3 crossProduct(const Vec3& _vecB);	//Return the cross product vector
	float getX() const;
	float getY() const;
	float getZ() const;
	float getLength() const;
	float dotProduct(const Vec3& _vecB) const;
	void display();

private:
	float x;
	float y;
	float z;
};

#endif