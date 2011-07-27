
#ifndef __CLPARAMS_HPP__
#define __CLPARAMS_HPP__

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

namespace mlib
{
	class ConsoleParameters
	{
		private:
			int argc;
			const char ** argv;
			std::string path;
			std::vector<std::string> get_aliases_from_string(std::string aliases);

		public:
			ConsoleParameters(int argc, const char ** argv): argc(argc), argv(argv), path(argv[0])
			{
					path = path.substr(0, path.find_last_of("/\\"));
			}

			bool has(const std::string& param);

			std::string get_path();

			template <typename T>
			T get(std::string param, T def_value = T());

			int count_args() const;
			std::string operator [](const int index) const;
	};

	std::ostream& operator << (std::ostream& out, const ConsoleParameters & params);
}

#endif

