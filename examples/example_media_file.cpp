
#include <string>
#include <iostream>

#include "mlib/console_parameters.hpp"
#include "mlib/media_file.hpp"
#include "mlib/datetime.hpp"
#include "mlib/convert.hpp"

int get_number_of_frames(mlib::Image & img)
{
	int num = 0;

	for (int i = 0; i < 32; i++)
	{
		int n = (img.get_color(static_cast<size_t>(i), 0) >= 200000) ? 1 : 0 ;
		num += n * (1 << i); 
	}

	return num;
}

int main(int argc, const char ** argv)
{
	mlib::ConsoleParameters params(argc, argv);

	std::string filename = params.get<std::string>("-f | --file", "test.avi");
	mlib::MediaFile mf(filename);

	//mf.print_info();
	//*/
	mlib::DateTime dt(static_cast<size_t>(mf.get_duration_sec()));

	std::cout << "duration in sec : " << mlib::to_str(dt) << std::endl; 
	std::cout << "duration in sec : " << mlib::time_to_str(mf.get_duration_sec()) << std::endl; 
	std::cout << "count frames    : " << mf.get_total_frames() << std::endl; 
	std::cout << "fps             : " << mf.get_fps() << std::endl; 
	std::cout << "bitrate         : " << mf.get_bitrate() << std::endl; 
	std::cout << "size            : " << mf.get_size() << std::endl; 
	std::cout << "size            : " << mlib::size_to_str(static_cast<size_t>(mf.get_size())) << std::endl; 
	//*/

	size_t ind = 1;
	while(true)
	{
		//std::cout << "read " << mlib::to_str(ind, 4, 0, '0') << " ... ";
		mlib::Image img(mf.read());
		if (img.empty()) break;

		
		/*/
		std::string name("output_img_" + mlib::to_str(ind, 4, 0, '0'));
		img.save(name);
		ind++;
		//*/

		//std::cout << "ok" << std::endl;

		//int num = get_number_of_frames(img);
		//std::cout << "num : " << num << std::endl;

		//if (num == 10) 
		//{
			//mf.seek(static_cast<size_t>(20));
			//mf.seek(30.0);
		//}

		//std::cout << ">>>   curr dts   >>>>>>  : " << mf.get_cur_dts() << std::endl; 
		
		ind++;
	}

	std::cout << "read " << ind << " frames";
	std::cout << std::endl;
	return 0;
}

