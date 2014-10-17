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
#ifndef GCJFRAMEWORK_UTILITY_JSONWRITESTREAM_HPP_INCLUDED
#define GCJFRAMEWORK_UTILITY_JSONWRITESTREAM_HPP_INCLUDED

#include <rapidjson/rapidjson.h>
#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
namespace Utility {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class JsonWriteStream {

	/// @name Types
	/// @{
public:
	/// @}

	/// @name JsonWriteStream implementation
	/// @{
public:
	void Put(char c) {
		os_.put(c);
	}

	void PutN(char c, size_t n) {
		for (size_t i = 0; i < n; ++i)
		{
			Put(c);
		}
	}

	void Flush() {
		os_.flush();
	}

	size_t Tell() const {
		return (int)os_.tellp();
	}

	char Peek() const
	{
		RAPIDJSON_ASSERT(false);
	}

	char Take()
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
	JsonWriteStream(std::ostream& os)
	:	os_(os)
	{
	}
	/// @}

	/// @name Member Variables
	/// @{
private:
	std::ostream& os_;
	/// @}

};	// class JsonWriteStream

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace Utility
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace rapidjson {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
template<>
inline void PutN(GCJFramework::Utility::JsonWriteStream& stream, char c, size_t n) {
	stream.PutN(c, n);
}
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace rapidjson
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif	// GCJFRAMEWORK_UTILITY_JSONWRITESTREAM_HPP_INCLUDED
