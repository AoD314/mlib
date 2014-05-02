
#include <string>
#include <iostream>

#include "mlib/video_reader.hpp"
#include "mlib/image.hpp"
#include "mlib/datetime.hpp"
#include "mlib/timer.hpp"
#include "mlib/command_line_parser.hpp"
#include "mlib/convert.hpp"

const std::string keys =
    "{ h help |           | help message }"
    "{ i      |/work/video/benchmark_4096x4096_60M_H264.mkv| input file   }";

using namespace mlib;

int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, keys);

    std::string filename = parser.get<std::string>("i");

    VideoReader reader(filename);
    Timer t;

    size_t index = 0;

    t.start();

    while (true)
    {
        mlib::Image img(reader.read());

        if (img.empty())
        {
            break;
        }

        ++index;
    }

    t.stop();

    std::cout << "read " << index << " frames in " << t.get_total_time_in_seconds()
              << " sec   FPS: " << static_cast<double>(index) / t.get_total_time_in_seconds();

    std::cout << std::endl;

    return 0;
}
