#pragma once

#include "../maths/maths.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Sparky {

	static unsigned int ColorToUInt(const Maths::Vec4f& color)
	{
		unsigned int r = (unsigned int)(color.x * 255.0f);
		unsigned int g = (unsigned int)(color.y * 255.0f);
		unsigned int b = (unsigned int)(color.z * 255.0f);
		unsigned int a = (unsigned int)(color.w * 255.0f);

		unsigned int col = a << 24 | b << 16 | g << 8 | r;

		return col;
	}

	static Maths::Vec4f ColorToVec(const unsigned int color)
	{
		Maths::Vec4f col;

		col.x = round((((color & (unsigned int)(0x000000FF))) / 255.0f) * 10.0f) / 10.0f;
		col.y = round((((color & (unsigned int)(0x0000FF00)) >> 8) / 255.0f) * 10.0f) / 10.0f;
		col.z = round((((color & (unsigned int)(0x00FF0000)) >> 16) / 255.0f) * 10.0f) / 10.0f;
		col.w = round((((color & (unsigned int)(0xFF000000)) >> 24) / 255.0f) * 10.0f) / 10.0f;

		return col;
	}
}