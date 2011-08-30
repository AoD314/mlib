
#include "mlib/media_file.hpp"
#include "mlib/safe_call.hpp"
#include "mlib/exception.hpp"
#include "mlib/processor.hpp"

#include <iostream>

namespace mlib
{
	MediaFile::MediaFile(const std::string& filename) : 
	    avformat_context(0), avcodec_context(0), avcodec(0),
	    avframe_native(0), avframe_rgb(0), video_stream(-1) 
	{
		av_register_all();

		// Open video file
		FFMPEG_SAFE_CALL( avformat_open_input(&avformat_context, filename.c_str(), NULL, NULL) );
		// Retrieve stream information
		FFMPEG_SAFE_CALL( av_find_stream_info(avformat_context) );

		// Dump information about file onto standard error 
		 av_dump_format(avformat_context, 0, filename.c_str() ,0);

		// Find the first video stream
		for(int i = 0; i < static_cast<int>(avformat_context->nb_streams); i++)
		{
			struct AVCodecContext * cc = avformat_context->streams[i]->codec;

			// set number of threads 
			cc->thread_count = Processor::get_number_of_cpus();

			if(cc->codec_type == AVMEDIA_TYPE_VIDEO && video_stream == -1)
			{
				AVCodec * codec = avcodec_find_decoder(cc->codec_id);

				if (codec == NULL)
					Error("Unsupported codec !!!");

				FFMPEG_SAFE_CALL(avcodec_open(cc, codec));
				video_stream = i;
				break;
			}
		}

		if(video_stream == -1)
			Error("Didn't find a video stream");

		// Get a pointer to the codec context for the video stream
		avcodec_context = avformat_context->streams[video_stream]->codec;

		// Allocate video frame
		avframe_native = avcodec_alloc_frame();

	}

	MediaFile::MediaFile(const MediaFile& mf) : 
	    avformat_context(mf.avformat_context), 
	    avcodec_context (mf.avcodec_context), 
	    avcodec(0),
	    avframe_native(0), 
	    avframe_rgb(0),
	    video_stream(-1) {}

	MediaFile& MediaFile::operator=(const MediaFile& mf)
	{
	    avformat_context = mf.avformat_context; 
	    avcodec_context  = mf.avcodec_context; 
		return *this;
	}

	Image MediaFile::read()
	{
		int frame_finished;
		AVPacket packet;

		int count_errs = 0;
		const int max_number_of_attempts = 8;

		while(true)
		{
			av_read_frame(avformat_context, &packet);

			if(packet.stream_index == video_stream) 
			{
				// Decode video frame
				avcodec_decode_video2(avcodec_context, avframe_native, &frame_finished, &packet);
                                  
				// Did we get a video frame?
				if(frame_finished) 
				{
					avframe_rgb   = avcodec_alloc_frame();
					int num_bytes = avpicture_get_size(PIX_FMT_RGB24, avcodec_context->width, avcodec_context->height);
					uint8_t * buffer = reinterpret_cast<uint8_t *>(av_malloc (static_cast<long unsigned int>(num_bytes) * sizeof(uint8_t)));
					avpicture_fill(reinterpret_cast<AVPicture*>(avframe_rgb), buffer, PIX_FMT_RGB24, avcodec_context->width, avcodec_context->height);

					avframe_rgb->width  = avframe_native->width;
					avframe_rgb->height = avframe_native->height;

					struct SwsContext * img_convert_ctx = 

					sws_getContext(
					                 avcodec_context->width,
					                 avcodec_context->height,
					                 avcodec_context->pix_fmt,
					                 avcodec_context->width,
					                 avcodec_context->height,
					                 PIX_FMT_BGR24,
					                 SWS_BICUBIC,
					                 NULL, NULL, NULL
					              );

					if (img_convert_ctx == NULL)
						Error("Cannot initialize the conversion context!");

					sws_scale(
					            img_convert_ctx, 
					            avframe_native->data,
					            avframe_native->linesize, 
					            0,
					            avcodec_context->height,
					            avframe_rgb->data, 
					            avframe_rgb->linesize
					         );

					sws_freeContext(img_convert_ctx);

					// Convert the image from its native format to RGB
					//img_convert( reinterpret_cast<AVPicture *>(avframe_rgb), PIX_FMT_RGB24, reinterpret_cast<AVPicture*>(avframe_native), 
					//             avcodec_context->pix_fmt, avcodec_context->width, avcodec_context->height);
					av_free(avframe_rgb);

					return Image(
					               static_cast<size_t>              (avcodec_context->width), 
					               static_cast<size_t>              (avcodec_context->height),
					             //reinterpret_cast<unsigned char *>(avframe_rgb->data[0]),
					               reinterpret_cast<unsigned char *>(buffer),
					               avframe_rgb->linesize[0],
					               false
					            );
				}
				else
				{
					count_errs ++;
					if (count_errs > max_number_of_attempts)
							break;
				}

			}
		}

		// Free the packet that was allocated by av_read_frame
		av_free_packet(&packet);

		return Image(0, 0);
	}

