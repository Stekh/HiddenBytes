//
// Created by Stek-l on 28/11/2025.
//

#include <cmath>

#include "graphics_helpers.h"
#include "graphics_lsb.h"

namespace gr {

	QImage lsb_encode(QString path, QString message) {
		QImage image = QImage(path);

		QByteArray msg = message.toUtf8();
		const size_t msg_len = msg.size();
		size_t msg_iter = 0;
		size_t upper_half = 0;

		if (image.format() != QImage::Format_RGB32) {
			image = image.convertToFormat(QImage::Format_RGB32);
		}

		uchar *data = image.bits();
		const size_t width = image.width();
		const size_t height = image.height();
		const size_t bytes_per_line = image.bytesPerLine();

		bool stop = false;

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				// there are 4 bytes per pixel, accessible as data[offset+a] where a is a value between 0 and 3
				const size_t offset = y * bytes_per_line + x * 4;
				for (size_t b = 0; b < 4; b++) {
					if ((data[offset + b] & 1) ^ (msg[msg_iter] & (1 << (b + 4 * upper_half)))) {
						data[offset + b] ^= 1 << 1;
					}
				}

				upper_half ^= 1; // flip between 0 and 1

				if (upper_half == 1) {
					msg_iter++;

					if (msg_iter >= msg_len) {
						stop = true;
						break;
					}
				}
			}
			if (stop) {
				break;
			}
		}

		return QImage(data, width, height, QImage::Format_RGB32);
	}

	QString lsb_decode(QString path) {
		std::ifstream file(path.toUtf8(), std::ios::binary);

		ImageMeta img_meta = verify_image(file);
		if (!img_meta.is_valid) {
			return {"Invalid image"};
		}

		size_t null_term_cnt = 0;
		std::string bin_res;

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
