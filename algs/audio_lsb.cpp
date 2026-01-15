//
// Created by Lenovo on 03.12.2025.
//

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "audio_helpers.h"
#include "audio_lsb.h"
#include "utils.h"


namespace ad {

	bool lsb_encode(const QString &path, const QString &message, const QString &output_dir) {
		Wav_File file = read_wav_file(path.toStdString());
		std::string bits = str2bin(message.toStdString());

		if (bits.size() > file.data.size()) {
			return false;
		}

		for (size_t i = 0; i < bits.size(); i++) {
			uint16_t sample = file.data[i];

			if (bits[i] == '1') {
				sample |= 1;
			} else {
				sample &= ~1;
			}

			file.data[i] = sample;
		}

		std::ofstream file_with_message(output_dir.toStdString() + "/res.wav", std::ios::binary);
		if (!file_with_message.is_open())
			return false;

		file_with_message.write(reinterpret_cast<char *>(&file.properties), sizeof(Wav_File_Properties));
		file_with_message.write(reinterpret_cast<char *>(file.data.data()), file.data.size() * sizeof(int16_t));

		file_with_message.close();

		return true;
	}


	QString lsb_decode(const QString &path) {
		Wav_File file = read_wav_file(path.toStdString());
		int null_cnt = 0;
		std::string message;

		for (size_t i = 0; i < file.data.size(); i++) {
			if (null_cnt != 8) {
				uint16_t bit = file.data[i] & 1;
				if (bit == 0) {
					null_cnt++;
				} else {
					null_cnt = 0;
				}
				message += std::to_string(bit);
			} else {
				break;
			}
		}

		return bin2str(message).removeLast();
	}

} // namespace ad
