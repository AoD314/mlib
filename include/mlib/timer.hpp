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

#ifndef __TIMER_HPP__
#define	__TIMER_HPP__

#include <ostream>
#include <iomanip>

#include "mlib/processor.hpp"

namespace mlib
{
	enum TimerModePrint
	{
		inSec,
		inMin,
		inHour,
		inDays,
		inAll
	};

	enum TimerModeCount
	{
		mode_sum,
		mode_min,
		mode_max,
		mode_avg
	};

	class Timer
	{
		private:
			double seconds_total;
			double seconds_last;
			double seconds_min;
			double seconds_max;

			unsigned long long fr;
			unsigned long long time_total;
			unsigned long long time_last;
			unsigned long long time_min;
			unsigned long long time_max;
			unsigned long long count_time;

			unsigned int time_edx, time_edx1;
			unsigned int time_eax, time_eax1;

			TimerModePrint mode_p;
			TimerModeCount mode_c;
			void CalcSec();

		public:
			Timer(TimerModeCount mode = mode_sum);
			Timer(unsigned long long frequency, TimerModeCount mode = mode_sum);

			inline void start()
			{
				#if defined WIN32 || defined _WIN32 || defined WINCE
					LARGE_INTEGER counter;
					QueryPerformanceCounter( &counter );
					time_edx = counter.HighPart;
					time_eax = counter.HighPart;
				#elif defined __linux || defined __linux__
					asm volatile (  "cpuid\n\t"
									"rdtsc\n\t"
									"mov %%edx, %0\n\t"
									"mov %%eax, %1\n\t" : "=r"(time_edx), "=r"(time_eax) ::
									"%rax", "%rbx", "%rcx", "%rdx");
				#endif
			}

			inline void stop ()
			{
				#if defined WIN32 || defined _WIN32 || defined WINCE
					LARGE_INTEGER counter;
					QueryPerformanceCounter( &counter );
					time_edx1 = counter.HighPart;
					time_eax1 = counter.HighPart;
				#elif defined __linux || defined __linux__
					asm volatile (  "rdtscp\n\t"
									"mov %%edx, %0\n\t"
									"mov %%eax, %1\n\t"
									"cpuid\n\t" : "=r"(time_edx1), "=r"(time_eax1) ::
									"%rax", "%rbx", "%rcx", "%rdx");
				#endif

				time_last =
							(static_cast<unsigned long long>(time_edx1) << 32 | static_cast<unsigned long long>(time_eax1)) -
							(static_cast<unsigned long long>(time_edx)  << 32 | static_cast<unsigned long long>(time_eax));
				CalcSec();
			}

			void reset();
			void set_mode(TimerModePrint m);

			double operation_per_second() const;
			unsigned long long get_frequency() const;

			double             get_time_in_mseconds() const;
			double             get_time_in_seconds() const;
			double             get_time_in_minutes() const;
			double             get_time_in_hours() const;
			double             get_time_in_days() const;
			unsigned long long get_time_in_tick() const;

			double             get_total_time_in_mseconds() const;
			double             get_total_time_in_seconds() const;
			double             get_total_time_in_minutes() const;
			double             get_total_time_in_hours() const;
			double             get_total_time_in_days() const;
			unsigned long long get_total_time_in_tick() const;


			friend std::ostream & operator << (std::ostream& out, const Timer & t);
	};
}

#endif

