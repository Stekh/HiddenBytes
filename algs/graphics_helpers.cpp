//
// Created by Stek-l on 28/11/2025.
//

#include <QString>
#include <fstream>

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

	bool save_res_image(const QString &output_dir, ImageMeta img_meta) {
		std::ofstream res_file(output_dir.toStdString() + "/res.bmp", std::ios::binary);
		if (!res_file.is_open()) {
			return false;
		}

		res_file.write(reinterpret_cast<char *>(&img_meta.bmp_header), sizeof(img_meta.bmp_header));
		res_file.write(reinterpret_cast<char *>(&img_meta.dib_header), sizeof(img_meta.dib_header));
		res_file.seekp(img_meta.bmp_header.dataOffset, std::ios::beg);

		for (int32_t y = img_meta.dib_header.height - 1; y >= 0; y--) {
			for (int32_t x = 0; x < img_meta.dib_header.width; x++) {
				res_file.write(reinterpret_cast<char *>(&img_meta.pixels[y * img_meta.dib_header.width + x]),
							   sizeof(RGBPixel));
			}
		}

		res_file.close();

		return true;
	}
} // namespace gr
