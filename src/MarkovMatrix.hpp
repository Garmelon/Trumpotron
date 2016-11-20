#ifndef MARKOVMATRIX_HPP
#define MARKOVMATRIX_HPP

#include <unordered_map>
#include <string>


class MarkovMatrix
{
public:
	MarkovMatrix();
	MarkovMatrix(char length);
	~MarkovMatrix();
	
	void feed(std::string& line);
	void reset(int length=0); // reset the matrix, length>0 -> set a new length
	std::unordered_map<std::string, int> hiccup(std::string& previous);
	
	// loading and saving of internal state to files
	virtual void load(std::istream& is);
	virtual void save(std::ostream& os);
	
private:
	char length = 0;
	std::unordered_map<std::string, std::unordered_map<std::string, int> > matrix;
	
	const char file_version = 1; // version of file format
};


std::istream& operator>>(std::istream& is, MarkovMatrix& matrix);
std::ostream& operator<<(std::ostream& os, MarkovMatrix& matrix);

#endif
