
#ifndef __PROCESSOR_HPP__
#define    __PROCESSOR_HPP__

#include <omp.h>
#include <limits>
#include <string>

#if defined WIN32 || defined _WIN32
    #include <windows.h>
    #include <intrin.h>
#elif defined __linux__ || defined __APPLE__
    #include <unistd.h>
    #include <stdio.h>
    #include <sys/types.h> 
    #include <sys/sysctl.h>
#endif

#undef max
#undef min

namespace mlib
{
    class Processor
    {
        public:
            static int get_number_of_cpus();
            static unsigned long long get_frequency();

            static bool supportSSE();
            static bool supportSSE2();
            static bool supportSSE3();
            static bool supportSSSE3();
            static bool supportSSE4_1();
            static bool supportSSE4_2();

            static bool supportAVX();
            static bool supportAVX2();

            static bool supportFMA();

            static bool supportAES();
            static bool supportPOPCNT();
            static bool supportRDTSCP();
            static bool supportMMX();
            static bool supportHT();

            static bool is_set_N_bit_in_EAX(unsigned int bit);
            static bool is_set_N_bit_in_EBX(unsigned int bit);
            static bool is_set_N_bit_in_ECX(unsigned int bit);
            static bool is_set_N_bit_in_EDX(unsigned int bit);
    };
}

#endif

