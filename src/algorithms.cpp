
#include <mlib/algorithms.hpp>

namespace mlib
{

    std::vector<std::string> split_string(std::string str, char symbol, bool create_empty_item)
    {
        std::vector<std::string> vec;
        std::string word = "";

        while (!str.empty())
        {
            if (str[0] == symbol)
            {
                if (!word.empty() || create_empty_item)
                {
                    vec.push_back(word);
                    word = "";
                }
            }
            else
            {
                word += str[0];
            }
            str = str.substr(1, str.length() - 1);
        }

        if (word != "" || create_empty_item)
        {
            vec.push_back(word);
        }

        return vec;
    }

    std::vector<std::string> split_range_string(std::string str, char fs, char ss)
    {
        std::vector<std::string> vec;
        std::string word = "";
        bool begin = false;

        while (!str.empty())
        {
            if (str[0] == fs)
            {
                if (begin == true)
                {
                    throw std::exception();
                }
                begin = true;
                word = "";
                str = str.substr(1, str.length() - 1);
            }

            if (str[0] == ss)
            {
                if (begin == false)
                {
                    throw std::exception();
                }
                begin = false;
                vec.push_back(word);
            }

            if (begin == true)
            {
                word += str[0];
            }
            str = str.substr(1, str.length() - 1);
        }

        if (begin == true)
        {
            throw std::exception();
        }

        return vec;
    }

    std::string cat_string(std::string str)
    {
        while (!str.empty() && str[0] == ' ')
        {
            str = str.substr(1, str.length() - 1);
        }

        while (!str.empty() && str[str.length() - 1] == ' ')
        {
            str = str.substr(0, str.length() - 1);
        }

        return str;
    }
}
