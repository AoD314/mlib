
#ifndef __SAFE_CALL_HPP__
#define __SAFE_CALL_HPP__

#include <string>

namespace mlib
{
		void ffmpeg_safe_call(int err, const std::string & file, unsigned long line);
}

	#define FFMPEG_SAFE_CALL(ERR) ffmpeg_safe_call( ERR , __FILE__, __LINE__ )

#endif

