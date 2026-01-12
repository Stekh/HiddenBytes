//
// Created by Stek-l on 28/11/2025.
//

#ifndef HIDDENBYTES_GRAPHICS_LSB_H
#define HIDDENBYTES_GRAPHICS_LSB_H

#include <QImage>

namespace gr {
	bool lsb_encode(const QString& path, const QString& message, const QString& output_dir);

	QString lsb_decode(const QString& path);

} // namespace gr

#endif // HIDDENBYTES_GRAPHICS_LSB_H
