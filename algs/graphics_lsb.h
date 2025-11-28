//
// Created by Stek-l on 28/11/2025.
//

#ifndef HIDDENBYTES_GRAPHICS_LSB_H
#define HIDDENBYTES_GRAPHICS_LSB_H

#include <QImage>

namespace gr {
	QImage lsb_encode(QString path, QString message);

	QString lsb_decode(QString path);

} // namespace gr

#endif // HIDDENBYTES_GRAPHICS_LSB_H
