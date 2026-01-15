//
// Created by stek on 15.01.2026.
//

#include <bitset>

#include "utils.h"

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

std::string str2bin(const std::string &str) {
	std::string bin_str;
	for (size_t i = 0; i < str.length(); i++) {
		bin_str += std::bitset<8>(str[i]).to_string();
	}
	// add the null terminator
	bin_str += "00000000";

	return bin_str;
}
