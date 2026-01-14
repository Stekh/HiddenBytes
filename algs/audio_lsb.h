//
// Created by Lenovo on 03.12.2025.
//

#ifndef HIDDENBYTES_AUDIO_LSB_H
#define HIDDENBYTES_AUDIO_LSB_H

#include <QString>

namespace ad {

	bool lsb_encode(const QString &path, const QString &message, const QString &output_dir);

	QString lsb_decode(const QString &path);

} // namespace ad

#endif // HIDDENBYTES_AUDIO_LSB_H