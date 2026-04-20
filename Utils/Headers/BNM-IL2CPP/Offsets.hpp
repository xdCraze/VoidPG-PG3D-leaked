#pragma once

#include <cstdint>

namespace BNM
{
    namespace Offsets
    {
        static int64_t toCharArray = -1;
        static int64_t methodOffset = -1;
        static uint64_t offsetOfMethod(uint64_t start_ptr, uint64_t equal_ptr)
        {
            if (BNM::Offsets::methodOffset == -1)
            {
                int depth = 512;
                for (int i = 0; i < depth; i++)
                {
                    if (*(void **)(start_ptr + i) == *(void **)(equal_ptr))
                    {
                        BNM::Offsets::methodOffset = i;
                        return i;
                    }
                }

                return 0;
            }
            else
                return BNM::Offsets::methodOffset;
        }

        static uint64_t offsetOfCharArray(void *start_ptr, int16_t value)
        {
            if (BNM::Offsets::toCharArray == -1)
            {
                int depth = 512;
                for (int i = 0; i < depth; i++)
                {
                    if ((uint16_t)(*((char *)((void *)((uint64_t)start_ptr + i)))) == value)
                    {
                        BNM::Offsets::toCharArray = i;
                        return i;
                    }
                }
                return 0;
            }
            else
                return BNM::Offsets::toCharArray;
        }
    }
}