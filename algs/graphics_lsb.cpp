//
// Created by Stek-l on 28/11/2025.
//

#include <bitset>
#include <cmath>

#include "graphics_helpers.h"
#include "graphics_lsb.h"

namespace gr {

	bool lsb_encode(QString path, QString message) {
		std::ifstream file(path.toStdString(), std::ios::binary);

		ImageMeta img_meta = verify_image(file);
		if (!img_meta.is_valid) {
			return false;
		}

		// convert message to binary
		std::string msg = message.toStdString();
		std::string bin_msg;
		for (size_t i = 0; i < msg.length(); i++) {
			bin_msg += std::bitset<8>(msg[i]).to_string();
		}
		// add the null terminator
		bin_msg += "00000000";

		// main loop over the image
		for (size_t y = 0; y < img_meta.height; y++) {
			for (size_t x = 0; x < img_meta.width; x++) {
				RGBPixel &pixel = img_meta.pixels[y * img_meta.width + x];
			}
		}

		return true;
	}

	QString lsb_decode(QString path) {
		std::ifstream file(path.toStdString(), std::ios::binary);

		ImageMeta img_meta = verify_image(file);
		if (!img_meta.is_valid) {
			return {"Invalid image"};
		}

		size_t null_term_cnt = 0;
		std::string bin_res;

		// main loop over the image
		for (size_t y = 0; y < img_meta.height; y++) {
			for (size_t x = 0; x < img_meta.width; x++) {
				RGBPixel &pixel = img_meta.pixels[y * img_meta.width + x];
				char bit = (pixel.r & 1) + '0';
				bin_res += bit;
				if (bit == '0' && ++null_term_cnt == 8) {
					//reached null terminator
					goto finish_reading;
				} else if (bit == '1') null_term_cnt = 0;

				bit = (pixel.g & 1) + '0';
				bin_res += bit;
				if (bit == '0' && ++null_term_cnt == 8) {
					//reached null terminator
					goto finish_reading;
				} else if (bit == '1') null_term_cnt = 0;

				bit = (pixel.b & 1) + '0';
				bin_res += bit;
				if (bit == '0' && ++null_term_cnt == 8) {
					//reached null terminator
					goto finish_reading;
				} else if (bit == '1') null_term_cnt = 0;
			}
		}
		finish_reading:

		QString res;
		if (bin_res.length() % 8 != 0) {
			res = "Invalid message; either no message was encoded or it got corrupted";
		} else {
			for (size_t i = 0; i < bin_res.length(); i += 8) {
				uint8_t buf = 0;
				for (int16_t b = 7; b >= 0; b--) {
					buf += std::pow(2, 8 - (b + 1)) * (bin_res[static_cast<int16_t>(i) + b] - '0');
				}
				res += static_cast<char>(buf);
			}
		}

		return res;
	}

} // namespace gr
