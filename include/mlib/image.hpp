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

#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <stddef.h> // for define size_t
#include <string>

/// \todo TODO: Implemented several class Image: ImageRGB, ImageYUV420, and convert it

namespace mlib
{
	class Image
	{
		public:
			Image(size_t width, size_t height);
			Image(size_t width, size_t height, unsigned char * d, int linesize, bool copy_memory = true);

			Image(const Image& img);
			Image& operator=(const Image& img);

			bool empty();

			size_t width();
			size_t height();
			size_t step();

			int get_color(size_t x, size_t y);

			~Image();

			void save(std::string & filename);

		private:
			unsigned char * data;

			size_t w;
			size_t h;
			size_t s;
			size_t size_in_byte;
	};

}

#endif

