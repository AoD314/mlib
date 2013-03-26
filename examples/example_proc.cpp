
#include <iostream>

#include <mlib/convert.hpp>
#include <mlib/processor.hpp>

int main(int /*argc*/, char ** /*argv*/)
{
    std::cout << "Processor: " << std::endl;
    std::cout << "MMX   : " << mlib::to_str(mlib::Processor::supportMMX())    << std::endl;
    std::cout << "SSE   : " << mlib::to_str(mlib::Processor::supportSSE())    << std::endl;
    std::cout << "SSE2  : " << mlib::to_str(mlib::Processor::supportSSE2())   << std::endl;
    std::cout << "SSE3  : " << mlib::to_str(mlib::Processor::supportSSE3())   << std::endl;
    std::cout << "SSSE3 : " << mlib::to_str(mlib::Processor::supportSSSE3())  << std::endl;
    std::cout << "SSE4.1: " << mlib::to_str(mlib::Processor::supportSSE4_1()) << std::endl;
    std::cout << "SSE4.2: " << mlib::to_str(mlib::Processor::supportSSE4_2()) << std::endl;
    std::cout << "AVX   : " << mlib::to_str(mlib::Processor::supportAVX())    << std::endl;
    std::cout << "AVX2  : " << mlib::to_str(mlib::Processor::supportAVX2())   << std::endl;

    std::cout << "FMA   : " << mlib::to_str(mlib::Processor::supportFMA())    << std::endl;
    std::cout << "AES   : " << mlib::to_str(mlib::Processor::supportAES())    << std::endl;
    std::cout << "HT    : " << mlib::to_str(mlib::Processor::supportHT())     << std::endl;
    std::cout << "POPCNT: " << mlib::to_str(mlib::Processor::supportPOPCNT()) << std::endl;
    std::cout << "RDTSCP: " << mlib::to_str(mlib::Processor::supportRDTSCP()) << std::endl;

    return 0;
}
