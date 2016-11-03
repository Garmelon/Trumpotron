#ifndef MARKOV_HPP
#define MARKOV_HPP

#include <string>


class Markov
{
public:
	virtual ~Markov();
	
	// loading and saving of internal state to files
	virtual void load(std::string filename) =0;
	virtual void save(std::string filename) =0;
	
	void eat(std::string filename); // gobble up a file
	void swallow(std::string& text); // ingest text to later regurgitate
	virtual void throwUp() =0; // empty the belly of previous text
	
	// generate new text from previously eaten text
	std::string regurgitate(int lines=1, std::string start="");
	
protected:
	virtual void swallowLine(std::string line) =0;
	virtual std::string regurgitateLine(std::string start="") =0;
};

#endif
