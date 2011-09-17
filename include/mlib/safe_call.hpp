
#ifndef __SAFE_CALL_HPP__
#define __SAFE_CALL_HPP__

#include <string>

namespace mlib
{
	#ifdef HAVE_FFMPEG
		void ffmpeg_safe_call(int err, const std::string & file, unsigned long line);
	#endif
}

#ifdef HAVE_FFMPEG
	#define FFMPEG_SAFE_CALL(ERR) ffmpeg_safe_call( ERR , __FILE__, __LINE__ )
#endif

#endif

