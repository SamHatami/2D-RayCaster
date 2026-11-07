#pragma once
struct vector2
{
	float x;
	float y;

	constexpr vector2(float x = 0, float y = 0) : x(x), y(y)
	{
	}

	float Magnitude() const;
	vector2 Normalized() const;
	static vector2 GetNormal(vector2& a);
	static float Dot(vector2& a, vector2& b);
	static float Dot(const vector2& a, const vector2& b);

	static float Magnitude(vector2& a);
	static void Normalize(vector2& a);

	friend vector2 operator+(const vector2& a, const vector2& b);

	friend vector2 operator-(const vector2& a, const vector2& b);

	friend vector2 operator*(const vector2& a, float scalar);

	friend vector2 operator/(const vector2& a, float scalar);
};
