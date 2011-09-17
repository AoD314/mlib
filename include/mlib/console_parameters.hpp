
#ifndef __CLPARAMS_HPP__
#define __CLPARAMS_HPP__

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

namespace mlib
{
	//! Class for getting parameters from console 
	class ConsoleParameters
	{
		private:
			int argc;
			const char ** argv;
			std::string path;
			std::vector<std::string> get_aliases_from_string(std::string aliases);

		public:
			ConsoleParameters(int argc, const char ** argv)
			: argc(argc), argv(argv), path(argv[0])
			{
				size_t found = path.find_last_of("/\\");
				if ( std::string::npos != found )
				{
					path = path.substr(0, found) + "/";
				}
				else
				{
					path = "";
				}
			}

			ConsoleParameters (const ConsoleParameters& params); 
			ConsoleParameters & operator = (const ConsoleParameters& params);

			//! Get value
			/*!

			  \param param name of the parameter whose value we want to get out of the console parameters
			  \param def_value default value
			 
			*/
			template <typename T>
			T get(std::string param, T def_value = T());

			//! Get true if params was set, otherwise false 
			/*!
			
			 \param param name of the parameter 
			
			*/
			bool has(const std::string& param);

			int count_args() const;
			std::string operator [](const int index) const;

			std::string get_path();
	};

	std::ostream& operator << (std::ostream& out, const ConsoleParameters & params);
}

#endif

