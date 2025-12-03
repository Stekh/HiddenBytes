//
// Created by Stek-l on 28/11/2025.
//

#include <QByteArray>

#include "graphics_helpers.h"
#include "graphics_lsb.h"

namespace gr {

	QImage lsb_encode(QString path, QString message) {
		QImage image = load_image(path);

		QByteArray msg = message.toUtf8();
		const size_t msg_len = msg.size();
		size_t msg_iter = 0;
		size_t bit_iter = 0;

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
				if (bit_iter == 3) {
					bit_iter %= 2;
					msg_iter++;
					if (msg_iter > msg_len) {
						stop = true;
						break;
					}
				}
				for (size_t b = 0; b < 4; b++) {
					if ((data[offset + b] & 1) ^ (msg[msg_iter] & (1 << (b + 4 * bit_iter)))) {
						data[offset + b] ^= 1 << 1;
					}
					bit_iter++;
				}
			}
			if (stop) {
				break;
			}
		}

		return QImage(data, width, height, QImage::Format_RGB32);
	}

	QString lsb_decode(QString path) {
		QImage image = load_image(path);

		if (image.format() != QImage::Format_RGB32) {
			image = image.convertToFormat(QImage::Format_RGB32);
		}

		const uchar *data = image.bits();
		const size_t width = image.width();
		const size_t height = image.height();
		const size_t bytes_per_line = image.bytesPerLine();

		QByteArray result;
		size_t upper_half = 0;
		size_t msg_cnt = 0;
		result.append('\0');

		bool stop = false;

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				// there are 4 bytes per pixel, accessible as data[offset+a] where a is a value between 0 and 3
				const size_t offset = y * bytes_per_line + x * 4;
				quint8 current_byte = static_cast<quint8>(result.at(msg_cnt));
				for (size_t b = 0; b < 4; b++) {
					if ((data[offset + b] & 1) == 1) {
						current_byte |= 1 << (b + 4 * upper_half);
					} else {
						current_byte &= ~(1 << (b + 4 * upper_half));
					}
				}

				result[msg_cnt] = static_cast<char>(current_byte);
				++upper_half %= 2;

				if (x > 0 && x % 2 == 0) {
					msg_cnt++;
					result.append('\0');
				}

				if (upper_half == 1 && current_byte == 0) {
					stop = true;
					break;
				}
			}

			if (stop) {
				break;
			}
		}

		return QString(result);
	}

} // namespace gr
