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

#ifndef __MEDIA_FILE_HPP__
#define __MEDIA_FILE_HPP__

#include <string>

/// \todo TODO: add class VideoReader with build without FFmpeg

extern "C"
{
    #undef  UINT64_C
    #define UINT64_C(val) val ## LL
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

#include "mlib/image.hpp"

namespace mlib
{
    class VideoReader
    {
        public:
            VideoReader(const std::string& filename);
            VideoReader(const VideoReader& reader);
            VideoReader& operator=(const VideoReader& reader);

            ~VideoReader();

            Image   read();

            void    seek(size_t frame_number);
            void    seek(double sec);

            double  get_duration_sec();
            double  get_fps();
            int64_t get_total_frames();
            int64_t get_size();
            int64_t get_bitrate();

            int64_t get_cur_dts();

            void print_info();

        private:
            AVFormatContext * avformat_context;
            AVCodecContext  * avcodec_context;
            AVCodec         * avcodec;
            AVFrame         * avframe_native;
            AVFrame         * avframe_rgb;

            int video_stream;
    };

}


#endif

