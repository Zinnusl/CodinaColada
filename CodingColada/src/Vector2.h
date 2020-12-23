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
};