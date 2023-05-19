#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>


class Definitions {
public:
	struct Pair {
		std::string term;
		std::string definition;
	};
public:
	Definitions() = default;
	Definitions(std::ifstream& someStream) {
		srand(time(NULL));
		while (someStream.eof() == false) {
			std::string line;
			Pair term;
			std::getline(someStream, line);
			for (std::size_t i = 1; i < line.size() && i < line.size() - 1; ++i) {
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
	
	void add(const std::string& term, const std::string& definition) {
		this->defs.push_back(Pair{ term, definition });
	}

	void add(std::istream& in) {
		if (!in) {
			throw std::runtime_error("Cannot open stream");
		}
		while (in.eof() == false) {
			std::string line;
			Pair term;
			std::getline(in, line);
			for (std::size_t i = 1; i < line.size() && i < line.size() - 1; ++i) {
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

	std::size_t size() {
		return this->defs.size();
	}

	Pair getRandomTerm() {
		std::size_t randomIndex = rand() % this->defs.size();
		return this->defs[randomIndex];
	}
private:
	std::vector<Pair> defs;

};
