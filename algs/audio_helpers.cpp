#include <string>
#include <fstream>
#include <vector>
#include "audio_helpers.h"
#include <bitset>
#include <QString>
#include <QByteArray>
namespace ad{
	Wav_File read_wav_file(const std::string& path){

		Wav_File_Properties file_properties{};
		Wav_File full_file;
		std::ifstream file(path);
		if(file.is_open()){
			file.read(reinterpret_cast<char*>(&file_properties), sizeof(Wav_File_Properties));

			// Read wave data
			std::vector<int16_t> audio_data(file_properties.sub_chunk2_size / sizeof(int16_t) );
			file.read(reinterpret_cast<char*>(audio_data.data()), file_properties.sub_chunk2_size );
			file.close();  // Close audio file

			full_file.data = audio_data;
			full_file.properties = file_properties;
		}
		return full_file;
	}


	std::string str2bin(const QString &str) {
		std::string bin_str;
		QByteArray bytes = str.toUtf8();
		for (char byte : bytes) {
			bin_str += std::bitset<8>(static_cast<unsigned char>(byte)).to_string();
		}
		bin_str += "00000000";
		return bin_str;
	}


	QString bin2str(const std::string &bin_str) {
		QString res;
		for (size_t i = 0; i < bin_str.length(); i += 8) {
			uint8_t buf = 0;
			for (int16_t b = 7; b >= 0; b--) {
				buf += std::pow(2, 8 - (b + 1)) * (bin_str[static_cast<int16_t>(i) + b] - '0');
			}
			res += static_cast<char>(buf);
		}
		return res;
	}
}
