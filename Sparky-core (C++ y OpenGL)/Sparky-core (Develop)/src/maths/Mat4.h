#pragma once

#include "Vec3f.h"
#include "Vec4f.h"
#include "Maths_func.h"

namespace Sparky {
	namespace Maths {
		
		struct Mat4 {

			union {
				float elements[4 * 4];
				Vec4f columns[4];
			};

			Mat4();
			Mat4(float diagonal);

			static Mat4 Identity();

			Vec4f GetColumn(int index)
			{
				index *= 4;
				return Vec4f(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
			}

			Mat4& Multiply(const Mat4& other);
			friend Mat4 operator*(Mat4 left, const Mat4& right);
			Mat4& operator*=(const Mat4& other);

			Vec3f Multiply(const Vec3f& other) const;
			friend Vec3f operator*(const Mat4& left, const Vec3f& right);

			Vec4f Multiply(const Vec4f& other) const;
			friend Vec4f operator*(const Mat4& left, const Vec4f& right);

			Mat4& invert();

			static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static Mat4 Perspective(float fov, float aspectRatio, float near, float far);

			static Mat4 Translation(const Vec3f& translation);
			static Mat4 Rotation(float angle, const Vec3f& axis);
			static Mat4 Scale(const Vec3f& scale);
		};

	}
}