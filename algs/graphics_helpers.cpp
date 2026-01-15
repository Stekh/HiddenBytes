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
		// file.read(reinterpret_cast<char *>(&bmp_header), sizeof(bmp_header));
		file.read(bmp_header.header, 2);
		file.read(reinterpret_cast<char*>(&bmp_header.fileSize), 4);
		file.read(reinterpret_cast<char*>(&bmp_header.reserved), 4);
		file.read(reinterpret_cast<char*>(&bmp_header.dataOffset), 4);
		if (bmp_header.header[0] != 'B' || bmp_header.header[1] != 'M') {
			return {false, {}, {}, std::vector<RGBPixel>{}};
		}

		// read the dib header
		// file.read(reinterpret_cast<char *>(&dib_header), sizeof(dib_header));
		file.read(reinterpret_cast<char*>(&dib_header.headerSize), 4);
		file.read(reinterpret_cast<char*>(&dib_header.width), 4);
		file.read(reinterpret_cast<char*>(&dib_header.height), 4);
		file.read(reinterpret_cast<char*>(&dib_header.colorPlanes), 2);
		file.read(reinterpret_cast<char*>(&dib_header.bitsPerPixel), 2);
		file.read(reinterpret_cast<char*>(&dib_header.compression), 4);
		file.read(reinterpret_cast<char*>(&dib_header.imageSize), 4);
		file.read(reinterpret_cast<char*>(&dib_header.xRes), 4);
		file.read(reinterpret_cast<char*>(&dib_header.yRes), 4);
		file.read(reinterpret_cast<char*>(&dib_header.colors), 4);
		file.read(reinterpret_cast<char*>(&dib_header.importantColors), 4);
		if (dib_header.bitsPerPixel != 24) {
			return {false, {}, {}, std::vector<RGBPixel>{}};
		}

		file.seekg(bmp_header.dataOffset, std::ios::beg);

		const int32_t width = dib_header.width;
		const int32_t height = std::abs(dib_header.height);

		const size_t rowSize = ((width * 3 + 3) / 4) * 4;
		std::vector<uint8_t> row(rowSize);

		std::vector<RGBPixel> pixels(width * height);

		for (int32_t y = height - 1; y >= 0; y--) {
			file.read(reinterpret_cast<char *>(row.data()), rowSize);

			for (int32_t x = 0; x < width; x++) {
				std::memcpy(&pixels[y * width + x], row.data() + x * 3, 3);
			}
		}

		return {true, bmp_header, dib_header, std::move(pixels)};
	}

	bool save_res_image(const QString &output_dir, ImageMeta img_meta) {
		std::ofstream res_file(output_dir.toStdString() + "/res.bmp");
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
