#pragma once

#include <string>

#include "src/PlatformLayer/utils/Font.h"

#include "GraphicsContext.h"

namespace Fierce{

	class GUIHelper {
	public:

		static inline float getStringWidth(std::string string, std::string fontString, int size,GraphicsContext* g) {
			Font* font = g->getFont(fontString);
			char letter;
			Font::Char character;
			float cursor = 0.0f;
			int kerning = 0;
			float sizeFactor = (float)size / (float)font->info.size;

			for (int i = 0; i < string.size(); i++) {
				letter = string[i];
				character = font->chars.chars[letter];

				//Search for kerning
				if (i < string.size() - 1) {
					for (int j = 0; j < font->kernings.count; j++) {
						Font::Kerning kern = font->kernings.kernings[j];
						if (kern.first == string[i] && kern.second == string[i + 1]) {
							kerning = kern.amount;
						}
					}
				}

				if (i < string.size() - 1) {
					cursor += (character.xadvance - 2 * font->info.padding[0] - font->info.spacing[0]) * sizeFactor + kerning * sizeFactor;
				}
				else {
					cursor += (character.width- font->info.padding[0]) * sizeFactor;
				}

				kerning = 0;
			}

			return cursor;
		}

		static inline float getStringHeight(std::string string, std::string fontString, int size, GraphicsContext* g) {
			Font* font = g->getFont(fontString);
			char letter;
			Font::Char character;
			float sizeFactor = (float)size / (float)font->info.size;
			float minY=0.0f;
			float maxY=0.0f;

			for (int i = 0; i < string.size(); i++) {
				letter = string[i];
				character = font->chars.chars[letter];

				float y1 = character.yoffset * sizeFactor;
				float y2 = (character.yoffset + character.height) * sizeFactor;

				if (y1 < minY) {
					minY = y1;
				}

				if (y2 > maxY) {
					maxY = y2;
				}
			}

			return maxY - minY-2* font->info.padding[0]*sizeFactor;
		}
	};
}