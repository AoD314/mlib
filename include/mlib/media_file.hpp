
#ifndef __MEDIA_FILE_HPP__
#define __MEDIA_FILE_HPP__

#include <string>

/// \todo TODO: add class MediaFile with build without FFmpeg

#ifdef HAVE_FFMPEG

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
		class MediaFile
		{
			public:
				MediaFile(const std::string& filename);
				MediaFile(const MediaFile& mf);
				MediaFile& operator=(const MediaFile& mf);

				~MediaFile();

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

#endif

