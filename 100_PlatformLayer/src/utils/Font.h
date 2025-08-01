#pragma once

#include "src/utils/FierceStrings.h"

namespace Fierce {
	class Font {
	public:
		struct{
			std::string name="";
			int size = 0;
			bool bold=false;
			bool italic=false;
			std::string charset = "";
			bool unicode = false;
			int stretchH = 0;
			bool smooth = true;
			bool aa = true;
			int padding[4];
			int spacing[2];
		} info;

		struct {
			int lineHeight = 0;
			int base = 0;
			int scaleW = 0;
			int scaleH = 0;
			int pages = 0;
			bool packed = false;
		} common;

		struct {
			int id = 0;
			std::string file = "";
			int textureId=-1;
		} page;

		struct Char {
			int id = 0;
			int x=0;
			int y=0;
			int width = 0;
			int height = 0;
			int xoffset = 0;
			int yoffset = 0;
			int xadvance = 0;
			int page = 0;
			int chnl = 0;
		};

		struct{
			int count = 0;
			Char chars[150];
		} chars;

		struct Kerning {
			int first = 0;
			int second = 0;
			int amount = 0;
		};

		struct {
			int count = 0;
			Kerning kernings[200];
		} kernings;
	};
}