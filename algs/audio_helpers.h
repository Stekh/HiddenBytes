//
// Created by Lenovo on 03.12.2025.
//

#ifndef HIDDENBYTES_AUDIO_HELPERS_H
#define HIDDENBYTES_AUDIO_HELPERS_H
#include <QString>
#include <cstdint>
#include <string>
#include <vector>

namespace ad {
	struct Wav_File_Properties {
		// riff
		char chunkID[4];
		uint32_t chunk_size;
		char format[4];

		// ftm
		char sub_chunk1_ID[4];
		uint32_t sub_chunk1_size;
		uint16_t audio_format;
		uint16_t num_channels;
		uint32_t sample_rate;
		uint32_t byte_rate;
		uint16_t block_align;
		uint16_t bits_per_sample;

		char sub_chunk2_ID[4];
		uint32_t sub_chunk2_size;
	};

	struct Wav_File {
		Wav_File_Properties properties;
		std::vector<int16_t> data;
	};

	Wav_File read_wav_file(const std::string &path);
	std::string str2bin(const QString &str);
	QString bin2str(const std::string &bin_str);

} // namespace ad


#endif // HIDDENBYTES_AUDIO_HELPERS_H
