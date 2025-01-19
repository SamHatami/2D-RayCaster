#pragma once
#include "Geometry.h"

struct vector2
{
	float x;
	float y;

	vector2(float x = 0, float y = 0) : x(x), y(y) {}

	void Multiply(float scalar);
	void Divide(float scalar);
	void Normalize();
	float Magnitude() const;
	vector2 Normalized() const;
	static vector2 GetNormal(vector2& a);
	static vector2 PointsToVector2(const Point& a, const Point& b);
	static vector2 Add(vector2& a, vector2& b);
	static vector2 Subtract(vector2& a, vector2& b);
	static float Dot(vector2& a, vector2& b);
	static float Dot(const vector2& a, const vector2& b);
	static void Multiply(vector2& a, float scalar);
	static void Divide(vector2& a, float scalar);

	static float Magnitude(vector2& a);
	static void Normalize(vector2& a);
};
