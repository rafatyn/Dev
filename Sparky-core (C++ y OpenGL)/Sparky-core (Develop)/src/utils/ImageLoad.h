#pragma once

#include <utils\Log.h>
#include <FreeImage\FreeImage.h>
#include <FreeImage\Utilities.h>

namespace Sparky {

	static BYTE* loadImage(const char* filename, GLsizei* width, GLsizei* height, unsigned int* bits)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = 0;

		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);

		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);

		if (!dib) {
			SPARKY_ERROR("[Utils] Cannot open image file with name ", filename);
			return nullptr;
		}

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		*bits = FreeImage_GetBPP(dib);

		if ((pixels == 0) || (*width == 0) || (*height == 0))
			return nullptr;

#ifdef SPARKY_EMSCRIPTEN
		SwapRedBlue32(dib);
#endif
		unsigned int size = FreeImage_GetDIBSize(dib);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		
		FreeImage_Unload(dib);

		return result;
	}
}