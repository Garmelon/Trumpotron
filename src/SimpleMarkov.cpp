#include "SimpleMarkov.hpp"

#include <chrono>
#include <fstream>
#include <stdexcept>





#include <iostream>

/*
class SimpleMarkov : public Markov
{
public:
	SimpleMarkov(int length=10);
	~SimpleMarkov();
	virtual ~SimpleMarkov();
	
	// loading and saving of internal state to files
	virtual void load(std::string filename);
	virtual void save(std::string filename);
	
	virtual void throwUp(); // empty the belly of previous text
	
private:
	virtual void swallowLine(std::string line);
	virtual std::string regurgitateLine(std::string start="");
};
*/
SimpleMarkov::SimpleMarkov(std::string filename)
{
	this->load(filename);
}

SimpleMarkov::SimpleMarkov(int length) :
	matrix(length),
	generator(std::chrono::system_clock::now().time_since_epoch().count())
{
	// do nothing
}


SimpleMarkov::~SimpleMarkov()
{
	// do nothing
}


/*
void SimpleMarkov::load(std::string filename)
{
	std::ifstream ifs(filename);
	std::string type, version;
	ifs >> type >> version;
	if (type != "s" || version != "0001") {
		throw std::invalid_argument("Wrong file type or version.");
	}
	
	ifs >> this->matrix;
	ifs.close();
}


void SimpleMarkov::save(std::string filename)
{
	std::ofstream ofs(filename);
	ofs << "s" << std::endl;
	ofs << "0001" << std::endl;
	ofs << this->matrix;
	ofs.close();
}
*/


void SimpleMarkov::load(std::string filename)
{
	std::ifstream ifs(filename);
	
	char gentype;
	int version;
	ifs >> gentype >> version;
	
	if (gentype == this->file_gentype and version == this->file_version) {
		ifs >> this->matrix;
	}
	
	ifs.close();
}


void SimpleMarkov::save(std::string filename)
{
	std::ofstream ofs(filename);
	
	// file type and version of format
	ofs << this->file_gentype << std::endl;
	ofs << this->file_version << std::endl;
	ofs << this->matrix;
	
	ofs.close();
}


void SimpleMarkov::throwUp()
{
	this->matrix.reset();
}


void SimpleMarkov::swallowLine(std::string& line)
{
	this->matrix.feed(line);
}


std::string SimpleMarkov::regurgitateLine(std::string start)
{
	std::string line = "";
	std::string next = "";
	do {
		// get the possible next characters from the matrix
		std::unordered_map<std::string, int> possibles = this->matrix.hiccup(line);
		
		// calculate sum of all possibilities
		int sum = 0;
		for (auto it : possibles) {
			sum += it.second;
		}
		
		// generate random number in that range
		int rand = std::uniform_int_distribution<>(1, sum)(this->generator);
		
		// iterate over possibilities again, this time picking the character chosen by rand
		sum = 0;
		for (auto it : possibles) {
			sum += it.second;
			if (rand <= sum) {
				next = it.first;
				break;
			}
		}
		
		// append the chosen character to the line
		line += next;
	} while (next != "");
	
	return line;
}
