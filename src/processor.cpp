
#include "mlib/processor.hpp"

namespace mlib
{
	unsigned long long Processor::get_optimal_threads()
	{
		unsigned long long count_thread = 1;

		try
		{
			#pragma omp parallel
			#pragma omp master
			count_thread = omp_get_max_threads ();
		}
		catch (...) {}

		return count_thread;
	}

	unsigned long long Processor::get_frequency()
	{
		unsigned long long frequency = static_cast<unsigned long long>(2400000000);
				register volatile unsigned int time_edx, time_edx1;
				register volatile unsigned int time_eax, time_eax1;
				asm volatile (  "cpuid\n\t"
								"rdtsc\n\t"
								"mov %%edx, %0\n\t"
								"mov %%eax, %1\n\t" : "=r"(time_edx), "=r"(time_eax) ::
								"%rax", "%rbx", "%rcx", "%rdx");
				sleep(1);

				asm volatile (  "rdtscp\n\t"
								"mov %%edx, %0\n\t"
								"mov %%eax, %1\n\t"
								"cpuid\n\t" : "=r"(time_edx1), "=r"(time_eax1) ::
								"%rax", "%rbx", "%rcx", "%rdx");

				frequency =     ((unsigned long long)(time_edx1) << 32 | (unsigned long long)(time_eax1)) -
								((unsigned long long)(time_edx)  << 32 | (unsigned long long)(time_eax));

		return frequency;
	}

	bool Processor::is_set_N_bit_in_EDX(int bit)
	{
                register volatile unsigned int func = 1, _eax, _edx, _ecx;
                asm volatile ( "cpuid\n" : "=a" (_eax), "=d" (_edx), "=c" (_ecx) : "a" (func));
		return ((_edx & (1 << bit)) >> bit);
	}

	bool Processor::is_set_N_bit_in_ECX(int bit)
	{
                register volatile unsigned int func = 1, _eax, _edx, _ecx;
                asm volatile ("cpuid\n" : "=a" (_eax), "=d" (_edx), "=c" (_ecx) : "a" (func));
		return ((_ecx & (1 << bit)) >> bit);
	}

	bool Processor::supportSSE()
	{
		return is_set_N_bit_in_EDX(25);
	}

	bool Processor::supportSSE2()
	{
		return is_set_N_bit_in_EDX(26);
	}

	bool Processor::supportSSE3()
	{
		return is_set_N_bit_in_ECX(0);
	}

	bool Processor::supportSSSE3()
	{
		return is_set_N_bit_in_ECX(9);
	}

	bool Processor::supportSSE4_1()
	{
		return is_set_N_bit_in_ECX(19) && is_set_N_bit_in_ECX(9) && is_set_N_bit_in_ECX(0);
	}

	bool Processor::supportSSE4_2()
	{
		return is_set_N_bit_in_ECX(20) && is_set_N_bit_in_ECX(19) && is_set_N_bit_in_ECX(9);
	}

	bool Processor::supportAVX()
	{
		return is_set_N_bit_in_ECX(28);
	}

	bool Processor::supportAES()
	{
		return is_set_N_bit_in_ECX(25);
	}

	bool Processor::supportPOPCNT()
	{
		return is_set_N_bit_in_ECX(23);
	}

	bool Processor::supportMMX()
	{
		return is_set_N_bit_in_EDX(23);
	}

	bool Processor::supportRDTSCP()
	{
		return is_set_N_bit_in_ECX(1);
	}

	bool Processor::supportHT()
	{
		return is_set_N_bit_in_EDX(28);
	}
}

