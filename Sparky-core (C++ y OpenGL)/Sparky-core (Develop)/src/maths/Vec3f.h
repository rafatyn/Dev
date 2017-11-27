#pragma once

#include <iostream>

namespace Sparky {
	namespace Maths {

		struct Vec2f;

		struct Vec3f {

			float x, y, z;

			Vec3f();
			Vec3f(float a, float b, float c);
			Vec3f(const Vec2f& vector);

			Vec3f& add(const Vec3f& other);
			Vec3f& sub(const Vec3f& other);
			Vec3f& mult(const Vec3f& other);
			Vec3f& div(const Vec3f& other);

			friend Vec3f operator+(const Vec3f& left, const Vec3f& right);
			friend Vec3f operator-(const Vec3f& left, const Vec3f& right);
			friend Vec3f operator*(const Vec3f& left, const Vec3f& right);
			friend Vec3f operator/(const Vec3f& left, const Vec3f& right);

			Vec3f& operator+=(const Vec3f& other);
			Vec3f& operator-=(const Vec3f& other);
			Vec3f& operator*=(const Vec3f& other);
			Vec3f& operator/=(const Vec3f& other);

			float distance(const Vec3f& other) const;

			friend std::ostream& operator<<(std::ostream& out, const Vec3f& vector);
		};

	}
}