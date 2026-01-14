
#ifndef HIDDENBYTES_AUDIO_LSB_H
#define HIDDENBYTES_AUDIO_LSB_H

#include <string>
#include <QString>
#include "audio_helpers.h"
namespace ad{
	bool lsb_encode(const QString &path, const QString &message, const QString &output_wav_file);
	QString lsb_decode(const QString& path);
}
#endif // HIDDENBYTES_AUDIO_LSB_H
