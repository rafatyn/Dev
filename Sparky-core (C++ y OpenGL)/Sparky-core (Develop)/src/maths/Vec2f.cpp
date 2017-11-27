#include "Vec2f.h"

namespace Sparky {
	namespace Maths {

		Vec2f::Vec2f()
		{
			x = 0.0f;
			y = 0.0f;
		}

		Vec2f::Vec2f(float a, float b)
		{
			x = a;
			y = b;
		}

		Vec2f::Vec2f(const Vec3f & vector)
		{
			x = vector.x;
			y = vector.y;
		}

		Vec2f& Vec2f::add(const Vec2f& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vec2f& Vec2f::sub(const Vec2f& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}
		
		Vec2f& Vec2f::mult(const Vec2f& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		Vec2f& Vec2f::div(const Vec2f& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		Vec2f& Vec2f::operator+=(const Vec2f& other)
		{
			return add(other);
		}
		
		Vec2f& Vec2f::operator-=(const Vec2f& other)
		{
			return sub(other);
		}
		
		Vec2f& Vec2f::operator*=(const Vec2f& other)
		{
			return mult(other);
		}
		
		Vec2f& Vec2f::operator/=(const Vec2f& other)
		{
			return div(other);
		}

		float Vec2f::distance(const Vec2f & other) const
		{
			float a = x - other.x;
			float b = y - other.y;
			return sqrt(a * + b * b);
		}

		float Vec2f::dot(const Vec2f & other) const
		{
			return x * other.x + y * other.y;
		}

		float Vec2f::magnitude() const
		{
			return sqrt(x * x + y * y);
		}

		Vec2f Vec2f::normalise() const
		{
			float length = magnitude();
			return Vec2f(x / length, y / length);
		}

		Vec2f operator+(const Vec2f& left, const Vec2f& right)
		{
			Vec2f tmp(left);
			return tmp.add(right);
		}

		Vec2f operator-(const Vec2f& left, const Vec2f& right)
		{
			Vec2f tmp(left);
			return tmp.sub(right);
		}

		Vec2f operator*(const Vec2f& left, const Vec2f& right)
		{
			Vec2f tmp(left);
			return tmp.mult(right);
		}

		Vec2f operator/(const Vec2f& left, const Vec2f& right)
		{
			Vec2f tmp(left);
			return tmp.div(right);
		}

		Vec2f operator+(const Vec2f& left, float value)
		{
			return Vec2f(left.x + value, left.y + value);
		}

		Vec2f operator*(const Vec2f& left, float value)
		{
			return Vec2f(left.x * value, left.y * value);
		}

		std::ostream& operator<<(std::ostream& out, const Vec2f& vector)
		{
			out << "Vector(" << vector.x << ", " << vector.y << ")";
			return out;
		}

	}
}