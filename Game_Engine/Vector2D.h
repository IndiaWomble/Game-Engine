//Vector2D header file

#pragma once

#ifndef __Vector2D_h__
#define __Vector2D_h__

#include <math.h>

class Vector2D
{
	float x, y;

public:
	Vector2D(float parameterX = 0.0f, float parameterY = 0.0f);
	float GetX();
	float GetY();
	void SetX(float parameterX);
	void SetY(float parameterY);
	float Length();
	Vector2D operator+(const Vector2D& vector2) const;
	friend Vector2D& operator+=(Vector2D& vector1, const Vector2D& vector2);
	Vector2D operator*(float scalar);
	Vector2D& operator*=(float scalar);
	Vector2D operator-(const Vector2D& vector2) const;
	friend Vector2D& operator-=(Vector2D& vector1, const Vector2D& vector2);
	Vector2D operator/(float scalar);
	Vector2D& operator/=(float scalar);
	void Normalize();
};

#endif // !__Vector2D_h__