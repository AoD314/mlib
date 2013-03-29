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

#ifndef __PROCESSOR_HPP__
#define __PROCESSOR_HPP__

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

