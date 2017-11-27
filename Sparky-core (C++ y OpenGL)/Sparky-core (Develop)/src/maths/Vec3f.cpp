#include "Vec3f.h"
#include "Vec2f.h"

namespace Sparky {
	namespace Maths {

		Vec3f::Vec3f()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Vec3f::Vec3f(float a, float b, float c)
		{
			x = a;
			y = b;
			z = c;
		}

		Vec3f::Vec3f(const Vec2f & vector)
		{
			x = vector.x;
			y = vector.y; 
			z = 0.0f;
		}

		Vec3f& Vec3f::add(const Vec3f& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		Vec3f& Vec3f::sub(const Vec3f& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}
		
		Vec3f& Vec3f::mult(const Vec3f& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		Vec3f& Vec3f::div(const Vec3f& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		Vec3f& Vec3f::operator+=(const Vec3f& other)
		{
			return add(other);
		}
		
		Vec3f& Vec3f::operator-=(const Vec3f& other)
		{
			return sub(other);
		}
		
		Vec3f& Vec3f::operator*=(const Vec3f& other)
		{
			return mult(other);
		}
		
		Vec3f& Vec3f::operator/=(const Vec3f& other)
		{
			return div(other);
		}

		float Vec3f::distance(const Vec3f & other) const
		{
			float a = x - other.x;
			float b = y - other.y;
			float c = z - other.z;
			return sqrt(a * a + b * b + c * c);
		}

		Vec3f operator+(const Vec3f& left, const Vec3f& right)
		{
			Vec3f tmp(left);
			return tmp.add(right);
		}

		Vec3f operator-(const Vec3f& left, const Vec3f& right)
		{
			Vec3f tmp(left);
			return tmp.sub(right);
		}

		Vec3f operator*(const Vec3f& left, const Vec3f& right)
		{
			Vec3f tmp(left);
			return tmp.mult(right);
		}

		Vec3f operator/(const Vec3f& left, const Vec3f& right)
		{
			Vec3f tmp(left);
			return tmp.div(right);
		}

		std::ostream& operator<<(std::ostream& out, const Vec3f& vector)
		{
			out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return out;
		}

	}
}