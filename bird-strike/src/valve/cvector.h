#pragma once
#define _USE_MATH_DEFINES
#include <numbers>
#include <cstdint>
#include <cmath>

inline float Pi()
{
	return (float)(std::atan(1) * 4);
}


class CVector
{
public:
	constexpr CVector operator+(const CVector& other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr CVector operator-(const CVector& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr CVector operator*(const CVector& other) const noexcept
	{
		return { x * other.x, y * other.y, z * other.z };
	}

	constexpr CVector operator/(const CVector& other) const noexcept
	{
		return { x / other.x, y / other.y, z / other.z };
	}

	constexpr CVector Scale(float factor) const noexcept
	{
		return { x * factor, y * factor, z * factor };
	}

	inline CVector ToAngle() const noexcept
	{
		return {
			std::atan2(-z, std::hypot(x, y)) * (180.0f / Pi()),
			std::atan2(y, x) * (180.0f / Pi()),
			0.0f
		};
	}

	float x{ }, y{ }, z{ };
};

__declspec(align(16)) class CVectorAligned : public CVector
{
public:
	constexpr CVectorAligned operator-(const CVectorAligned& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}

	float w{ };
};