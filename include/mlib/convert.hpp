/*M/////////////////////////////////////////////////////////////////////////////
//
//    Copyright (c) 2012 Morozov Andrey (morozov.andrey.vmk@gmail.com)
//    All Rights Reserved.
//
//    Redistribution and use in source and binary forms, with or without
//    modification, are permitted provided that the following conditions
//    are met:
//        1. Redistributions of source code must retain the above copyright
//           notice, this list of conditions and the following disclaimer.
//        2. Redistributions in binary form must reproduce the above copyright
//           notice, this list of conditions and the following disclaimer in
//           the documentation and/or other materials provided with
//           the distribution.
//        3. The name of the author may not be used to endorse or promote
//           products derived from this software without specific prior
//           written permission.
//
//    THIS SOFTWARE IS PROVIDED BY "AS IS" AND ANY EXPRESS OR
//    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//    ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
//    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
//    THE POSSIBILITY OF SUCH DAMAGE.
//
//M*/

#ifndef __CONVERT_HPP__
#define __CONVERT_HPP__

#include <string>
#include <sstream>
#include <iomanip>

namespace mlib
{
    //! Convert bool value to "true" or "false"
    std::string to_str(bool t);

	//! Convert Type to std::string
	template <typename T>
	std::string to_str(const T & t, int align = 0, int precision = 0, char c = ' ')
	{
		std::stringstream ss;
		ss
			<< std::setiosflags(std::ios::fixed)
			<< std::setprecision(precision)
			<< std::setw(align)
			<< std::setfill(c)
			<< t;

		return ss.str();
	}

	//! Parse Type from std::string
	template <typename T>
	T from_str(const std::string & val, bool throw_exception = true, T defval = T())
	{
		std::istringstream iss(val);
		T t = T();
		bool result = iss >> t;
		if (!result && throw_exception) throw std::exception();
		if (!result && !throw_exception) return defval;
		return t;
	}


	//! Formating size to std::string
	std::string size_to_str(const size_t size_in_byte);

	//! Formating time to std::string
	std::string time_to_str(const double time_in_sec );
}

#endif

