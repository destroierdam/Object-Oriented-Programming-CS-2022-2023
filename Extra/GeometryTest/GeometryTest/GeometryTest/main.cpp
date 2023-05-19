#include <iostream>
#include "Definitions.hpp"

int main() {
	system("chcp 1251");
	Definitions defs;
	std::cout << "Enter lectures you want to study\n";
	int lecture;

	while (std::cin >> lecture) {
		std::string filename("Unit");
		filename += std::to_string(lecture);
		filename += ".txt";
		std::ifstream file(filename);
		if (file.is_open() == false) {
			std::cerr << "File " << filename << " could not be opened.\n";
			continue;
		}
		defs.add(file);
	}
	std::cin.clear();
	while (true) {
		auto term = defs.getRandomTerm();
		std::cout << term.term << "\n";
		std::string answer;
		std::getline(std::cin, answer);
		if (answer == term.definition) {
			std::cout << "OK\n";
		}
		else if (answer == "exit") {
			break;
		}
		else {
			std::cout << term.definition << "\n";
		}
	}
}
