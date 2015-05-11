
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
    enum CMLParamType {
        UNKNOWN = 0,
        BOOL,
        NUMBER,
        VALUE
    };

    class Params
    {
        public:
            Params();
            Params(std::string ks, std::string def, std::string help, int num = -1);

            bool            in(std::string key);
            std::string     get_def() const;
            int             get_number() const;
            std::string     get_help() const;
            CMLParamType    type() const;

            void            set_number(int num);
            void            set_def(std::string dv);

            std::vector<std::string> get_keys();

        private:


            std::string help_message;
            std::string def_value;
            std::vector<std::string> keys;
            int number;
            CMLParamType param_type;
    };


    class CommandLineParser
    {
        public:
            CommandLineParser(int argc, char** argv, const std::string keys);

            std::string get_path_to_application();

            template <typename T>
            T get(const std::string& name, bool space_delete = true)
            {
                Params * p = find_params_by_name(name);

                if (p != nullptr)
                {
                    std::string v = p->get_def();
                    if (space_delete == true)
                    {
                        v = cat_string(v);
                    }

                    return from_str<T>(v);
                }

                error = true;
                error_message += "Unknown parametes " + name + "\n";
                return T();
            }

            template <typename T>
            T get(int index, bool space_delete = true)
            {
                Params * p = find_params_by_number(index);

                if (p != nullptr)
                {
                    std::string v = p->get_def();
                    if (space_delete == true)
                    {
                        v = cat_string(v);
                    }

                    return from_str<T>(v);
                }

                error = true;
                error_message += "Unknown parametes #" + to_str<int>(index) + "\n";
                return T();
            }

            bool has(const std::string& name);


            void about(std::string message);

            void print_help();
            void print_errors();
            bool is_error();

        private:
            bool error;
            std::string error_message;
            std::string about_message;

            std::string path_to_app;
            std::string app_name;

            std::vector<Params> data;

            void apply_params(std::string key, std::string value);
            void apply_params(int i, std::string value);

            void setup_apps(std::string app);
            std::string clear_params(std::string param);
            Params * find_params_by_name(std::string name);
            Params * find_params_by_number(int num);
    };
}

#endif
