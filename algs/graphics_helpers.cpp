//
// Created by Stek-l on 28/11/2025.
//

#include "graphics_helpers.h"

namespace gr {
	ImageMeta verify_image(std::ifstream &file) {
		if (!file.is_open()) {
			return {false, 0, 0, std::vector<RGBPixel>{}};
		}

		BMPHeader bmp_header;
		DIBHeader dib_header;

		// read the bmp header
		file.read(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
		if (bmp_header.header[0] != 'B' || bmp_header.header[1] != 'M') {
			return {false, 0, 0, std::vector<RGBPixel>{}};
		}

		// read the dib header
		file.read(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));
		if (dib_header.bitsPerPixel != 24) {
			return {false, 0, 0, std::vector<RGBPixel>{}};
		}

		file.seekg(bmp_header.dataOffset, std::ios::beg);

		std::vector<RGBPixel> pixels (dib_header.width * dib_header.height);

		for (int32_t y = dib_header.height - 1; y >= 0; y--) {
			for (int32_t x = 0; x < dib_header.width; x++) {
				file.read(reinterpret_cast<char*>(&pixels[y * dib_header.width + x]), sizeof(RGBPixel));
			}
		}

		return {false, 0, 0, std::move(pixels)};
	}
} // namespace gr
