
#include "mlib/safe_call.hpp"
#include "mlib/exception.hpp"

#ifdef HAVE_FFMPEG
	extern "C"
	{
		#undef  UINT64_C
		#define UINT64_C(val) val ## LL
		#include <libavutil/error.h>
	}
#endif

namespace mlib
{
	#ifdef HAVE_FFMPEG
		void ffmpeg_safe_call(int err, const std::string & file, unsigned long line)
		{
			if (err == 0) return;

			size_t size = 1024;
			char * message = new char[size];
			int ret = av_strerror(err, message, size);

			if (ret != 0)
			{
				delete [] message;
				return;
			}

			throw mlib::Exception (message , file, line );
		}
	#endif
}
