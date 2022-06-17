#include "Parser.h"

#include <fstream>  

std::map<std::string, std::string> Parser::parsePropertiesFile(std::string filename) {
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

std::vector<char> Parser::readBinary(std::string filename){
	std::ifstream file(filename, std::ios::binary);

	if (file.is_open()) {
		std::vector<char> sourceCode((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		file.close();
		return sourceCode;
	}
	else {
		LOGGER->error("Failed to read shader: %s",filename);
	}

	return std::vector<char>();
}

std::vector<char> Parser::readText(std::string filename){
	std::ifstream file(filename);

	if (file.is_open()) {
		std::vector<char> sourceCode((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		file.close();
		return sourceCode;
	}
	else {
		LOGGER->error("Failed to read shader: %s", filename);
	}

	return std::vector<char>();
}