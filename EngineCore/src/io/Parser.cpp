#include "Parser.h"

#include <fstream>
#include <iostream>

namespace Fierce {

	std::map<std::string, std::string> Parser::parsePropertiesFile(std::string filename){
		std::string line;
		std::vector<std::string> tokens;
		std::ifstream myfile(filename);
		std::map<std::string, std::string> settings;

		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				trim(line);

				//Empty line
				if (line.empty()) {
					continue;
				}

				//Comment
				if (startsWith(line, "//")) {
					continue;
				}

				//Invalid line
				if (!contains(line, "=")) {
					continue;
				}

				//Valid line
				else {
					tokens = split(line, '=');
					trim(tokens[0]);
					trim(tokens[1]);
					settings.insert(std::make_pair(tokens[0], tokens[1]));
				}
			}
			myfile.close();
		}

		return settings;
	}

	Font* Parser::parseFontFile(std::string filename) {
		std::string line;
		std::string lineType;
		std::vector<std::string> tokens1;
		std::vector<std::string> tokens2;
		std::ifstream myfile(filename);
		Font* font = new Font();
		int charId = -1;
		int kCounter = -1;

		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				trim(line);

				//Empty line
				if (line.empty()) {
					continue;
				}

				//Split line at " "
				tokens1 = split(line, ' ');

				//Find line type
				trim(tokens1[0]);
				lineType = tokens1[0];

				//Parse depnding on line type
				if (lineType=="info") {
					for (std::string token : tokens1) {
						if (token.empty()) {
							continue;
						}

						tokens2 = split(token, '=');
						if (tokens2.size()!=2){
							continue;
						}

						trim(tokens2[0]);
						trim(tokens2[1]);

						if (tokens2[0]=="face") {
							font->info.name = tokens2[1].substr(1,tokens2[1].size()-2);
							//std::cout << font->info.name << std::endl;
						}
						else if (tokens2[0] == "size") {
							font->info.size = std::stoi(tokens2[1]);
							//std::cout << font->info.size << std::endl;
						}
						else if (tokens2[0] == "bold") {
							if (tokens2[1]=="0") {
								font->info.bold = false;
							}
							else {
								font->info.bold = true;
							}
							//std::cout << font->info.bold << std::endl;
						}
						else if (tokens2[0] == "italic") {
							if (tokens2[1] == "0") {
								font->info.italic = false;
							}
							else {
								font->info.italic = true;
							}
							//std::cout << font->info.italic << std::endl;
						}
						else if (tokens2[0] == "charset") {
							font->info.charset = tokens2[1].substr(1, tokens2[1].size() - 2);
							//std::cout << font->info.charset << std::endl;
						}
						else if (tokens2[0] == "unicode") {
							if (tokens2[1] == "0") {
								font->info.unicode = false;
							}
							else {
								font->info.unicode = true;
							}
							//std::cout << font->info.unicode << std::endl;
						}
						else if (tokens2[0] == "stretchH") {
							font->info.stretchH = std::stoi(tokens2[1]);
							//std::cout << font->info.stretchH << std::endl;
						}
						else if (tokens2[0] == "smooth") {
							if (tokens2[1] == "0") {
								font->info.smooth = false;
							}
							else {
								font->info.smooth = true;
							}
							//std::cout << font->info.smooth << std::endl;
						}
						else if (tokens2[0] == "aa") {
							if (tokens2[1] == "0") {
								font->info.aa = false;
							}
							else {
								font->info.aa = true;
							}
							//std::cout << font->info.aa << std::endl;
						}
						else if (tokens2[0] == "padding") {
							std::vector<std::string> tokens3;
							tokens3 = split(tokens2[1],',');
							trim(tokens3[0]);
							trim(tokens3[1]);
							trim(tokens3[2]);
							trim(tokens3[3]);
							font->info.padding[0] = std::stoi(tokens3[0]);
							font->info.padding[1] = std::stoi(tokens3[1]);
							font->info.padding[2] = std::stoi(tokens3[2]);
							font->info.padding[3] = std::stoi(tokens3[3]);
							//std::cout << font->info.padding[0] << std::endl;
							//std::cout << font->info.padding[1] << std::endl;
							//std::cout << font->info.padding[2] << std::endl;
							//std::cout << font->info.padding[3] << std::endl;
						}
						else if (tokens2[0] == "spacing") {
							std::vector<std::string> tokens3;
							tokens3 = split(tokens2[1], ',');
							trim(tokens3[0]);
							trim(tokens3[1]);
							font->info.spacing[0] = std::stoi(tokens3[0]);
							font->info.spacing[1] = std::stoi(tokens3[1]);
							//std::cout << font->info.spacing[0] << std::endl;
							//std::cout << font->info.spacing[1] << std::endl;
						}
						else {
							//std::cout << lineType << std::endl;
						}
					}
				}
				else if(lineType=="common") {
					for (std::string token : tokens1) {
						if (token.empty()) {
							continue;
						}

						tokens2 = split(token, '=');
						if (tokens2.size() != 2) {
							continue;
						}

						trim(tokens2[0]);
						trim(tokens2[1]);

						if (tokens2[0] == "lineHeight") {
							font->common.lineHeight = std::stoi(tokens2[1]);
							//std::cout << font->common.lineHeight << std::endl;
						}
						else if (tokens2[0] == "base") {
							font->common.base = std::stoi(tokens2[1]);
							//std::cout << font->common.base << std::endl;
						}
						else if (tokens2[0] == "scaleW") {
							font->common.scaleW = std::stoi(tokens2[1]);
							//std::cout << font->common.scaleW << std::endl;
						}
						else if (tokens2[0] == "scaleH") {
							font->common.scaleH = std::stoi(tokens2[1]);
							//std::cout << font->common.scaleH << std::endl;
						}
						else if (tokens2[0] == "pages") {
							font->common.pages = std::stoi(tokens2[1]);
							//std::cout << font->common.pages << std::endl;
						}
						else if (tokens2[0] == "packed") {
							if (tokens2[1] == "0") {
								font->common.packed = false;
							}
							else {
								font->common.packed = true;
							}
							//std::cout << font->common.packed << std::endl;
						}
						else {
							//std::cout << lineType << std::endl;
						}
					}
				}
				else if (lineType == "page") {
					for (std::string token : tokens1) {
						if (token.empty()) {
							continue;
						}

						tokens2 = split(token, '=');
						if (tokens2.size() != 2) {
							continue;
						}

						trim(tokens2[0]);
						trim(tokens2[1]);

						if (tokens2[0] == "id") {
							font->page.id = std::stoi(tokens2[1]);
							//std::cout << font->page.id << std::endl;
						}
						else if (tokens2[0] == "file") {
							font->page.file = tokens2[1].substr(1, tokens2[1].size() - 2);
							//std::cout << font->page.file << std::endl;
						}
						else {
							//std::cout << lineType << std::endl;
						}
					}
				}
				else if (lineType == "chars") {
					for (std::string token : tokens1) {
						if (token.empty()) {
							continue;
						}

						tokens2 = split(token, '=');
						if (tokens2.size() != 2) {
							continue;
						}

						trim(tokens2[0]);
						trim(tokens2[1]);

						if (tokens2[0] == "count") {
							font->chars.count = std::stoi(tokens2[1]);
							//std::cout << font->chars.count << std::endl;
						}
						else {
							//std::cout << lineType << std::endl;
						}

					}
				}
				else if (lineType == "char") {
					for (std::string token : tokens1) {
						if (token.empty()) {
							continue;
						}

						tokens2 = split(token, '=');
						if (tokens2.size() != 2) {
							continue;
						}

						trim(tokens2[0]);
						trim(tokens2[1]);

						if (tokens2[0] == "id") {
							charId= std::stoi(tokens2[1]);
							font->chars.chars[charId].id = charId;
							//std::cout << font->chars.chars[charId].id << std::endl;
						}
						else if (tokens2[0] == "x") {
							font->chars.chars[charId].x = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].x << std::endl;
						}
						else if (tokens2[0] == "y") {
							font->chars.chars[charId].y = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].y << std::endl;
						}
						else if (tokens2[0] == "width") {
							font->chars.chars[charId].width = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].width << std::endl;
						}
						else if (tokens2[0] == "height") {
							font->chars.chars[charId].height = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].height << std::endl;
						}
						else if (tokens2[0] == "xoffset") {
							font->chars.chars[charId].xoffset = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].xoffset << std::endl;
						}
						else if (tokens2[0] == "yoffset") {
							font->chars.chars[charId].yoffset = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].yoffset << std::endl;
						}
						else if (tokens2[0] == "xadvance") {
							font->chars.chars[charId].xadvance = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].xadvance << std::endl;
						}
						else if (tokens2[0] == "page") {
							font->chars.chars[charId].page = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].page << std::endl;
						}
						else if (tokens2[0] == "chnl") {
							font->chars.chars[charId].chnl = std::stoi(tokens2[1]);
							//std::cout << font->chars.chars[charId].chnl << std::endl;
						}
						else {
							//std::cout << lineType << std::endl;
						}
					}
				}
				else if (lineType == "kernings") {
					for (std::string token : tokens1) {
						if (token.empty()) {
							continue;
						}

						tokens2 = split(token, '=');
						if (tokens2.size() != 2) {
							continue;
						}

						trim(tokens2[0]);
						trim(tokens2[1]);

						if (tokens2[0] == "count") {
							font->kernings.count = std::stoi(tokens2[1]);
							//std::cout << font->kernings.count << std::endl;
						}
						else {
							//std::cout << lineType << std::endl;
						}

					}
				}
				else if (lineType == "kerning") {
					kCounter++;
					for (std::string token : tokens1) {
						if (token.empty()) {
							continue;
						}

						tokens2 = split(token, '=');
						if (tokens2.size() != 2) {
							continue;
						}

						trim(tokens2[0]);
						trim(tokens2[1]);

						if (tokens2[0] == "first") {
							font->kernings.kernings[kCounter].first = std::stoi(tokens2[1]);
							//std::cout << font->kernings.kernings[kCounter].first << std::endl;
						}
						else if (tokens2[0] == "second") {
							font->kernings.kernings[kCounter].second = std::stoi(tokens2[1]);
							//std::cout << font->kernings.kernings[kCounter].second << std::endl;
						}
						else if (tokens2[0] == "amount") {
							font->kernings.kernings[kCounter].amount = std::stoi(tokens2[1]);
							//std::cout << font->kernings.kernings[kCounter].amount << std::endl;
						}
						else {
							//std::cout << lineType << std::endl;
						}
					}
				}
				else {
					continue;
				}
			}
			myfile.close();
		}

		return font;
	}

}//end namespace