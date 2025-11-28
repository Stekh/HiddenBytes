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
		size_t msg_len = msg.size();
		size_t msg_iter = 0;
		size_t bit_iter = 0;

		if (image.format() != QImage::Format_RGB32) {
			image = image.convertToFormat(QImage::Format_RGB32);
		}

		uchar *data = image.bits();
		size_t width = image.width();
		size_t height = image.height();
		size_t bytes_per_line = image.bytesPerLine();

		bool stop = false;

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				// there are 4 bytes per pixel, accessible as data[offset+a] where a is a value between 0 and 3
				size_t offset = y * bytes_per_line + x * 4;
				if (bit_iter == 3) {
					bit_iter %= 2;
					msg_iter++;
					if (msg_iter > msg_len) {
						stop = true;
						break;
					}
				}
				for (size_t b = 0; b < 4; b++) {
					if ((data[offset+b] & (1 << 1)) ^ (msg[msg_iter] & (1 << (b + 4*bit_iter)))) {
						data[offset] ^= 1 << 1;
						bit_iter++;
					}
				}
			}
			if (stop) {
				break;
			}
		}

		return QImage(data, width, height, QImage::Format_RGB32);
	}

	QString lsb_decode(QString path) { return ""; }

} // namespace gr
