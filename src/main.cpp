#include <iostream>
#include <string>
#include "SimpleMarkov.hpp"


int main(int argc, char* argv[])
{
	if (argc > 5 || argc < 3)
	{
		std::cout << "Usage: " << argv[0] << " <filename> [s][gsl] [...]" << std::endl;
		std::cout << "  s -- SimpleMarkov" << std::endl;
		std::cout << "  sg: [<number_of_paragraphs> [<length>]] -> generate from file" << std::endl;
		std::cout << "  ss: <filename> [<length>]               -> save" << std::endl;
		std::cout << "  sl: [<number_of_paragraphs>]            -> load and generate" << std::endl;
		return 1;
	}
	
	std::string filename = argv[1];
	std::string mode = argv[2];
	
	if (mode.substr(0, 1) == "s")
	{
		if (mode.substr(1, 1) == "g")
		{
			int paragraphs = 1;
			if (argc >= 4) paragraphs = std::stoi(argv[3]);
			int length = 10;
			if (argc >= 5) length = std::stoi(argv[4]);
			
			SimpleMarkov m(length);
			std::cout << "Processing file..." << std::endl;
			m.eat(filename);
			std::cout << "Generating text..." << std::endl;
			std::cout << m.regurgitate(paragraphs);
		}
		else if (mode.substr(1, 1) == "s")
		{
			if (argc < 4)
			{
				std::cout << "Error: No save file." << std::endl;
				return 3;
			}
			
			std::string savefile = argv[3];
			int length = 10;
			if (argc >= 5) length = std::stoi(argv[4]);
			
			SimpleMarkov m(length);
			std::cout << "Processing file..." << std::endl;
			m.eat(filename);
			std::cout << "Saving to file..." << std::endl;
			m.save(savefile);
		}
		else if (mode.substr(1, 1) == "l")
		{
			int paragraphs = 1;
			if (argc >= 4) paragraphs = std::stoi(argv[3]);
			
			SimpleMarkov m;
			std::cout << "Loading file..." << std::endl;
			try {
				m.load(filename);
			} catch (const std::invalid_argument e) {
				std::cout << "Error: " << e.what() << std::endl;
				return 4;
			}
			std::cout << "Generating text..." << std::endl;
			std::cout << m.regurgitate(paragraphs);
		}
	}
	else
	{
		std::cout << "Error: Incorrect mode." << std::endl;
		return 2;
	}
	
	return 0;
}
