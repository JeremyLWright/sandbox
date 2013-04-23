/**
 * @file InputFile.cpp
 *
 * @brief C++ File Utilities Library
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 * @addtogroup file_utils File Utilities
 * @{
 */
#include "InputFile.h"
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

cpp_practicum::InputFile::InputFile(string filename, InputFileFormat& file_format):
		_file_format(file_format)
{
    this->_filename = filename;
    _inputfile = new ifstream(this->_filename.c_str(), ifstream::in);
}

bool cpp_practicum::InputFile::next()
{
	string line;
	std::stringstream ss;
	ss << _file_format.get_sentenial_value();
	getline(*_inputfile, line);

	/** If we find the sentenial value, we're done.
	 *
	 * @note This conditional is kinda weird, find() returns the index of the
	 * found string. find() returns npos i.e. no-position meaning that the index
	 * is beyond the string.  This an awkward of stating that it didn't find the
	 * requested string.  Said another way:
	 * if(find()'s index is outside the bounds of string)...
	 */

	if(line.find(ss.str()) != string::npos)
	{
		return false;
	}
	else
	{
		vector<string> tokens = tokenize(line);
		// We've separated the object into tokens, so feed it to the formatter.
		for(vector<string>::iterator token = tokens.begin();
				token != tokens.end();
				++token)
		{
			 _file_format.put_next_token(*token);
		}
		return true;
	}
}

vector<string> cpp_practicum::InputFile::tokenize(string line)
{

	// construct a stream from the string
	stringstream strstr(line);

	// use stream iterators to copy the stream to the vector as whitespace separated strings
	istream_iterator<string> it(strstr);
	istream_iterator<string> end;
	vector<string> results(it, end);

	return results;
}


cpp_practicum::InputFile::~InputFile(void)
{
}
/** @} */
