#pragma once

#include <iostream>

namespace Sparky {
	namespace Maths {

		struct Vec4f {

			float x, y, z, w;

			Vec4f() = default;
			Vec4f(float a, float b, float c, float d);

			Vec4f& add(const Vec4f& other);
			Vec4f& sub(const Vec4f& other);
			Vec4f& mult(const Vec4f& other);
			Vec4f& div(const Vec4f& other);

			friend Vec4f operator+(const Vec4f& left, const Vec4f& right);
			friend Vec4f operator-(const Vec4f& left, const Vec4f& right);
			friend Vec4f operator*(const Vec4f& left, const Vec4f& right);
			friend Vec4f operator/(const Vec4f& left, const Vec4f& right);

			Vec4f& operator+=(const Vec4f& other);
			Vec4f& operator-=(const Vec4f& other);
			Vec4f& operator*=(const Vec4f& other);
			Vec4f& operator/=(const Vec4f& other);	

			friend std::ostream& operator<<(std::ostream& out, const Vec4f& vector);
		};

	}
}