#include <QApplication>
#include "window.h"
#include "algs/audio_helpers.h"
#include <string>
#include <iostream>
//int main(int argc, char *argv[]) {
//	QApplication app(argc, argv);
//	Window window;
//	return QApplication::exec();
//}

int main(){
	std::string path = "C:/temp/file_example_WAV_1MG.wav";
	ad::Wav_File wav_file = ad::read_wav_file(path);


	std::cout << "File size:" << wav_file.properties.chunk_size+8 << std::endl;
	std::cout << "Resource Exchange File Mark:" << std::string(wav_file.properties.chunkID, 4) << std::endl;
	std::cout << "Format:" << std::string(wav_file.properties.format, 4) << std::endl;
	std::cout << "Channels: " << wav_file.properties.num_channels << std::endl;
	std::cout << "Sample Rate: " << wav_file.properties.sample_rate << " Hz" << std::endl;
	std::cout << "Bits Per Sample: " << wav_file.properties.bits_per_sample << " bits" << std::endl;

}



