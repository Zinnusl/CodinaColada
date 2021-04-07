#pragma once

class Vector2
{
protected:
	float x_;
	float y_;

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(float xy);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float multi) const;
	Vector2 operator/(float divisor) const;
	bool operator==(const Vector2& other) const;

	float GetX() const;
	float GetY() const;

	void SetX(float value);
	void SetY(float value);

	float length() const;
	float distance(const Vector2& other) const;

	float dot(const Vector2& other) const;

	static bool isPointInRectangle(const Vector2& point, const Vector2& rectStart, const Vector2& rectSize);
	//TODO not sure if it works
	static bool intersects(const Vector2& rectALeft, const Vector2& rectARight, const Vector2& rectBLeft, const Vector2& rectBRight);

	static Vector2 lerp(const Vector2& first, const Vector2& second, float t);

};