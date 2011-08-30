
#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <stddef.h> // for define size_t
#include <string>

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

