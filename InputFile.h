/** @file InputFile.h
 *
 * @brief Wrap the InputFile in a standard way so I can reuse this class for
 * other project.
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 *
 * @addtogroup file_utils File Utilities
 * @{
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
	/**
	 * Creates a new InputFile with a given file format.
	 * @param filename file to open.
	 * @param file_format Format object that describes the tokens of a line in the input file.
	 */
    InputFile(string filename, InputFileFormat& file_format);
    virtual ~InputFile(void);
    /**
	 * Move to the next Input Line
	 * @return True of the line parsed correctly and Format is valid, false on sentenial match, or failure.
	 */
    virtual bool next();
protected:
    /**
     * Breaks a whitespace delimited line into a vector of string tokens.
     * @param line whitespace delimited input line.
     * @return vector of string tokens.
     */
    vector<string> tokenize(string line);
private:
    /**
     * FileFormat object. The FileFormat must implement the InputFileFormat Interface.
     * InputFile feeds this object the tokens.  This allows parsing separately, from
     * type conversion.
     */
    InputFileFormat& _file_format;
    /**
     * The InputFile Name.
     */
    string _filename;
    /**
     * InputFile's stream.
     */
    ifstream* _inputfile;
};


}
/** @} */
#endif
