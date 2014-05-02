
#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

namespace mlib
{
    template <typename T>
    void mem_copy(T* src, T* dst, size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            dst[i] = src[i];
        }
    }
}

#endif
