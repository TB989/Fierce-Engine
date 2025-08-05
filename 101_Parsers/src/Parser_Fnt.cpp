#include "Parser_Fnt.h"

#include "src/utils/FierceStrings.h"

#define KEY m_tokens[0]
#define VALUE m_tokens[1]

namespace Fierce {
	Parser_Fnt::Parser_Fnt(TextFileReader* textFileReader) {
		m_fileReader = textFileReader;
	}

	void Parser_Fnt::parseFile(std::string filename,Font* font) {
		m_fileReader->openFile(filename);

		std::string line;
		while (m_fileReader->readNextLine(line)) {
			trim(line);

			//Empty line
			if (isEmptyLine(line)) continue;

			//Comment starts with //
			if (isCommentLine(line)) continue;

			//Valid line
			parseLine(line, font);
		}

		m_fileReader->closeFile();
	}

	void Parser_Fnt::parseLine(std::string line, Font* font) {
		m_lineParts=split(line, ' ');
		std::string lineType=m_lineParts[0];
		trim(lineType);

		if (lineType == "info") {
			parseLineInfo(font);
		}
		else if (lineType == "common") {
			parseLineCommon(font);
		}
		else if (lineType == "page") {
			parseLinePage(font);
		}
		else if (lineType == "chars") {
			parseLineChars(font);
		}
		else if (lineType == "char") {
			parseLineChar(font);
		}
		else if (lineType == "kernings") {
			parseLineKernings(font);
		}
		else if (lineType == "kerning") {
			parseLineKerning(font);
			numKernings++;
		}
		else {
			return;
		}
	}

	void Parser_Fnt::parseLineInfo(Font* font){
		for (std::string token : m_lineParts) {
			if (token.empty()) {
				continue;
			}

			if (!lineContains(token, "=")) {
				continue;
			}

			m_tokens = split(token, '=');
			trim(KEY);
			trim(VALUE);

			if (KEY == "face") {
				font->info.name = asString(VALUE);
			}
			if (KEY == "size") {
				font->info.size = asInt(VALUE);
			}
			if (KEY == "bold") {
				font->info.bold = asBool(VALUE);
			}
			if (KEY == "italic") {
				font->info.italic = asBool(VALUE);
			}
			if (KEY == "charset") {
				font->info.charset = asString(VALUE);
			}
			if (KEY == "unicode") {
				font->info.unicode = asBool(VALUE);
			}
			if (KEY == "stretchH") {
				font->info.stretchH = asInt(VALUE);
			}
			if (KEY == "smooth") {
				font->info.smooth = asBool(VALUE);
			}
			if (KEY == "aa") {
				font->info.aa = asBool(VALUE);
			}
			if (KEY == "padding") {
				font->info.padding[0] = asArray(VALUE, 0);
				font->info.padding[1] = asArray(VALUE, 1);
				font->info.padding[2] = asArray(VALUE, 2);
				font->info.padding[3] = asArray(VALUE, 3);
			}
			if (KEY == "spacing") {
				font->info.spacing[0] = asArray(VALUE, 0);
				font->info.spacing[1] = asArray(VALUE, 1);
			}
		}
	}

	void Parser_Fnt::parseLineCommon(Font* font){
		for (std::string token : m_lineParts) {
			if (token.empty()) {
				continue;
			}

			if (!lineContains(token, "=")) {
				continue;
			}

			m_tokens = split(token, '=');
			trim(KEY);
			trim(VALUE);

			if (KEY == "lineHeight") {
				font->common.lineHeight = asInt(VALUE);
			}
			if (KEY == "base") {
				font->common.base = asInt(VALUE);
			}
			if (KEY == "scaleW") {
				font->common.scaleW = asInt(VALUE);
			}
			if (KEY == "scaleH") {
				font->common.scaleH = asInt(VALUE);
			}
			if (KEY == "pages") {
				font->common.pages = asInt(VALUE);
			}
			if (KEY == "packed") {
				font->common.packed = asBool(VALUE);
			}
		}
	}

	void Parser_Fnt::parseLinePage(Font* font){
		for (std::string token : m_lineParts) {
			if (token.empty()) {
				continue;
			}

			if (!lineContains(token, "=")) {
				continue;
			}

			m_tokens = split(token, '=');
			trim(KEY);
			trim(VALUE);

			if (KEY == "id") {
				font->page.id = asInt(VALUE);
			}
			if (KEY == "file") {
				font->page.file = asString(VALUE);
			}
		}
	}

	void Parser_Fnt::parseLineChars(Font* font){
		for (std::string token : m_lineParts) {
			if (token.empty()) {
				continue;
			}

			if (!lineContains(token, "=")) {
				continue;
			}

			m_tokens = split(token, '=');
			trim(KEY);
			trim(VALUE);

			if (KEY == "count") {
				font->chars.count = asInt(VALUE);
			}
		}
	}

	void Parser_Fnt::parseLineChar(Font* font){
		int charId;

		for (std::string token : m_lineParts) {
			if (token.empty()) {
				continue;
			}

			if (!lineContains(token, "=")) {
				continue;
			}

			m_tokens = split(token, '=');
			trim(KEY);
			trim(VALUE);

			if (KEY == "id") {
				charId= asInt(VALUE);
				font->chars.chars[charId].id = charId;
			}
			if (KEY == "x") {
				font->chars.chars[charId].x = asInt(VALUE);
			}
			if (KEY == "y") {
				font->chars.chars[charId].y = asInt(VALUE);
			}
			if (KEY == "width") {
				font->chars.chars[charId].width = asInt(VALUE);
			}
			if (KEY == "height") {
				font->chars.chars[charId].height = asInt(VALUE);
			}
			if (KEY == "xoffset") {
				font->chars.chars[charId].xoffset = asInt(VALUE);
			}
			if (KEY == "yoffset") {
				font->chars.chars[charId].yoffset = asInt(VALUE);
			}
			if (KEY == "xadvance") {
				font->chars.chars[charId].xadvance = asInt(VALUE);
			}
			if (KEY == "page") {
				font->chars.chars[charId].page = asInt(VALUE);
			}
			if (KEY == "chnl") {
				font->chars.chars[charId].chnl = asInt(VALUE);
			}
		}
	}

	void Parser_Fnt::parseLineKernings(Font* font){
		for (std::string token : m_lineParts) {
			if (token.empty()) {
				continue;
			}

			if (!lineContains(token, "=")) {
				continue;
			}

			m_tokens = split(token, '=');
			trim(KEY);
			trim(VALUE);

			if (KEY == "count") {
				font->kernings.count = asInt(VALUE);
			}
		}
	}

	void Parser_Fnt::parseLineKerning(Font* font){
		for (std::string token : m_lineParts) {
			if (token.empty()) {
				continue;
			}

			if (!lineContains(token, "=")) {
				continue;
			}

			m_tokens = split(token, '=');
			trim(KEY);
			trim(VALUE);

			if (KEY == "first") {
				font->kernings.kernings[numKernings].first = asInt(VALUE);
			}
			if (KEY == "second") {
				font->kernings.kernings[numKernings].second = asInt(VALUE);
			}
			if (KEY == "amount") {
				font->kernings.kernings[numKernings].amount = asInt(VALUE);
			}
		}
	}
}