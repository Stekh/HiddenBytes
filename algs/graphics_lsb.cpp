//
// Created by Stek-l on 28/11/2025.
//

#include "graphics_lsb.h"
#include "graphics_helpers.h"

namespace gr {

	bool lsb_encode(QString path, QString message) {
		std::ifstream file(path.toStdString(), std::ios::binary);

		ImageMeta img_meta = verify_image(file);
		if (!img_meta.is_valid) {
			return false;
		}

		// convert message to binary
		std::string msg = message.toStdString();
		std::string bin_msg = str2bin(msg);

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
		size_t byte_cnt = 0;
		std::string bin_res;

		// main loop over the image
		for (size_t y = 0; y < img_meta.height; y++) {
			for (size_t x = 0; x < img_meta.width; x++) {
				RGBPixel &pixel = img_meta.pixels[y * img_meta.width + x];
				char bit = (pixel.r & 1) + '0';
				bin_res += bit;
				byte_cnt++;
				if (bit == '0') {
					null_term_cnt++;
					if (byte_cnt == 7 && ++null_term_cnt == 8) {
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
					if (byte_cnt == 7 && ++null_term_cnt == 8) {
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
					if (byte_cnt == 7 && ++null_term_cnt == 8) {
						// reached null terminator
						goto finish_reading;
					}
				} else if (bit == '1')
					null_term_cnt = 0;
			}
		}
	finish_reading:

		QString res = bin2str(bin_res);

		return res;
	}

} // namespace gr
