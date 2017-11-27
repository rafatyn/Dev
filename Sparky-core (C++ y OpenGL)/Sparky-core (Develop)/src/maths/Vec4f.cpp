#include "Vec4f.h"

namespace Sparky {
	namespace Maths {
		
		Vec4f::Vec4f(float a, float b, float c, float d)
		{
			x = a;
			y = b;
			z = c;
			w = d;
		}

		Vec4f& Vec4f::add(const Vec4f& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		Vec4f& Vec4f::sub(const Vec4f& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}
		
		Vec4f& Vec4f::mult(const Vec4f& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		Vec4f& Vec4f::div(const Vec4f& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			
			return *this;
		}

		Vec4f& Vec4f::operator+=(const Vec4f& other)
		{
			return add(other);
		}
		
		Vec4f& Vec4f::operator-=(const Vec4f& other)
		{
			return sub(other);
		}
		
		Vec4f& Vec4f::operator*=(const Vec4f& other)
		{
			return mult(other);
		}
		
		Vec4f& Vec4f::operator/=(const Vec4f& other)
		{
			return div(other);
		}

		Vec4f operator+(const Vec4f& left, const Vec4f& right)
		{
			Vec4f tmp(left);
			return tmp.add(right);
		}

		Vec4f operator-(const Vec4f& left, const Vec4f& right)
		{
			Vec4f tmp(left);
			return tmp.sub(right);
		}

		Vec4f operator*(const Vec4f& left, const Vec4f& right)
		{
			Vec4f tmp(left);
			return tmp.mult(right);
		}

		Vec4f operator/(const Vec4f& left, const Vec4f& right)
		{
			Vec4f tmp(left);
			return tmp.div(right);
		}

		std::ostream& operator<<(std::ostream& out, const Vec4f& vector)
		{
			out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return out;
		}

	}
}