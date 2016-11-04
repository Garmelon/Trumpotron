#include "MarkovMatrix.hpp"

#include <algorithm> // for std::max


MarkovMatrix::MarkovMatrix(int length)
{
	this->length = length;
}


MarkovMatrix::~MarkovMatrix()
{
	// do nothing
}


void MarkovMatrix::feed(std::string& line)
{
	for (int i=0; i<=int(line.size()); ++i) {
		int pos = std::max(i-this->length, 0);
		int len = i - pos;
		std::string before = line.substr(pos, len);
		std::string current = line.substr(i, 1);
		this->matrix[before][current] += 1;
	}
}


void MarkovMatrix::reset(int length)
{
	this->matrix.clear();
	
	if (length > 0) {
		this->length = length;
	}
}


std::unordered_map<std::string, int> MarkovMatrix::hiccup(std::string& previous)
{
	int size = previous.size();
	int pos = std::max(size-this->length, 0);
	int len = size - pos;
	std::string before = previous.substr(pos, len);
	return this->matrix.at(before);
}
