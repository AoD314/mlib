
#include <iostream>
#include <limits>

#include <mlib/convert.hpp>
#include <mlib/processor.hpp>

using namespace mlib;

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << "Processor: " << std::endl;
    std::cout << "MMX   : " << to_str(Processor::supportMMX()) << std::endl;
    std::cout << "SSE   : " << to_str(Processor::supportSSE()) << std::endl;
    std::cout << "SSE2  : " << to_str(Processor::supportSSE2()) << std::endl;
    std::cout << "SSE3  : " << to_str(Processor::supportSSE3()) << std::endl;
    std::cout << "SSSE3 : " << to_str(Processor::supportSSSE3()) << std::endl;
    std::cout << "SSE4.1: " << to_str(Processor::supportSSE4_1()) << std::endl;
    std::cout << "SSE4.2: " << to_str(Processor::supportSSE4_2()) << std::endl;
    std::cout << "AVX   : " << to_str(Processor::supportAVX()) << std::endl;
    std::cout << "AVX2  : " << to_str(Processor::supportAVX2()) << std::endl;

    std::cout << "FMA   : " << to_str(Processor::supportFMA()) << std::endl;
    std::cout << "AES   : " << to_str(Processor::supportAES()) << std::endl;
    std::cout << "HT    : " << to_str(Processor::supportHT()) << std::endl;
    std::cout << "POPCNT: " << to_str(Processor::supportPOPCNT()) << std::endl;
    std::cout << "RDTSCP: " << to_str(Processor::supportRDTSCP()) << std::endl;

    return 0;
}
