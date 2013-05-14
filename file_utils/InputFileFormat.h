/** 
 * @file InputFileFormat.h
 * 
 * @brief C++ File Utilities Library
 * 
 * @par 
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 * @addtogroup file_utils File Utilities
 * @{
 */
#ifndef INPUTFILEFORMAT_H_
#define INPUTFILEFORMAT_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace cpp_practicum
{

using std::string;

/**
 * Wrap the Input File format to allow the file format to change independent
 * of the Input File tokenizing and processing.
 *
 * @note This is technically an abstract class, not an interface.  The
 * distinction in C++ is value, but essentially if the class provides at
 * least 1 pure virtual function it is abstract, if the class provides all
 * pure virtual functions, it is an interface.
 */
class InputFileFormat
{
public:
	InputFileFormat();
	virtual ~InputFileFormat();
	/**
	 * Child classes choose what put_next_token means.
	 * This is intended to allow child classes to rename the generic tokens
	 * to something meaningful for their Input file.  It is the user's choice.
	 *
	 * @param token Next Item found on the input line.
	 */
	virtual void put_next_token(string token) = 0;

	/**
	 * Returns the stopping value for the InputFile.
	 *
	 * @note We allow child classes to override this function because it's
	 * possible that the sentenial value is not constant. A child class may
	 * want a dynamic stop condition.
	 *
	 * @return string representation of the stopping value.
	 */
	virtual string get_sentenial_value() const;

	/**
	 * Uses a C++ streams to convert a string representation to some other type.
	 *
	 * @param[out] t Target to save the converted value
	 * @param[in] s Source string to convert the value from.
	 * @param[in] f Format e.g.std::hex, or std::dec
	 * @return returns fail is conversion is not successful.
	 */
	template <typename T>
	bool from_string(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
	{
		std::istringstream iss(s, std::istringstream::in);
		return !(iss >> f >> t).fail();
	}


protected:
	string _sentenial_value;
};

}
/** @} */
#endif /* INPUTFILEFORMAT_H_ */

