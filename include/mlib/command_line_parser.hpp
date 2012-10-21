
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
			std::string help_message;
			std::string def_value;
			std::vector<std::string> keys;
			int number;
	};

	bool cmp_params(const Params & p1, const Params & p2);

	class CommandLineParser
	{
		public:
			CommandLineParser(int argc, char ** argv, std::string keys);

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

