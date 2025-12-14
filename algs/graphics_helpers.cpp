//
// Created by Stek-l on 28/11/2025.
//

#include "graphics_helpers.h"

namespace gr {
	ImageMeta verify_image(const std::ifstream &file) {
		return {false, 0, 0, std::span<RGBPixel>{}};
	}
} // namespace gr
