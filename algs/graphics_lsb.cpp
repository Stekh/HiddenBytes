//
// Created by Stek-l on 28/11/2025.
//

#include <fstream>

#include "graphics_helpers.h"
#include "graphics_lsb.h"
#include "utils.h"

namespace gr {

	bool lsb_encode(const QString &path, const QString &message, const QString &output_dir) {
		std::ifstream file(path.toStdString(), std::ios::binary);

		ImageMeta img_meta = verify_image(file);
		if (!img_meta.is_valid) {
			return false;
		}

		// convert message to binary
		std::string msg = message.toStdString();
		std::string bin_msg = str2bin(msg);
		size_t bin_cnt = 0;

		// main loop over the image
		for (size_t y = 0; y < img_meta.dib_header.height; y++) {
			for (size_t x = 0; x < img_meta.dib_header.width; x++) {
				RGBPixel &pixel = img_meta.pixels[y * img_meta.dib_header.width + x];
				if (bin_cnt == bin_msg.length()) {
					goto finish_writing;
				}
				if (pixel.r & 1 ^ bin_msg[bin_cnt] - '0') {
					pixel.r ^= 1; // flip LSB
				}
				bin_cnt++;

				if (bin_cnt == bin_msg.length()) {
					goto finish_writing;
				}
				if (pixel.g & 1 ^ bin_msg[bin_cnt] - '0') {
					pixel.g ^= 1; // flip LSB
				}
				bin_cnt++;

				if (bin_cnt == bin_msg.length()) {
					goto finish_writing;
				}
				if (pixel.b & 1 ^ bin_msg[bin_cnt] - '0') {
					pixel.b ^= 1; // flip LSB
				}
				bin_cnt++;
			}
		}
	finish_writing:

		bool res = save_res_image(output_dir, std::move(img_meta));

		file.close();
		return res;
	}

	QString lsb_decode(const QString &path) {
		std::ifstream file(path.toStdString(), std::ios::binary);

		ImageMeta img_meta = verify_image(file);
		if (!img_meta.is_valid) {
			return {"Invalid image"};
		}

		size_t null_term_cnt = 0;
		size_t byte_cnt = 0;
		std::string bin_res;

		// main loop over the image
		for (size_t y = 0; y < img_meta.dib_header.height; y++) {
			for (size_t x = 0; x < img_meta.dib_header.width; x++) {
				RGBPixel &pixel = img_meta.pixels[y * img_meta.dib_header.width + x];
				char bit = (pixel.r & 1) + '0';
				bin_res += bit;
				byte_cnt++;
				if (bit == '0') {
					null_term_cnt++;
					if (byte_cnt % 8 == 0 && ++null_term_cnt >= 8) {
						// reached null terminator
						goto finish_reading;
					}
				} else if (bit == '1')
					null_term_cnt = 0;

				bit = (pixel.g & 1) + '0';
				bin_res += bit;
				byte_cnt++;
				if (bit == '0') {
					null_term_cnt++;
					if (byte_cnt % 8 == 0 && ++null_term_cnt >= 8) {
						// reached null terminator
						goto finish_reading;
					}
				} else if (bit == '1')
					null_term_cnt = 0;

				bit = (pixel.b & 1) + '0';
				bin_res += bit;
				byte_cnt++;
				if (bit == '0') {
					null_term_cnt++;
					if (byte_cnt % 8 == 0 && ++null_term_cnt >= 8) {
						// reached null terminator
						goto finish_reading;
					}
				} else if (bit == '1')
					null_term_cnt = 0;
			}
		}
	finish_reading:

		QString res = bin2str(bin_res);

		file.close();
		return res.removeLast();
	}

} // namespace gr
