#ifndef MARKOVMATRIX_HPP
#define MARKOVMATRIX_HPP

#include <map>
#include <string>


class MarkovMatrix
{
public:
	MarkovMatrix(int length);
	~MarkovMatrix();
	
	void feed(std::string line);
	void reset(int length=0); // reset the matrix, length>0 -> set a new length
	std::map<std::string, int> hiccup(std::string& previous);
	
private:
	int length;
	std::map<std::string, std::map<std::string, int> > matrix;
};

#endif
