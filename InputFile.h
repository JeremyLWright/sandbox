/** @file InputFile.h
 *
 * @brief Wrap the InputFile in a standard way so I can reuse this class for
 * other project.
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _INPUTFILE_H
#define _INPUTFILE_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "InputFileFormat.h"
using namespace std;

namespace cpp_practicum
{

class InputFile
{
public:
    InputFile(string filename, InputFileFormat& file_format);
    virtual ~InputFile(void);
    /**
	 * Move to the next Input Line
	 * @return True of the line parsed correctly and Format is valid, false on sentenial match, or failure.
	 */
    virtual bool next();
protected:
    vector<string> tokenize(string line);
private:
    InputFileFormat& _file_format;
    string _filename;
    ifstream* _inputfile;
};


}
#endif
