//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Google Code Jam Solution Framework
//
// Copyright (C) 2012-2014 Matthew Alan Gray
//
//  This software is licensed as described in the file license.txt, which you
//  should have received as part of this distribution.
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the terms described in the file license.txt.
//
//  @author Matthew Alan Gray <matthew.alan.gray@gmail.com>
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef GCJFRAMEWORK_UTILITY_JSONREADSTREAM_HPP_INCLUDED
#define GCJFRAMEWORK_UTILITY_JSONREADSTREAM_HPP_INCLUDED

#include <rapidjson/rapidjson.h>
#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
namespace Utility {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class JsonReadStream {

	/// @name Types
	/// @{
public:
	/// @}

	/// @name JsonReadStream implementation
	/// @{
public:
	char Peek() const 
	{
		return static_cast<char>(is_.peek());
	}

	char Take() const 
	{
		return static_cast<char>(is_.get());
	}

	size_t Tell() const 
	{
		return (int)is_.tellg();
	}

	void Put(char c) 
	{ 
		RAPIDJSON_ASSERT(false); 
	}

	void Flush() 
	{ 
		RAPIDJSON_ASSERT(false); 
	}

	char* PutBegin() 
	{ 
		RAPIDJSON_ASSERT(false); 
		return 0; 
	}

	size_t PutEnd(char*) 
	{ 
		RAPIDJSON_ASSERT(false); 
		return 0; 
	}
	/// @}

	/// @name 'Structors
	/// @{
public:
	JsonReadStream(std::istream& is) 
	: is_(is) 
	{
	}
	/// @}

	/// @name Member Variables
	/// @{
private:
	std::istream& is_;
	/// @}

};	// class JsonReadStream

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Utility
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_UTILITY_JSONREADSTREAM_HPP_INCLUDED
