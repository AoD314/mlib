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

#ifndef __COMMANDLINEPARSER_HPP__
#define __COMMANDLINEPARSER_HPP__

#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <exception>
#include <algorithm>
#include <iostream>

#include "mlib/algorithms.hpp"
#include "mlib/convert.hpp"

namespace mlib
{
    class Params
    {
        public:
            Params();
            std::string help_message;
            std::string def_value;
            std::vector<std::string> keys;
            int number;
    };

	bool cmp_params(const Params & p1, const Params & p2);

	class CommandLineParser
	{
		public:
            CommandLineParser(int argc, char ** argv, const std::string keys);

			std::string get_path_to_application();

			template <typename T>
			T get(const std::string& name, bool space_delete = true)
			{
				for (size_t i = 0; i < data.size(); i++)
				{
					for (size_t j = 0; j < data[i].keys.size(); j++)
					{
						if (name.compare(data[i].keys[j]) == 0)
						{
							std::string v = data[i].def_value;
							if (space_delete == true) v = cat_string(v);
							return from_str<T>(v);
						}
					}
				}
				error = true;
				error_message += "Unknown parametes " + name + "\n";
				return T();
			}

			template <typename T>
			T get(int index, bool space_delete = true)
			{
				for (size_t i = 0; i < data.size(); i++)
				{
					if (data[i].number == index)
					{
						std::string v = data[i].def_value;
						if (space_delete == true) v = cat_string(v);
						return from_str<T>(v);
					}
				}
				error = true;
				error_message += "Unknown parametes #" + to_str<int>(index) + "\n";
				return T();
			}

			bool has(const std::string& name);

			bool check();

			void set_error(std::string msg);

			void about(std::string message);

			void print_help();

		protected:
			bool error;
			std::string error_message;
			std::string about_message;

            std::string path_to_app;
			std::string app_name;

			std::vector<Params> data;

			void apply_params(std::string key, std::string value);
			void apply_params(int i, std::string value);

			void sort_params();

	};

}

#endif

