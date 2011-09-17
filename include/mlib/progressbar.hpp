
#ifndef __PROGRESSBAR_HPP__
#define __PROGRESSBAR_HPP__

#include <string>

#if defined WIN32 || defined _WIN32
    #include <windows.h>
#endif

namespace mlib
{
	//! Method for drawing progress bar in console
	/*!
	
	 \param progress displays the overall progress. should be from 0.0 to 1.0
	 \param msg      displays a message on a new line with the overall progress 
	 \param len      length progress bar
	
	*/
	void progress_bar(double progress, std::string msg = "", size_t len = 80);

	//! Wait sec seconds
	void sleep(unsigned int sec);
}

#endif
