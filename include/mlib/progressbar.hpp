
#ifndef __PROGRESSBAR_HPP__
#define __PROGRESSBAR_HPP__

#include <string>

namespace mlib
{

	// 0.0 <= progress <= 1.0
	void progress_bar(double progress, std::string msg = "", size_t len = 80);

}

#endif
