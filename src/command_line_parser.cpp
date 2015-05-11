#include <exception>

#include "mlib/command_line_parser.hpp"
#include "mlib/convert.hpp"
#include "mlib/exception.hpp"

namespace mlib
{

Params::Params() :
    help_message(""), def_value(""), keys(), number(0), param_type(CMLParamType::UNKNOWN)
{}

Params::Params(std::string ks, std::string def, std::string help, int num) :
    help_message(help), def_value(def), keys(split_string(ks)), number(num), param_type(CMLParamType::UNKNOWN)
{
    for (size_t i = 0; i < keys.size(); i++)
    {
        std::string key = keys[i];

        if (key[0] == '@')
        {
            param_type = CMLParamType::NUMBER;
            break;
        }

        if (key[0] == ':')
        {
            param_type = CMLParamType::VALUE;
            break;
        }

        if (CMLParamType::UNKNOWN == param_type)
        {
            param_type = CMLParamType::BOOL;
            def_value = cat_string(def_value);
            if (def_value.empty())
            {
                def_value = "false";
            }
            break;
        }
    }

    for (size_t i = 0; i < keys.size(); i++)
    {
        if (keys[i][0] == '@' || keys[i][0] == ':')
        {
            keys[i] = keys[i].substr(1, keys[i].length() - 1);
        }
    }
}

std::string Params::get_def() const
{
    return def_value;
}

int Params::get_number() const
{
    return number;
}

std::string Params::get_help() const
{
    return help_message;
}

CMLParamType Params::type() const
{
    return param_type;
}

void Params::set_number(int num)
{
    number = num;
}

void Params::set_def(std::string dv)
{
    def_value = dv;
}

std::vector<std::string> Params::get_keys()
{
    return keys;
}

bool Params::in(std::string key)
{
    for (size_t i = 0; i < keys.size(); i++)
    {
        if (keys[i].compare(key) == 0)
        {
            return true;
        }
    }
    return false;
}


    CommandLineParser::CommandLineParser(int argc, char** argv, const std::string keys)
        : error(false), error_message(""), about_message(""), path_to_app(""), app_name(""), data()
    {
        setup_apps(argv[0]);

        std::vector<std::string> kk = split_range_string(keys, '{', '}');

        if (kk.size() == 0)
        {
            error = true;
            error_message = "Variable KEYS could not be empty\n";
        }

        int index = 0;
        for (size_t i = 0; i < kk.size(); i++)
        {
            std::vector<std::string> l = split_string(kk[i], '|', true);

            Params p(l[0], l[1], l[2]);

            if (cat_string(l[0]).empty())
            {
                error = true;
                error_message = "Field KEYS could not be empty\n";
            }
            else
            {
                if (p.type() == mlib::CMLParamType::NUMBER)
                {
                    p.set_number(index);
                    index++;
                }
                data.push_back(p);
            }
        }

        // parse argv
        index = 0;
        for (int i = 1; i < argc; i++)
        {
            // '-t' => 't'
            // '--time' => 'time'
            std::string s = clear_params(argv[i]);
            std::string next = "";
            if (i + 1 < argc) next = std::string(argv[i+1]);

            if (s.find('=') != std::string::npos && s.find('=') < s.length())
            {
                std::vector<std::string> k_v = split_string(s, '=', true);
                s = k_v[0];
                next = k_v[1];
            }

            Params * p = find_params_by_name(s);
            if (p == nullptr) continue;

            mlib::CMLParamType t = p->type();

            switch(t) {
                case mlib::CMLParamType::BOOL:
                    apply_params(s, "true");
                    break;

                case mlib::CMLParamType::NUMBER:
                    apply_params(index, s);
                    break;

                case mlib::CMLParamType::VALUE:
                    apply_params(s, next);
                    i++;
                    break;
            }
        }
    }

    void CommandLineParser::about(std::string message)
    {
        about_message = message;
    }

    void CommandLineParser::apply_params(std::string key, std::string value)
    {
        Params * p = find_params_by_name(key);
        if (p != nullptr)
        {
            p->set_def(value);
        }
    }

    void CommandLineParser::apply_params(int i, std::string value)
    {
        Params * p = find_params_by_number(i);
        if (p != nullptr)
        {
            p->set_def(value);
        }
    }

    void CommandLineParser::setup_apps(std::string app)
    {
        size_t pos_s = app.find_last_of("/\\");
        if (pos_s == std::string::npos)
        {
            path_to_app = "";
            app_name = app;
        }
        else
        {
            path_to_app = app.substr(0, pos_s);
            app_name = app.substr(pos_s + 1, app.length() - pos_s);
        }
    }

    std::string CommandLineParser::clear_params(std::string param)
    {
        while (param.length() > 1 && param[0] == '-')
        {
            param = param.substr(1, param.length() - 1);
        }

        return param;
    }

    Params * CommandLineParser::find_params_by_name(std::string name)
    {
        for (size_t i = 0; i < data.size(); i++)
        {
            if (data[i].in(name))
            {
                return &data[i];
            }
        }

        return nullptr;
    }

    Params * CommandLineParser::find_params_by_number(int num)
    {
        for (size_t i = 0; i < data.size(); i++)
        {
            if (data[i].get_number() == num)
            {
                return &data[i];
            }
        }

        return nullptr;
    }

    std::string CommandLineParser::get_path_to_application()
    {
        return path_to_app;
    }

    bool CommandLineParser::has(const std::string& name)
    {
        Params * p = find_params_by_name(name);
        if (p == nullptr)
        {
            return false;
        }
        else
        {
            if (p->type() == mlib::CMLParamType::BOOL)
            {
                if (p->get_def() == "true")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
                return false;
        }
    }

    void CommandLineParser::print_help()
    {
        if (about_message != "")
        {
            std::cout << about_message << std::endl;
        }

        std::cout << "Usage: " << app_name << " [params] " << std::endl;

        for (size_t i = 0; i < data.size(); i++)
        {
            Params * p = &data[i];
            if (p->type() == mlib::CMLParamType::NUMBER) continue;

            std::vector<std::string> ks = p->get_keys();
            for (size_t j = 0; j < ks.size(); j++)
            {
                std::string k = ks[j];

                if (k.length() > 1)
                {
                    std::cout << "--";
                }
                else
                {
                    std::cout << "-";
                }
                std::cout << k;

                if (j != ks.size() - 1)
                {
                    std::cout << ", ";
                }
            }

            std::string dv = cat_string(p->get_def());

            if (dv.compare("") != 0)
            {
                std::cout << " (value:" << dv << ")";
            }

            std::cout << "\n\t\t" << p->get_help() << std::endl;
        }

        std::cout << std::endl;

        for (size_t i = 0; i < data.size(); i++)
        {
            Params * p = &data[i];
            if (p->type() != mlib::CMLParamType::NUMBER) continue;

            std::cout << "\t";
            std::cout << p->get_keys()[0];

            std::string dv = cat_string(p->get_def());
            if (dv.compare("") != 0)
            {
                std::cout << " (value:" << dv << ")";
            }

            std::cout << "\n\t\t" << p->get_help() << std::endl;
        }
    }

    void CommandLineParser::print_errors()
    {
        if (is_error())
        {
            std::cout << error_message << std::endl;
        }
    }

    bool CommandLineParser::is_error()
    {
        return error;
    }
}
