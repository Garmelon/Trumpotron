#include "MarkovMatrix.hpp"

#include <algorithm> // for std::max
#include <iostream>
#include <stdexcept>


MarkovMatrix::MarkovMatrix()
{
	// do nothing
}


MarkovMatrix::MarkovMatrix(char length)
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


void MarkovMatrix::load(std::istream& is)
{
	char file_version;
	is.read(&file_version, sizeof(char));
}


void MarkovMatrix::save(std::ostream& os)
{
	os << this->file_version << std::endl;
	
	os << this->matrix.size() << std::endl;
	for (auto map : this->matrix) {
		os << map.first << std::endl;
		
		os << map.second.size() << std::endl;
		for (auto character : map.second) {
			os << character.first << std::endl;
			os << character.second << std::endl;
		}
	}
}


std::istream& operator>>(std::istream& is, MarkovMatrix& matrix)
{
	matrix.load(is);
	return is;
}


std::ostream& operator<<(std::ostream& os, MarkovMatrix& matrix)
{
	matrix.save(os);
	return os;
}
