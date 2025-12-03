#include <string>
#include <fstream>
#include <vector>
#include "audio_helpers.h"
namespace ad{
	Wav_File read_wav_file(std::string path){

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
}
#include "audio_helpers.h"
