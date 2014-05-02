
#ifndef __ALGORITHMS_HPP__
#define __ALGORITHMS_HPP__

#include <string>
#include <vector>

/// \todo TODO: c++11 is the required for library
/// \todo TODO: add doxygen comments for algorithms

namespace mlib
{

    std::vector<std::string> split_range_string(std::string str, char fs, char ss);

    std::vector<std::string> split_string(std::string str, char symbol = ' ', bool create_empty_item = false);

    std::string cat_string(std::string str);
}

#endif
