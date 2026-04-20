#pragma once

#include "../../ExportCall.hpp"
#include <string>
#include <stringapiset.h>

namespace BNM
{
    struct String
    {
    public:
        static BNM::String *New(const char *content)
        {
            return (BNM::String *)BNM::ExportCall::StringNew(content);
        }

        int Length()
        {
            return BNM::ExportCall::StringLength((void *)this);
        }

        std::string Content()
        {
            int length = this->Length();
            std::string result(static_cast<size_t>(length) * 3 + 1, '\0');
            WideCharToMultiByte(CP_UTF8, 0, BNM::ExportCall::StringChars((void *)this), length, &result[0], static_cast<int>(result.size()), 0, 0);
            return result;
        }
    };
}