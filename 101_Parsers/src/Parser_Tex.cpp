#include "Parser_Tex.h"

#include "stb_image.h"

namespace Fierce {

	Parser_Tex::Parser_Tex(std::string directory){
		m_directory = directory;
	}

	unsigned char* Parser_Tex::parseFile(std::string filename, int* width, int* height, int* numChannels){
		std::string path = m_directory;
		path.append(filename);
		return stbi_load(path.c_str(), width, height, numChannels, STBI_rgb_alpha);
	}

	void Parser_Tex::freeData(unsigned char* pixels){
		stbi_image_free(pixels);
	}
}