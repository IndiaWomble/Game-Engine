//Vector2D source file

#include "Vector2D.h"

//Vector2D constructor takes x and y values
Vector2D::Vector2D(float parameterX, float parameterY)
{
	x = parameterX;
	y = parameterY;
}

//Returns x value of vector
float Vector2D::GetX()
{
	return x;
}

//Returns y value of vector
float Vector2D::GetY()
{
	return y;
}

//Sets x value of vector
void Vector2D::SetX(float parameterX)
{
	x = parameterX;
}

//Sets y value of vector
void Vector2D::SetY(float parameterY)
{
	y = parameterY;
}

//Returns length of vector
float Vector2D::Length()
{
	return sqrt((x * x) + (y * y));
}

//+ operator overload
Vector2D Vector2D::operator+(const Vector2D& vector2) const
{
	return Vector2D(x + vector2.x, y + vector2.y);
}

//+= operator overload
Vector2D& operator+=(Vector2D& vector1, const Vector2D& vector2)
{
	vector1.x += vector2.x;
	vector1.y += vector2.y;
	return vector1;
}

//* operator overload
Vector2D Vector2D::operator*(float scalar)
{
	return Vector2D(x * scalar, y * scalar);
}

//*= operator overload
Vector2D& Vector2D::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

//- operator overload
Vector2D Vector2D::operator-(const Vector2D& vector2) const
{
	return Vector2D(x - vector2.x, y - vector2.y);
}

//-= operator overload
Vector2D& operator-=(Vector2D& vector1, const Vector2D& vector2)
{
	vector1.x -= vector2.x;
	vector1.y -= vector2.y;
	return vector1;
}

// / operator overload
Vector2D Vector2D::operator/(float scalar)
{
	return Vector2D(x / scalar, y / scalar);
}

// /= operator overload
Vector2D& Vector2D::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

//To normalize the vector, i.e. keeps the direction same as original and reduces length to unit length
void Vector2D::Normalize()
{
	float length = Length();
	if (length > 0)
		(*this) *= 1 / length;
}