	double MediaFile::get_duration_sec()
	{
		return static_cast<double>(avformat_context->duration) / static_cast<double>(AV_TIME_BASE);
	}

	int64_t MediaFile::get_bitrate()
	{
		return avformat_context->bit_rate;
	}
	int64_t MediaFile::get_size()
	{
		return avformat_context->file_size;
	}

	int64_t MediaFile::get_cur_dts()
	{
		std::cout << std::endl;
		//std::cout << "cur_dts " << avformat_context->streams[video_stream]->cur_dts << std::endl;
		//std::cout << "pkt_dts " << avformat_context->streams[video_stream]->cur_pkt.dts << std::endl;
		//std::cout << "offset  " << avformat_context->data_offset << std::endl;
		return 0;
	}

	double MediaFile::get_fps()
	{
		return av_q2d(avformat_context->streams[video_stream]->r_frame_rate); 
	}

	int64_t MediaFile::get_total_frames()
	{
		int64_t nbf = avformat_context->streams[video_stream]->nb_frames;
		if (nbf == 0)
			nbf = static_cast<int64_t>(get_duration_sec() * get_fps());
		return nbf;
	}

	void MediaFile::seek(size_t frame_number) 
	{
		double sec = static_cast<double>(frame_number) / static_cast<double>(get_fps());
		seek(sec);
	}

	void MediaFile::seek(double sec)
	{
		int64_t time_stamp = avformat_context->streams[video_stream]->start_time;
		double  time_base  = av_q2d(avformat_context->streams[video_stream]->time_base);
		time_stamp += static_cast<int64_t>(sec / time_base);
		FFMPEG_SAFE_CALL( av_seek_frame(avformat_context, video_stream, time_stamp, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD) );
	}

	MediaFile::~MediaFile()
	{
		av_close_input_file(avformat_context);
	}

	void MediaFile::print_info()
	{
		std::cout << "avf->nb_streams   : " << avformat_context->nb_streams << std::endl;
		std::cout << "avf->start_time   : " << avformat_context->start_time << std::endl;
		std::cout << "avf->duration     : " << avformat_context->duration << std::endl;
		std::cout << "avf->file_size    : " << avformat_context->file_size << std::endl;
		std::cout << "avf->bit_rate     : " << avformat_context->bit_rate << std::endl;
		std::cout << "avf->data_offset  : " << avformat_context->data_offset << std::endl;
		std::cout << "avf->mux_rate     : " << avformat_context->mux_rate << std::endl;

		std::cout << "stream->index               : " << avformat_context->streams[video_stream]->index << std::endl;
		std::cout << "stream->id                  : " << avformat_context->streams[video_stream]->id << std::endl;
		std::cout << "stream->first_tds           : " << avformat_context->streams[video_stream]->first_dts << std::endl;
		std::cout << "stream->start_time          : " << avformat_context->streams[video_stream]->start_time << std::endl;
		std::cout << "stream->duration            : " << avformat_context->streams[video_stream]->duration << std::endl;
		std::cout << "stream->nb_frames           : " << avformat_context->streams[video_stream]->nb_frames << std::endl;

		std::cout << "stream->r_frame_rate        : " << av_q2d(avformat_context->streams[video_stream]->r_frame_rate) << std::endl;
		std::cout << "stream->time_base           : " << av_q2d(avformat_context->streams[video_stream]->time_base) << std::endl;
		std::cout << "stream->sample_aspect_ratio : " << av_q2d(avformat_context->streams[video_stream]->sample_aspect_ratio) << std::endl;
		std::cout << "stream->avg_frame_rate      : " << av_q2d(avformat_context->streams[video_stream]->avg_frame_rate) << std::endl;

		std::cout << std::endl;
	}

}

