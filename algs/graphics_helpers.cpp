//
// Created by Stek-l on 28/11/2025.
//

#include <QString>

#include <bitset>
#include "graphics_helpers.h"

namespace gr {
	ImageMeta verify_image(std::ifstream &file) {
		if (!file.is_open()) {
			return {false, {}, {}, std::vector<RGBPixel>{}};
		}

		BMPHeader bmp_header;
		DIBHeader dib_header;

		// read the bmp header
		file.read(reinterpret_cast<char *>(&bmp_header), sizeof(bmp_header));
		if (bmp_header.header[0] != 'B' || bmp_header.header[1] != 'M') {
			return {false, {}, {}, std::vector<RGBPixel>{}};
		}

		// read the dib header
		file.read(reinterpret_cast<char *>(&dib_header), sizeof(dib_header));
		if (dib_header.bitsPerPixel != 24) {
			return {false, {}, {}, std::vector<RGBPixel>{}};
		}

		file.seekg(bmp_header.dataOffset, std::ios::beg);

		std::vector<RGBPixel> pixels(dib_header.width * dib_header.height);

		for (int32_t y = dib_header.height - 1; y >= 0; y--) {
			for (int32_t x = 0; x < dib_header.width; x++) {
				file.read(reinterpret_cast<char *>(&pixels[y * dib_header.width + x]), sizeof(RGBPixel));
			}
		}

		return {true, bmp_header, dib_header, std::move(pixels)};
	}

	QString bin2str(const std::string &bin_str) {
		QString res;
		for (size_t i = 0; i < bin_str.length(); i += 8) {
			uint8_t buf = 0;
			for (int16_t b = 7; b >= 0; b--) {
				buf += std::pow(2, 8 - (b + 1)) * (bin_str[static_cast<int16_t>(i) + b] - '0');
			}
			res += static_cast<char>(buf);
		}

		return res;
	}

	std::string str2bin(const std::string &str) {
		std::string bin_str;
		for (size_t i = 0; i < str.length(); i++) {
			bin_str += std::bitset<8>(str[i]).to_string();
		}
		// add the null terminator
		bin_str += "00000000";

		return bin_str;
	}
} // namespace gr
