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

int main(int argc, char ** argv)
{
    CommandLineParser parser(argc, argv, keys);

    std::string filename = parser.get<std::string>("i");

    VideoReader reader(filename);
    Timer t;

    size_t index = 0;

    t.start();

    while(true)
    {
        mlib::Image img(reader.read());

        if (img.empty())
        {
            break;
        }

        ++index;
        //if (index > 50) break;
        //std::cout << ".";
        //if (index % 10 == 0) std::cout << std::endl;
    }

    t.stop();

    std::cout << "read " << index << " frames in "
              << t.get_total_time_in_seconds() << " sec   FPS: "
              << static_cast<double>(index) / t.get_total_time_in_seconds();

    std::cout << std::endl;

    return 0;
}

