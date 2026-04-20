#pragma once

#include "Image.hpp"
#include "../../ExportCall.hpp"

namespace BNM
{
    struct Assembly
    {
    public:
        // Returns image of assembly. By image you can get all needed things.
        BNM::Image *Image()
        {
            return (BNM::Image *)(BNM::ExportCall::AssemblyGetImage((void *)this));
        }
    };
}