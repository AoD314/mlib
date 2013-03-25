#include <exception>

#include "mlib/command_line_parser.hpp"
#include "mlib/convert.hpp"

namespace mlib
{
	bool cmp_params(const Params & p1, const Params & p2)
	{
		if (p1.number > p2.number)
			return true;

		if (p1.number == -1 && p2.number == -1)
		{
			if (p1.keys[0].compare(p2.keys[0]) > 0)
			{
				return true;
			}
		}

		return false;
	}

	CommandLineParser::CommandLineParser(int argc, char ** argv, std::string keys):
		error(false), error_message("")
	{
		// path to application
		size_t pos_s = std::string(argv[0]).find_last_of("/\\");
		if (pos_s == std::string::npos)
		{
			path_to_app = "";
			app_name = std::string(argv[0]);
		}
		else
		{
			path_to_app = std::string(argv[0]).substr(0, pos_s);
			app_name = std::string(argv[0]).substr(pos_s + 1, std::string(argv[0]).length() - pos_s);
		}

		// parse keys
		std::vector<std::string> k = split_range_string(keys, '{', '}');

		int jj = 0;
		for (size_t i = 0; i < k.size(); i++)
		{
			std::vector<std::string> l = split_string(k[i], '|', true);
			Params p;
			p.keys = split_string(l[0]);
			p.def_value = l[1];
			p.help_message = cat_string(l[2]);
			p.number = -1;
			if (p.keys.size() <= 0)
			{
				error = true;
				error_message = "Field KEYS could not be empty\n";
			}
			else
			{
				if (p.keys[0][0] == '@')
				{
					p.number = jj;
					jj++;
				}

				data.push_back(p);
			}

		}

		// parse argv
		jj = 0;
		for (int i = 1; i < argc; i++)
		{
			std::string s = std::string(argv[i]);

			if (s.find('=') != std::string::npos && s.find('=') < s.length())
			{
                std::vector<std::string> k_v = split_string(s, '=', true);
				for (int h = 0; h < 2; h++)
				{
					if (k_v[0][0] == '-')
                    {
						k_v[0] = k_v[0].substr(1, k_v[0].length() -1);
                    }
				}
				apply_params(k_v[0], k_v[1]);
			}
			else if (s.length() > 1 && s[0] == '-')
			{
				for (int h = 0; h < 2; h++)
				{
					if (s[0] == '-')
                    {
						s = s.substr(1, s.length() - 1);
                    }
				}
				apply_params(s, "true");
			}
			else if (s[0] != '-')
			{
				apply_params(jj, s);
				jj++;
			}
		}

		sort_params();
	}

	void CommandLineParser::about(std::string message)
	{
		about_message = message;
	}

	void CommandLineParser::apply_params(std::string key, std::string value)
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			for (size_t k = 0; k < data[i].keys.size(); k++)
			{
				if (key.compare(data[i].keys[k]) == 0)
				{
					data[i].def_value = value;
					break;
				}
			}
		}
	}

	void CommandLineParser::apply_params(int i, std::string value)
	{
		for (size_t j = 0; j < data.size(); j++)
		{
			if (data[j].number == i)
			{
				data[j].def_value = value;
				break;
			}
		}
	}

	void CommandLineParser::sort_params()
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			sort(data[i].keys.begin(), data[i].keys.end());
		}

		for (size_t j = 0; j < data.size();     j++)
		for (size_t i = 0; i < data.size() - 1; i++)
		{
			if (cmp_params(data[i], data[i+1]))
			{
				Params tmp = data[i];
				data[i] = data[i+1];
				data[i+1] = tmp;
			}
		}
	}

	void CommandLineParser::set_error(std::string msg)
	{
		error = true;
		error_message += msg + "\n";
	}

	std::string CommandLineParser::get_path_to_application()
	{
		return path_to_app;
	}

	bool CommandLineParser::has(const std::string& name)
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			for (size_t j = 0; j < data[i].keys.size(); j++)
			{
                if (name.compare(data[i].keys[j]) == 0 &&
                        std::string("true").compare(data[i].def_value) == 0)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool CommandLineParser::check()
	{
		return error == false;
	}

	void CommandLineParser::print_help()
	{
		if (about_message != "")
        {
			std::cout << about_message << std::endl;
        }

		std::cout << "Usage: " << app_name << " [params] ";

		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i].number > -1)
			{
                std::string name = data[i].keys[0].substr(1, data[i].keys[0].length()-1);
				std::cout << name << " ";
			}
		}

		std::cout << std::endl << std::endl;

		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i].number == -1)
			{
                std::cout << "\t";
				for (size_t j = 0; j < data[i].keys.size(); j++)
				{
					std::string k = data[i].keys[j];
					if (k.length() > 1)
					{
						std::cout << "--";
					}
					else
					{
						std::cout << "-";
					}
					std::cout << k;

					if (j != data[i].keys.size() - 1)
					{
						std::cout << ", ";
					}
				}
                std::string dv = cat_string(data[i].def_value);
                if (dv.compare("") != 0)
                {
                    std::cout << " (value:" << dv << ")";;
                }

                std::cout << "\n\t\t" << data[i].help_message << std::endl;
			}
		}
		std::cout << std::endl;

		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i].number != -1)
			{
				std::cout << "\t";
				std::string k = data[i].keys[0];
				k = k.substr(1, k.length() - 1);

				std::cout << k;

                std::string dv = cat_string(data[i].def_value);
                if (dv.compare("") != 0)
                {
                    std::cout << " (value:" << dv << ")";;
                }

                std::cout << "\n\t\t" << data[i].help_message << std::endl;
			}
		}
	}


}
