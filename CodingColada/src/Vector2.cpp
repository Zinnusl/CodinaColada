#pragma once

#include "Vector2.h"

#include <cmath>

Vector2::Vector2()
	: x_(0.f), y_(0.f)
{
}

Vector2::Vector2(float x, float y)
	: x_(x), y_(y)
{
}

Vector2::Vector2(float xy)
	: x_(xy), y_(xy)
{
}

float Vector2::length() const
{
	return sqrtf(x_ * x_ + y_ * y_);
}

float Vector2::distance(const Vector2& other) const
{
	Vector2 delta = *this - other;
	return delta.length();
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x_ + other.x_, y_ + other.y_);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x_ - other.x_, y_ - other.y_);
}

Vector2 Vector2::operator*(float multi) const
{
	return Vector2(x_ * multi, y_ * multi);
}

Vector2 Vector2::operator/(float divisor) const
{
	return Vector2(x_ * divisor, y_ * divisor);
}

bool Vector2::operator==(const Vector2& other) const
{
	//TODO we are comparing floats with == without an epsilon
	return x_ == other.x_ && y_ == other.y_;
}

float Vector2::dot(const Vector2& other) const
{
	return x_ * other.x_ + +y_ * other.y_;
}

Vector2 Vector2::lerp(const Vector2& first, const Vector2& second, float t)
{
	auto tmp = first * (1.f - t) + second * t;
	return tmp;
}

float Vector2::GetX() const
{
	return x_;
}

float Vector2::GetY() const
{
	return y_;
}

void Vector2::SetX(float value)
{
	x_ = value;
}

void Vector2::SetY(float value)
{
	y_ = value;
}
