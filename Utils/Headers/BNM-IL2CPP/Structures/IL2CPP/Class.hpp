#pragma once

#include "../../ExportCall.hpp"
#include "Headers/BNM-IL2CPP/Offsets.hpp"
#include "Method.hpp"
#include "Field.hpp"
#include <vector>
#include <algorithm>

namespace BNM
{
    struct Class
    {
    public:

        const char* Name()
        {
            return BNM::ExportCall::ClassGetName((void*)this);
        }

        // Return method of class by the name and parameter count
        BNM::Method* Method(const char* name, int parameter_count = -1)
        {
            return (BNM::Method*)BNM::ExportCall::MethodFromName((void*)this, name, parameter_count);
        }

        // Return field of class by the name
        BNM::Field* Field(const char* name)
        {
            return (BNM::Field*)(BNM::ExportCall::FieldFromName((void*)this, name));
        }

        // Returns size of erm what the sigma
        int ElementSize()
        {
            return BNM::ExportCall::ClassArrayElementSize((void*)this);
        }

        void* Type()
        {
            return BNM::ExportCall::TypeFromClass((void*)this);
        }

        void* BaseType()
        {
            return BNM::ExportCall::ClassEnumBasetype((void*)this);
        }

        std::vector<BNM::Class*> NestedClasses()
        {
            std::vector<BNM::Class*> arr;
            void* iterator = nullptr;
            void* m_handle = BNM::ExportCall::ClassNestedClasses((void*)this, &iterator);
            while (m_handle != NULL)
            {
                arr.push_back((BNM::Class*)m_handle);
                m_handle = BNM::ExportCall::ClassNestedClasses((void*)this, &iterator);
            }

            return arr;
        }

        BNM::Class* Nested(const char* name)
        {
            std::vector<BNM::Class*> vec{ this->NestedClasses() };
            if (vec.size() == 0)
            {
                return (BNM::Class*)nullptr;
            }

            for (auto klass : vec)
            {
                if (strcmp(klass->Name(), name) == 0)
                {
                    return klass;
                    break;
                }
            }
        }

        // Returns generic instance of generic class with given parameters
        BNM::Class* Inflate(std::vector<BNM::Class*> types)
        {
            void* il2cpp_array_types = BNM::ExportCall::ArrayNew(BNM::ExportCall::ClassFromName(BNM::ExportCall::AssemblyGetImage(BNM::ExportCall::GetAssemblyFromDomain(BNM::ExportCall::GetDomain(), "mscorlib")), "System", "Type"), (int)types.size());
            void* str = BNM::ExportCall::StringNew("v");
            void* (*toCharArray)(void*) = (void* (*)(void*))((((BNM::Method*)(BNM::ExportCall::MethodFromName(BNM::ExportCall::ClassFromName(BNM::ExportCall::AssemblyGetImage(BNM::ExportCall::GetAssemblyFromDomain(BNM::ExportCall::GetDomain(), "mscorlib")), "System", "String"), "ToCharArray", 0)))->VA()));
            void* charArray = toCharArray(str);
            uint64_t offset = BNM::Offsets::offsetOfCharArray(charArray, 118);
            void* array_elements = (void*)((uint64_t)il2cpp_array_types + offset);
            for (int i = 0; i < types.size(); i++)
            {
                *(void**)((uint64_t)array_elements + i * sizeof(void*)) = BNM::ExportCall::TypeGetObject((types.at(i))->Type());
            }
            BNM::Method* MakeGenericType_method = ((BNM::Class*)(BNM::ExportCall::ObjectGetClass(BNM::ExportCall::TypeGetObject(this->Type()))))->Method("MakeGenericType", 1);
            void* (*MakeGenericType)(void*, void*) = (void* (*)(void*, void*))((void*)(MakeGenericType_method->VA()));
            return (BNM::Class*)(BNM::ExportCall::ClassFromSystemType(MakeGenericType((BNM::ExportCall::TypeGetObject(this->Type())), il2cpp_array_types)));
        }
    };

    struct Object
    {
    public:
        // Returns class of object.
        BNM::Class* Class()
        {
            return (BNM::Class*)BNM::ExportCall::ObjectGetClass((void*)this);
        }

        static BNM::Object* New(BNM::Class* klass)
        {
            return (BNM::Object*)BNM::ExportCall::ObjectNew((void*)klass);
        }

        BNM::Field* Field(const char* name)
        {
            return (BNM::Field*)(BNM::ExportCall::FieldFromName((void*)(this->Class()), name));
        }
    };

    struct Type
    {
    public:
        BNM::Class* Class()
        {
            return (BNM::Class*)BNM::ExportCall::ClassFromType((void*)this);
        }
    };
}