#pragma once

#include <type_traits>

namespace hk
{
	template<typename T>
	struct Vector2
	{
		T x;
		T y;

		// Ctors
		Vector2()
			: x()
			, y()
		{
			static_assert(std::is_arithmetic<T>::value, "Not an arithmetic type");
		}

		Vector2(T _x, T _y)
			: x(_x)
			, y(_y)
		{
			static_assert(std::is_arithmetic<T>::value, "Not an arithmetic type");
		}

		Vector2(const Vector2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}

		T Magnitude() const
		{
			return (T)sqrt((x * x) + (y * y));
		}

		T MagnitudeSquared() const
		{
			return (x * x) + (y * y);
		}

		Vector2<T>& Normalise()
		{
			const T mag = Magnitude();

			x /= mag;
			y /= mag;

			return *this;
		}

		Vector2<T> AsNormalised() const
		{
			const T mag = Magnitude();
			return { x / mag, y / mag };
		}
	};

	// Operators
	template<typename T>
	Vector2<T> operator-(const Vector2<T>& rhs)
	{
		return { -rhs.x, -rhs.y };
	}

	template<typename T>
	bool operator==(const Vector2<T> lhs, const Vector2<T> rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template<typename T>
	bool operator!=(const Vector2<T> lhs, const Vector2<T> rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	template<typename T>
	Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	template<typename T>
	Vector2<T> operator*(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		return { lhs.x * rhs.x, lhs.y * rhs.y };
	}

	template<typename T>
	Vector2<T> operator/(Vector2<T> lhs, const Vector2<T>& rhs)
	{
		return { lhs.x / rhs.x, lhs.y / rhs.y };
	}

	template<typename T>
	const Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;

		return lhs;
	}

	template<typename T>
	const Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;

		return lhs;
	}

	template<typename T>
	const Vector2<T>& operator*=(Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;

		return lhs;
	}

	template<typename T>
	const Vector2<T>& operator/=(Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;

		return lhs;
	}

	using Vector2i = Vector2<int32_t>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2u = Vector2<uint32_t>;
}