#pragma once

#include "../../ExportCall.hpp"
#include "Assembly.hpp"

namespace BNM
{
    struct Domain
    {
    public:
        Domain()
        {
            //BNM::ExportCall::GetDomain();
        }

        // Returns assembly by the name
        BNM::Assembly *Assembly(const char *name)
        {
            return (BNM::Assembly *)(BNM::ExportCall::GetAssemblyFromDomain((void *)this, name));
        }

        // а тут мы кароч представим КУЧУ крутых методов чтобы ну там ээээ ну ээээ найти КЛАСС
    };
}
