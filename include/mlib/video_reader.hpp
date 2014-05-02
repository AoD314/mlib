
#ifndef __MEDIA_FILE_HPP__
#define __MEDIA_FILE_HPP__

#include <string>

/// \todo TODO: add class VideoReader with build without FFmpeg

extern "C" {
#undef UINT64_C
#define UINT64_C(val) val##LL
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

        Image read();

        void seek(size_t frame_number);
        void seek(double sec);

        double get_duration_sec();
        double get_fps();
        int64_t get_total_frames();
        int64_t get_size();
        int64_t get_bitrate();

        int64_t get_cur_dts();

        void print_info();

    private:
        AVFormatContext* avformat_context;
        AVCodecContext* avcodec_context;
        AVCodec* avcodec;
        AVFrame* avframe_native;
        AVFrame* avframe_rgb;

        struct SwsContext* img_convert_ctx;

        int video_stream;
    };
}

#endif
