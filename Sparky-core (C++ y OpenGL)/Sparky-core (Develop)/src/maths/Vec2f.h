#pragma once

#include <iostream>
#include <math.h>
#include "Vec3f.h"

namespace Sparky {
	namespace Maths {

		struct Vec2f {

			float x, y;

			Vec2f();
			Vec2f(float a, float b);
			Vec2f(const Vec3f& vector);	

			Vec2f& add(const Vec2f& other);
			Vec2f& sub(const Vec2f& other);
			Vec2f& mult(const Vec2f& other);
			Vec2f& div(const Vec2f& other);

			friend Vec2f operator+(const Vec2f& left, const Vec2f& right);
			friend Vec2f operator-(const Vec2f& left, const Vec2f& right);
			friend Vec2f operator*(const Vec2f& left, const Vec2f& right);
			friend Vec2f operator/(const Vec2f& left, const Vec2f& right);

			friend Vec2f operator+(const Vec2f& left, float value);
			friend Vec2f operator*(const Vec2f& left, float value);

			Vec2f& operator+=(const Vec2f& other);
			Vec2f& operator-=(const Vec2f& other);
			Vec2f& operator*=(const Vec2f& other);
			Vec2f& operator/=(const Vec2f& other);	

			float distance(const Vec2f& other) const;
			float dot(const Vec2f& other) const;
			float magnitude() const;
			Vec2f normalise() const;

			friend std::ostream& operator<<(std::ostream& out, const Vec2f& vector);
		};

	}
}