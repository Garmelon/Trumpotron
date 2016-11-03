#include "Markov.hpp"

#include <fstream>
#include <sstream>


Markov::~Markov()
{
	// does nothing
}


void Markov::eat(std::string filename) // gobble up a file
{
	std::ifstream ifs(filename);
	for (std::string line; std::getline(ifs, line); )
	{
		this->swallowLine(line);
	}
}


void Markov::swallow(std::string& text) // ingest text to later regurgitate
{
	std::istringstream iss(text);
	for (std::string line; std::getline(iss, line); )
	{
		this->swallowLine(line);
	}
}


std::string Markov::regurgitate(int lines, std::string start)
{
	// Not sure if it should return or just correct invalid input.
	// For now, just correct it.
	if (lines < 1) lines = 1;
	
	std::string answer = "";
	for (int i=0; i<lines; ++i) {
		answer += this->regurgitateLine(start) + "\n";
	}
	
	return answer;
}
