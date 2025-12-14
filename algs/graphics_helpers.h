//
// Created by Stek-l on 28/11/2025.
//

#ifndef HIDDENBYTES_GRAPHICS_HELPERS_H
#define HIDDENBYTES_GRAPHICS_HELPERS_H

#include <cstdint>
#include <fstream>
#include <vector>

namespace gr {

#pragma pack(push, 1) // Ensure that structure members are not padded

	// Define BMP Header Structure

	struct BMPHeader {
		char header[2]; // 'BM' for Bitmap
		uint32_t fileSize; // Size of the entire file
		uint32_t reserved; // Reserved (usually 0)
		uint32_t dataOffset; // Offset to the pixel data
	};


	struct DIBHeader {
		uint32_t headerSize; // DIB Header size (40 bytes)
		int32_t width; // Image width
		int32_t height; // Image height
		uint16_t colorPlanes; // Color planes (usually 1)
		uint16_t bitsPerPixel; // Bits per pixel (24 for RGB)
		uint32_t compression; // Compression type (0 for none)
		uint32_t imageSize; // Image size (may be 0 for uncompressed)
		int32_t xRes; // Horizontal resolution (pixels per meter)
		int32_t yRes; // Vertical resolution (pixels per meter)
		uint32_t colors; // Number of colors
		uint32_t importantColors; // Important colors
	};

	// Define a pixel structure for RGB
	struct RGBPixel {
		uint8_t b;
		uint8_t g;
		uint8_t r;
	};

#pragma pack(pop) // Restore previous packing alignment

	struct ImageMeta {
		bool is_valid;
		int32_t width;
		int32_t height;
		std::vector<RGBPixel> pixels;
	};

	ImageMeta verify_image(std::ifstream &file);

} // namespace gr

#endif // HIDDENBYTES_GRAPHICS_HELPERS_H
