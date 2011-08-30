
#include "mlib/image.hpp"
#include "mlib/memory.hpp"

#include <fstream>

namespace mlib
{

	Image::Image(size_t width, size_t height) : 
	    data(0), w(width), h(height), s(3 * w), size_in_byte(s * h)
	{
		if (size_in_byte != 0)
		{
			data = new unsigned char[size_in_byte];

			for (size_t i = 0; i < size_in_byte; ++i)
			{
				data[i] = 0;
			}
		}
	}

	Image::Image(size_t width, size_t height, unsigned char * d, int linesize, bool copy_memory)
	: data(0), w(width), h(height), s(static_cast<size_t>(linesize)), size_in_byte(s * h)
	{
		if (copy_memory == true)
		{
			if (size_in_byte != 0)
			{
				data = new unsigned char[size_in_byte];
				mem_copy<unsigned char>(d, data, size_in_byte);
			}
		}
		else
		{
			data = d;
		}
	}

	Image::Image(const Image& img) : 
	    data(0), w(img.w), h(img.h), s(img.s), size_in_byte(img.size_in_byte)
	{
		if (size_in_byte != 0)
		{
			data = new unsigned char[size_in_byte];
			mem_copy<unsigned char>(img.data, data, size_in_byte);
		}
	}

	int Image::get_color(size_t x, size_t y)
	{
		int b = static_cast<int>(data[y * s + 3 * x + 0]);
		int g = static_cast<int>(data[y * s + 3 * x + 1]);
		int r = static_cast<int>(data[y * s + 3 * x + 2]);

		return (r << 16) + (g << 8) + (b);
	}

	Image& Image::operator=(const Image& img)
	{
		w = img.w;
		h = img.h;
		s = img.s;
		size_in_byte = img.size_in_byte;

		data = new unsigned char[size_in_byte]; 
		mem_copy<unsigned char>(img.data, data, size_in_byte);

		return *this;
	}

	void Image::save(std::string & filename)
	{
		filename += ".ppm";

		// Open file
		std::ofstream file(filename.c_str());

		file << "P3" << std::endl << w << " " << h << std::endl << "255" << std::endl;

		// Write pixel data
		for (size_t i = 0; i < 3 * w * h; i+=3)
		{
			file << static_cast<int>(data[i + 0]) << " ";
			file << static_cast<int>(data[i + 1]) << " ";
			file << static_cast<int>(data[i + 2]) << std::endl;
		}

		file.close();
	}

	size_t Image::step()
	{
		return s;
	}

	size_t Image::width()
	{
		return w;
	}

	size_t Image::height()
	{
		return h;
	}

	bool Image::empty()
	{
		if (data == 0)
			return true;
		else
			return false;
	}

	Image::~Image()
	{
		if (data != 0)
		{
			delete[] data;
			data = 0;
		}
	}


}

