#include <iostream>
#include <string>
#include "SimpleMarkov.hpp"


int main(int argc, char* argv[])
{
	if (argc > 5 || argc < 3) {
		std::cout << "Usage: " << argv[0] << "<filename> [s] [...]" << std::endl;
		std::cout << "  s: [<number_of_paragraphs> [<length>]] -> SimpleMarkov" << std::endl;
		return 1;
	}
	
	std::string filename = argv[1];
	std::string mode = argv[2];
	
	if (mode == "s") {
		int paragraphs = 1;
		if (argc >= 4) paragraphs = std::stoi(argv[3]);
		int length = 10;
		if (argc >= 5) length = std::stoi(argv[4]);
		
		SimpleMarkov m(length);
		m.eat(filename);
		std::cout << m.regurgitate(paragraphs);
	} else {
		std::cout << "Error: Incorrect mode." << std::endl;
		return 2;
	}
	
	return 0;
}
