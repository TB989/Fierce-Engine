#pragma once

#include "src/Common.h"

struct Character {
	int x;
	int y;
	int width;
	int height;
	int xoffset;
	int yoffset;
	int advance;
};

struct Kerning {
	int first;
	int second;
	int amount;
};

class Font {
private:
	std::string name;
	int size;
	bool bold;
	bool italic;
	int PADDING = 8;
	int lineHeight = 98;
	int base = 56;
	int textureWidth = 512;
	int textureHeight = 512;
	int numChars;
	Character* chars;
	int numKernings;
	Kerning* kernings;
};