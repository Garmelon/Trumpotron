#ifndef SIMPLEMARKOV_HPP
#define SIMPLEMARKOV_HPP

#include "Markov.hpp"
#include "MarkovMatrix.hpp"

#include <random>
#include <string>


class SimpleMarkov : public Markov
{
public:
	SimpleMarkov(std::string filename);
	SimpleMarkov(int length=10);
	virtual ~SimpleMarkov();
	
	// loading and saving of internal state to files
	virtual void load(std::string filename);
	virtual void save(std::string filename);
	
	virtual void throwUp(); // empty the belly of previous text
	
private:
	virtual void swallowLine(std::string& line);
	virtual std::string regurgitateLine(std::string start="");
	
	MarkovMatrix matrix;
	std::default_random_engine generator;
	
	const char file_gentype = 's'; // type of the generator
	const char file_version = 1; // version of file format
};

#endif
