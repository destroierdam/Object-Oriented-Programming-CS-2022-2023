#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>


class Definitions {
public:
	
	Definitions() = default;
	/* Definitions(std::ifstream& someStream) {
		while (someStream.eof() == false) {
			std::string line;
			Pair term;
			std::getline(someStream, line);
			for (std::size_t i = 1; i < line.size() - 1; ++i) {
				if (line[i - 1] == ' ' &&
					line[i] == '-' &&
					line[i + 1] == ' ') {

					term.term = line.substr(0, i - 1);
					term.definition = line.substr(i + 2,
						line.size() - (i + 2) - 1);
					this->defs.push_back(term);
				}
			}
		}
	}
	*/
	
	void add(std::string term, std::string definition) {
		this->defs.emplace_back(term, definition);
	}

	std::size_t size() {
		return this->defs.size();
	}
private:
	struct Pair {
		std::string term;
		std::string definition;
	};
private:
	std::vector<Pair> defs;

};
