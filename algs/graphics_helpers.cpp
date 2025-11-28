//
// Created by Stek-l on 28/11/2025.
//

#include "graphics_helpers.h"

namespace gr {
	QImage load_image(QString filepath){
		QImage image;
		if (!image.load(filepath)) {
			throw std::runtime_error("Couldn't open image");
		}

		return image;
	}
}
