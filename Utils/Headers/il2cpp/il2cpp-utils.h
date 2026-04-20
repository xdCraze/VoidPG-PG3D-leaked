#pragma once
#define IL2CPP
#include "il2cpp-types.h"
#include "il2cpp-tabledefs.h"

#define DO_API(r, n, p) r (*n) p

#include "il2cpp-api-functions.h"

#undef DO_API

#include <Windows.h>
#include <vector>
#include <sstream>

typedef uintptr_t FieldPtr;
typedef unsigned long long MethodPtr;
typedef std::vector<const char*> FieldPattern;

auto AssemblyModuleHandle = GetModuleHandleA("GameAssembly.dll");
uint64_t il2cpp_base = (uint64_t)AssemblyModuleHandle;


namespace CommonLibImages
{
	const Il2CppImage* Corlib;
	const Il2CppImage* System;
	const Il2CppImage* UnityCoreModule;
	const Il2CppImage* UnityPhysicsModule;
	const Il2CppImage* AssemblyCSharp;
	const Il2CppImage* InputLegacyModule;
	const Il2CppImage* Photon3Unity3D;
	const Il2CppImage* SteamworksNet;
	const Il2CppImage* UserSessionManagement;
}

namespace CSharpTypeClass
{
	Il2CppClass* Boolean;
	Il2CppClass* Byte;
	Il2CppClass* Int16;
	Il2CppClass* Int32;
	Il2CppClass* Int64;
	Il2CppClass* Float;
	Il2CppClass* Double;
	Il2CppClass* Decimal;
	Il2CppClass* Char;
	Il2CppClass* String;
	Il2CppClass* Object;
	Il2CppClass* Array;
}



struct SignatureCondition {
    const char* modifier = nullptr;
    const char* typeName = nullptr;
    const char* name = nullptr;
    std::vector<const char*> paramTypeName;
    bool CalcNegative = false;
};

struct SignaturePattern
{
    const char* modifier = nullptr;
    const char* typeName = nullptr;
    const char* name = nullptr;
    std::vector<const char*> paramTypeName;
    int Index = 0;
    bool CalcNegative = false;
};

#define LOG_PROPLAM(msg, ...);
#define LOG_INFO(msg, ...);

bool StringContains(std::string str, std::string ValToFind)
{
    if (str.find(ValToFind) != std::string::npos) { return true; }
    return false;
}

std::string ReplaceString(std::string str, std::string ToReplace, std::string ReplaceWith)
{
    size_t pos = str.find(ToReplace);
    while (pos != std::string::npos) {
        str.replace(pos, ToReplace.length(), ReplaceWith);
        pos = str.find(ToReplace, pos + ReplaceWith.length());
    }
    return str;
}

#define NAME_CHECK(klass, name) strcmp(il2cpp_class_get_name(klass), name) == 0
#define CHECK_CLASSIZE(klass, size) il2cpp_class_get_data_size(klass) == size
#define NAMESPACE_CHECK(klass, namespaze) strcmp(il2cpp_class_get_namespace(klass), namespaze) == 0
#define ASSEMBLY_CHECK(klass, assemblyname) strcmp(il2cpp_class_get_assemblyname(klass), assemblyname) == 0
bool FieldCountIsMoreThan(Il2CppClass* klass, int value) {
    if (klass->field_count > value) return true;
    return false;
}
bool FieldCountIsLessThan(Il2CppClass* klass, int value) {
    if (klass->field_count < value) return true;
    return false;
}
bool MethodCountIsLessThan(Il2CppClass* klass, int value) {
    if (klass->method_count < value) return true;
    return false;
}
bool MethodCountIsMoreThan(Il2CppClass* klass, int value) {
    if (klass->method_count > value) return true;
    return false;
}
#define GET_FIELD(type, location) *(type*)((uint64_t)location)
#define EDIT_FIELD(type, location, editValue) GET_FIELD(type, location) = editValue;
bool CLASS_VALUETYPE_CHECK(Il2CppClass* klass, const char* valuetype) {
    std::stringstream outPut;
    auto flags = il2cpp_class_get_flags(klass);
    auto is_valuetype = il2cpp_class_is_valuetype(klass);
    auto is_enum = il2cpp_class_is_enum(klass);
    if (flags & TYPE_ATTRIBUTE_INTERFACE) {
        outPut << "interface";
    }
    else if (is_enum) {
        outPut << "enum";
    }
    else if (is_valuetype) {
        outPut << "struct";
    }
    else {
        outPut << "class";
    }
    if (strcmp(outPut.str().c_str(), valuetype) == 0) return true;
    return false;
}










namespace Il2CppDumper { // modified by Sxitxma
    std::string get_method_modifier(uint32_t flags) {
        std::stringstream outPut;
        auto access = flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;
        switch (access) {
        case METHOD_ATTRIBUTE_PRIVATE:
            outPut << "private ";
            break;
        case METHOD_ATTRIBUTE_PUBLIC:
            outPut << "public ";
            break;
        case METHOD_ATTRIBUTE_FAMILY:
            outPut << "protected ";
            break;
        case METHOD_ATTRIBUTE_ASSEM:
        case METHOD_ATTRIBUTE_FAM_AND_ASSEM:
            outPut << "internal ";
            break;
        case METHOD_ATTRIBUTE_FAM_OR_ASSEM:
            outPut << "protected internal ";
            break;
        }
        if (flags & METHOD_ATTRIBUTE_STATIC) {
            outPut << "static ";
        }
        if (flags & METHOD_ATTRIBUTE_ABSTRACT) {
            outPut << "abstract ";
            if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
                outPut << "override ";
            }
        }
        else if (flags & METHOD_ATTRIBUTE_FINAL) {
            if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
                outPut << "sealed override ";
            }
        }
        else if (flags & METHOD_ATTRIBUTE_VIRTUAL) {
            if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_NEW_SLOT) {
                outPut << "virtual ";
            }
            else {
                outPut << "override ";
            }
        }
        if (flags & METHOD_ATTRIBUTE_PINVOKE_IMPL) {
            outPut << "extern ";
        }
        return outPut.str();
    }
    std::string get_method_modifier2(uint32_t flags) {
        std::string _ = get_method_modifier(flags);
        _.pop_back(); return _;
    }

    std::string Field_ReturnType(FieldInfo* field)
    {
        auto field_type = il2cpp_field_get_type(field);
        auto field_class = il2cpp_class_from_type(field_type);
        return std::string(il2cpp_class_get_name(field_class));
    }

    std::string GetFullType(const Il2CppType* type) { // Shows shit like Dictionary<TKey, TValue>, List<...> etc. 
        std::string _ = "";
        if (type->type == IL2CPP_TYPE_GENERICINST) {
            Il2CppGenericClass* genericClass = type->data.generic_class;
            _ = il2cpp_class_get_name(genericClass->cached_class);
            _.pop_back(); _.pop_back();
            _ += "<";
            const Il2CppGenericInst* classInst = genericClass->context.class_inst;
            if (classInst) {
                for (uint32_t i = 0; i < classInst->type_argc; ++i) {
                    const Il2CppType* argType = classInst->type_argv[i];
                    Il2CppClass* argClass = il2cpp_class_from_type(argType);
                    if (argClass) {
                        _ += GetFullType(argType);
                    }
                    else {
                        _ += "UnknownType";
                    }

                    if (i < classInst->type_argc - 1) {
                        _ += ", ";
                    }
                }
            }
            _ += ">";
        }
        else {
            Il2CppClass* typeClass = il2cpp_class_from_type(type);
            if (typeClass) {
                _ += il2cpp_class_get_name(typeClass);
            }
        }
        return _;
    }


#define skibidi_lower(str) static_cast<char>(std::tolower(str[0]))
    std::string get_return_type_name(const char* type_name, bool OBF = false, const MethodInfo* method = nullptr, int param = 0) {

        if (method != nullptr) {
            int param_count = (int)il2cpp_method_get_param_count(method);
            auto paramClass = il2cpp_class_from_type(il2cpp_method_get_param(method, param));
            bool is_enum = il2cpp_class_is_enum(paramClass);
            if (is_enum) {
                if (OBF) return "OBF(\"ENUM\")";
                return "\"ENUM\"";
            }
        }

        if (type_name == nullptr || type_name == "") return "";
        const char* alphabet[] = {
            "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
            "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", ".", "<", ">", "_"
        };
        bool SuccessSkibidi = false;
        for (int i = 0; i < std::size(alphabet); i++) {
            if (skibidi_lower(type_name) == (const char)*alphabet[i]) {
                SuccessSkibidi = true;
                break;
            }
        }
        if (SuccessSkibidi) {
            if (OBF) return "OBF(\"" + std::string(type_name) + "\")";
            return "\"" + std::string(type_name) + "\"";
        }
        else {
            return "nullptr";
        }
    }

    bool _il2cpp_type_is_byref(const Il2CppType* type) {
        auto byref = type->byref;
        if (il2cpp_type_is_byref) {
            byref = il2cpp_type_is_byref(type);
        }
        return byref;
    }


    // Just found this shit right after I completely modified the runtime dumper :skull:
    bool IsBasicLatin(int32_t x) noexcept
    {
        return x >= 0x0020 && x <= 0x007F;
    }

    bool IsObfuscated(std::string str)
    {
        std::string moment;
        for (auto it = std::find_if(str.begin(), str.end(), IsBasicLatin); it != str.end(); it++) {
            moment += std::string(it, it + 1);
        }

        return moment.empty();
    }


    std::string GetMethodSignaturePattern(const MethodInfo* method) {
        std::stringstream outPut;

        std::string methodTypeName = il2cpp_class_get_name(il2cpp_class_from_type(il2cpp_method_get_return_type(method)));
        std::string methodName = il2cpp_method_get_name(method);

        uint32_t iflags = 0;
        auto flags = il2cpp_method_get_flags(method, &iflags);

        auto modif = get_method_modifier(flags);
        modif.pop_back();
        outPut << "{" << "\"" << modif << "\", ";

        if (IsObfuscated(methodTypeName)) {
            outPut << "nullptr" << ", ";
        }
        else {
            outPut << "\"" << methodTypeName << "\", ";
        }

        if (IsObfuscated(methodName)) {
            outPut << "nullptr" << ", {";
        }
        else {
            outPut << "\"" << methodName << "\", {";
        }

        auto param_count = il2cpp_method_get_param_count(method);
        bool first = true;
        for (int i = 0; i < (int)param_count; ++i) {
            auto param = il2cpp_method_get_param(method, i);
            std::string paramTypeName = il2cpp_class_from_type(param)->name;

            if (il2cpp_class_is_enum(il2cpp_class_from_type(param))) {
                outPut << (first ? "\"ENUM\"" : ", \"ENUM\"");
                first = false;
            }
            else if (IsObfuscated(paramTypeName)) {
                outPut << (first ? "nullptr" : ", nullptr");
                first = false;
            }
            else {
                outPut << (first ? "\"" : ", \"") << paramTypeName << "\"";
                first = false;
            }

        }

        outPut << "}};";

        return outPut.str();
    }

    std::string GetMethodSignaturePatternV2(const MethodInfo* method)
    {
        std::string ___ = GetMethodSignaturePattern(method);
        ___.pop_back(); return ___;
    }


    std::string dump_field_pattern(Il2CppClass* klass) {
        std::stringstream outPut;
        outPut << "\t// FieldPattern: {";

        void* iter = nullptr;
        while (auto field = il2cpp_class_get_fields(klass, &iter)) {

            auto fieldClass = il2cpp_class_from_type(il2cpp_field_get_type(field));
            std::string name = il2cpp_class_get_name(fieldClass);

            if (!IsObfuscated(name)) {
                outPut << "\"" << il2cpp_class_get_name(fieldClass) << "\", ";
            }
            else {
                outPut << "nullptr, ";
            }
        }

        auto strOut = outPut.str();

        if (strOut.length() > 18) {
            strOut.pop_back();
            strOut.pop_back();
        }

        return strOut + "};\n\n";
    }

    std::string dump_field_pattern_v2(Il2CppClass* klass) {
        if (klass == nullptr) return "NULL";
        std::stringstream outPut;
        outPut << "{";

        void* iter = nullptr;
        while (auto field = il2cpp_class_get_fields(klass, &iter)) {

            auto fieldClass = il2cpp_class_from_type(il2cpp_field_get_type(field));
            std::string name = il2cpp_class_get_name(fieldClass);

            if (!IsObfuscated(name)) {
                outPut << "\"" << il2cpp_class_get_name(fieldClass) << "\", ";
            }
            else {
                outPut << "nullptr, ";
            }
        }

        auto strOut = outPut.str();

        if (strOut.length() > 18) {
            strOut.pop_back();
            strOut.pop_back();
        }

        return strOut + "}";
    }

    // modified by Sxitxma
    std::string dump_method(Il2CppClass* klass, bool ObfuscatedToo = false) {
        std::stringstream outPut;
        outPut << "\n\t// Methods\n\n";
        void* iter = nullptr;
        uintptr_t MethodIndex = 0x0;
        while (auto method = il2cpp_class_get_methods(klass, &iter)) {
            //TODO attribute
            if (method->methodPointer) {
                uint32_t Skibidi = 0;
                int param_count = (int)il2cpp_method_get_param_count(method);
                auto Skibidi2 = il2cpp_method_get_flags(method, &Skibidi);
                outPut << "\t// SignaturePattern"; if (ObfuscatedToo) outPut << " (OBF)";
                outPut << ": {";
                if (ObfuscatedToo) outPut << "OBF(\"" << get_method_modifier2(Skibidi2) << "\"), ";
                else outPut << "\"" << get_method_modifier2(Skibidi2) << "\", ";
                outPut << get_return_type_name(il2cpp_class_get_name(il2cpp_class_from_type(il2cpp_method_get_return_type(method))), ObfuscatedToo)
                    << ", " << /*I know the name here doesnt fit, shut up nigga*/get_return_type_name(il2cpp_method_get_name(method), ObfuscatedToo) << ", {";

#define get_param_name_method(method1, obfV, overload1, ImRunningOutOfIdeasDawg, iParam) get_return_type_name(il2cpp_class_get_name(il2cpp_class_from_type(il2cpp_method_get_param(method1, overload1))), obfV, ImRunningOutOfIdeasDawg, iParam)
                if (param_count > 1) {
                    for (int i = 0; i < param_count; i++) {
                        std::string nigger = get_param_name_method(method, ObfuscatedToo, i, method, i);
                        if (i == param_count - 1) {
                            outPut << nigger;
                        }
                        else {
                            outPut << nigger << ", ";
                        }
                    }
                }
                else {
                    for (int i = 0; i < param_count; i++) {
                        outPut << get_param_name_method(method, ObfuscatedToo, i, method, i);
                    }
                }

                outPut << "}};\n";

                outPut << "\t// Index: 0x";
                outPut << std::hex << (uint64_t)MethodIndex; MethodIndex += 0x1;
                outPut << " Offset: 0x";
                outPut << std::hex << (uint64_t)method->methodPointer - il2cpp_base;
                outPut << " VA: 0x";
                outPut << std::hex << (uint64_t)method->methodPointer;
            }
            else {
                outPut << "\t// RVA: 0x VA: 0x0";
            }
            outPut << "\n\t";
            uint32_t iflags = 0;
            auto flags = il2cpp_method_get_flags(method, &iflags);
            outPut << get_method_modifier(flags);
            auto return_type = il2cpp_method_get_return_type(method);
            if (_il2cpp_type_is_byref(return_type)) {
                outPut << "ref ";
            }
            auto return_class = il2cpp_class_from_type(return_type);
            outPut << Il2CppDumper::GetFullType(return_type) << " " << il2cpp_method_get_name(method) << "(";
            auto param_count = il2cpp_method_get_param_count(method);
            for (int i = 0; i < (int)param_count; ++i) {
                auto param = il2cpp_method_get_param(method, i);
                auto attrs = param->attrs;
                if (_il2cpp_type_is_byref(param)) {
                    if (attrs & PARAM_ATTRIBUTE_OUT && !(attrs & PARAM_ATTRIBUTE_IN)) {
                        outPut << "out ";
                    }
                    else if (attrs & PARAM_ATTRIBUTE_IN && !(attrs & PARAM_ATTRIBUTE_OUT)) {
                        outPut << "in ";
                    }
                    else {
                        outPut << "ref ";
                    }
                }
                else {
                    if (attrs & PARAM_ATTRIBUTE_IN) {
                        outPut << "[In] ";
                    }
                    if (attrs & PARAM_ATTRIBUTE_OUT) {
                        outPut << "[Out] ";
                    }
                }
                auto parameter_class = il2cpp_class_from_type(param);
                if (param->type == IL2CPP_TYPE_GENERICINST) outPut << Il2CppDumper::GetFullType(param);
                else outPut << il2cpp_class_get_name(parameter_class);
                outPut << " " << il2cpp_method_get_param_name(method, i) << ", ";
            }
            if (param_count > 0) {
                outPut.seekp(-2, outPut.cur);
            }
            outPut << ") { }\n\n";
        }
        return outPut.str();
    }

    std::string dump_property(Il2CppClass* klass) {
        std::stringstream outPut;
        outPut << "\n\t// Properties\n";
        void* iter = nullptr;
        while (auto prop_const = il2cpp_class_get_properties(klass, &iter)) {
            //TODO attribute
            auto prop = const_cast<PropertyInfo*>(prop_const);
            auto get = il2cpp_property_get_get_method(prop);
            auto set = il2cpp_property_get_set_method(prop);
            auto prop_name = il2cpp_property_get_name(prop);
            outPut << "\t";
            Il2CppClass* prop_class = nullptr;
            uint32_t iflags = 0;
            if (get) {
                outPut << get_method_modifier(il2cpp_method_get_flags(get, &iflags));
                prop_class = il2cpp_class_from_type(il2cpp_method_get_return_type(get));
            }
            else if (set) {
                outPut << get_method_modifier(il2cpp_method_get_flags(set, &iflags));
                auto param = il2cpp_method_get_param(set, 0);
                prop_class = il2cpp_class_from_type(param);
            }
            if (prop_class) {
                const Il2CppType* skibidi = il2cpp_class_get_type(prop_class);
                outPut << Il2CppDumper::GetFullType(skibidi) << " " << prop_name << " { ";
                if (get) {
                    outPut << "get; ";
                }
                if (set) {
                    outPut << "set; ";
                }
                outPut << "}\n";
            }
            else {
                if (prop_name) {
                    outPut << " // unknown property " << prop_name;
                }
            }
        }
        return outPut.str();
    }

    std::string dump_field(Il2CppClass* klass) {
        std::stringstream outPut;
        void* iter = nullptr;
        void* iter2 = nullptr;
        uintptr_t FieldIndex = 0x0;

        outPut << "\n\t// Fields\n\n";

        outPut << "\t// FieldPattern: {";
        int FieldAt = 0;
        int FieldsCount = (int)klass->field_count;
#define get_param_name_field(field1) get_return_type_name(il2cpp_class_get_name(il2cpp_class_from_type(il2cpp_field_get_type(field1))))
        while (auto field = il2cpp_class_get_fields(klass, &iter)) {
            FieldAt += 1;
            if (FieldAt == FieldsCount) {
                outPut << get_param_name_field(field);
            }
            else {
                outPut << get_param_name_field(field) << ", ";
            }
        }

        outPut << "};\n\n";

        auto is_enum = il2cpp_class_is_enum(klass);

        while (auto field = il2cpp_class_get_fields(klass, &iter2)) {
            //TODO attribute
            outPut << "\t";
            auto attrs = il2cpp_field_get_flags(field);
            auto access = attrs & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK;
            switch (access) {
            case FIELD_ATTRIBUTE_PRIVATE:
                outPut << "private ";
                break;
            case FIELD_ATTRIBUTE_PUBLIC:
                outPut << "public ";
                break;
            case FIELD_ATTRIBUTE_FAMILY:
                outPut << "protected ";
                break;
            case FIELD_ATTRIBUTE_ASSEMBLY:
            case FIELD_ATTRIBUTE_FAM_AND_ASSEM:
                outPut << "internal ";
                break;
            case FIELD_ATTRIBUTE_FAM_OR_ASSEM:
                outPut << "protected internal ";
                break;
            }
            if (attrs & FIELD_ATTRIBUTE_LITERAL) {
                outPut << "const ";
            }
            else {
                if (attrs & FIELD_ATTRIBUTE_STATIC) {
                    outPut << "static ";
                }
                if (attrs & FIELD_ATTRIBUTE_INIT_ONLY) {
                    outPut << "readonly ";
                }
            }
            auto field_type = il2cpp_field_get_type(field);
            auto field_class = il2cpp_class_from_type(field_type);
            outPut << GetFullType(field_type) << " " << il2cpp_field_get_name(field);
            if (attrs & FIELD_ATTRIBUTE_LITERAL && is_enum) {
                uint64_t val = 0;
                il2cpp_field_static_get_value(field, &val);
                outPut << " = " << std::dec << val;
            };
            outPut << "; // Index: 0x" << std::hex << FieldIndex << " Offset: 0x" << std::hex << il2cpp_field_get_offset(field) << "\n";
            FieldIndex += 0x1; 
        }
        return outPut.str();
    }

    std::string dump_type(const Il2CppType* type, bool ObfuscatedToo = false) {
        std::stringstream outPut;
        auto* klass = il2cpp_class_from_type(type);
        outPut << "\n// Namespace: " << (strlen(il2cpp_class_get_namespace(klass)) == 0 ? "none" : il2cpp_class_get_namespace(klass)) << "  ClassDataSize: " << il2cpp_class_get_data_size(klass) << "  FieldCount: " << std::to_string(klass->field_count) << "  MethodCount: " << std::to_string(klass->method_count) << "\n";
        auto flags = il2cpp_class_get_flags(klass);
        if (flags & TYPE_ATTRIBUTE_SERIALIZABLE) {
            outPut << "[Serializable]\n";
        }
        //TODO attribute
        auto is_valuetype = il2cpp_class_is_valuetype(klass);
        auto is_enum = il2cpp_class_is_enum(klass);
        auto visibility = flags & TYPE_ATTRIBUTE_VISIBILITY_MASK;
        switch (visibility) {
        case TYPE_ATTRIBUTE_PUBLIC:
        case TYPE_ATTRIBUTE_NESTED_PUBLIC:
            outPut << "public ";
            break;
        case TYPE_ATTRIBUTE_NOT_PUBLIC:
        case TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM:
        case TYPE_ATTRIBUTE_NESTED_ASSEMBLY:
            outPut << "internal ";
            break;
        case TYPE_ATTRIBUTE_NESTED_PRIVATE:
            outPut << "private ";
            break;
        case TYPE_ATTRIBUTE_NESTED_FAMILY:
            outPut << "protected ";
            break;
        case TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM:
            outPut << "protected internal ";
            break;
        }
        if (flags & TYPE_ATTRIBUTE_ABSTRACT && flags & TYPE_ATTRIBUTE_SEALED) {
            outPut << "static ";
        }
        else if (!(flags & TYPE_ATTRIBUTE_INTERFACE) && flags & TYPE_ATTRIBUTE_ABSTRACT) {
            outPut << "abstract ";
        }
        else if (!is_valuetype && !is_enum && flags & TYPE_ATTRIBUTE_SEALED) {
            outPut << "sealed ";
        }
        if (flags & TYPE_ATTRIBUTE_INTERFACE) {
            outPut << "interface ";
        }
        else if (is_enum) {
            outPut << "enum ";
        }
        else if (is_valuetype) {
            outPut << "struct ";
        }
        else {
            outPut << "class ";
        }
        outPut << il2cpp_class_get_name(klass);
        std::vector<std::string> extends;
        auto parent = il2cpp_class_get_parent(klass);
        if (!is_valuetype && !is_enum && parent) {
            auto parent_type = il2cpp_class_get_type(parent);
            if (parent_type->type != IL2CPP_TYPE_OBJECT) {
                extends.emplace_back(il2cpp_class_get_name(parent));
            }
        }
        void* iter = nullptr;
        while (auto itf = il2cpp_class_get_interfaces(klass, &iter)) {
            extends.emplace_back(il2cpp_class_get_name(itf));
        }
        if (!extends.empty()) {
            outPut << " : " << extends[0];
            for (int i = 1; i < extends.size(); ++i) {
                outPut << ", " << extends[i];
            }
        }
        outPut << "\n{";
        outPut << dump_field(klass);
        outPut << dump_property(klass);
        outPut << dump_method(klass, ObfuscatedToo);
        //TODO EventInfo
        outPut << "}\n";
        return outPut.str();
    }

    std::string DumpClass(Il2CppClass* klass) {
        return dump_type(il2cpp_class_get_type(const_cast<Il2CppClass*>(klass)));
    }

    void Dump(const char* fileName, bool ObfuscatedToo = false) {
        auto domain = il2cpp_domain_get();
        il2cpp_thread_attach(domain);

        std::stringstream imageOutput;
        size_t size;
        auto assemblies = il2cpp_domain_get_assemblies(domain, &size);

        for (int i = 0; i < size; ++i) {
            auto image = il2cpp_assembly_get_image(assemblies[i]);
            imageOutput << "// Image " << i << ": " << il2cpp_image_get_name(image) << "\n";
        }

        std::vector<std::string> outPuts;
        if (il2cpp_image_get_class) {
            std::stringstream imageStr;
            for (int i = 0; i < size; ++i) {
                auto image = il2cpp_assembly_get_image(assemblies[i]);
                std::stringstream imageStr;
                imageStr << "\n// Dll : " << il2cpp_image_get_name(image);
                auto classCount = il2cpp_image_get_class_count(image);
                for (int j = 0; j < classCount; ++j) {
                    auto klass = il2cpp_image_get_class(image, j);
                    auto type = il2cpp_class_get_type(const_cast<Il2CppClass*>(klass));
                    auto outPut = imageStr.str() + "\n// Class Number " + std::to_string(j) + dump_type(type, ObfuscatedToo);
                    outPuts.push_back(outPut);
                }
            }
        }

        FILE* file;
        fopen_s(&file, fileName, "w+");
        std::ofstream out(file);
        out << imageOutput.str();
        auto count = outPuts.size();
        for (int i = 0; i < count; ++i) {
            out << outPuts[i];
        }
        fclose(file);
    }
}








namespace Il2CppUtils
{
    long il2cpp_base = 0;
    Il2CppDomain* domain;
    size_t libCount;
    const Il2CppAssembly** libs;

    std::string ksdjhfjebfhebfgefb() {
        HMODULE pe_base = LoadLibraryExA("GameAssembly.dll", NULL, DONT_RESOLVE_DLL_REFERENCES);
        PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)pe_base;
        PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((BYTE*)dos_header + dos_header->e_lfanew);

        PIMAGE_OPTIONAL_HEADER optional_header = (PIMAGE_OPTIONAL_HEADER)&nt_headers->OptionalHeader;
        PIMAGE_DATA_DIRECTORY export_data_directory = &(optional_header->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]);
        PIMAGE_EXPORT_DIRECTORY export_directory = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)pe_base + export_data_directory->VirtualAddress);

        DWORD name_count = export_directory->NumberOfNames;
        PDWORD export_name_table = (PDWORD)((BYTE*)pe_base + export_directory->AddressOfNames);

        std::string protected_export = OBF("_wasting_your_life");

        for (DWORD i = 0; i < export_directory->NumberOfNames; i++) {
            char* name = (char*)((BYTE*)pe_base + export_name_table[i]);
            std::string name_buf = std::string(name);
            if (name_buf.find(protected_export) != std::string::npos) {
                return name_buf;
            }
        }
        return OBF("il2cpp_domain_get_assemblies");
    }

    const Il2CppImage* ResolveImage(Il2CppDomain* _domain, const char* dll)
    {
        const Il2CppAssembly* assembly = nullptr;
        while (assembly == nullptr)
        {
            assembly = il2cpp_domain_assembly_open(_domain, dll);
        }

        auto img = il2cpp_assembly_get_image(assembly);
        return img;
    }

    /*

        #define DO_API(r, n, p) {													     \
            const char* name = #n;                                                  \
            n = (r (*) p) GetProcAddress(AssemblyModuleHandle, name); \
        }
    */
    static inline bool INIT()
    {
    #define DO_API(r, n, p) {													     \
        const char* name = #n;                                                  \
        if (strcmp(name, "il2cpp_domain_get_assemblies") != 0) {n = (r (*) p) GetProcAddress(AssemblyModuleHandle, name); } else {n = (r (*) p) GetProcAddress(AssemblyModuleHandle, Il2CppUtils::ksdjhfjebfhebfgefb().c_str());} \
	}

#include "il2cpp-api-functions.h"

#undef DO_API

        while (il2cpp_get_corlib == nullptr || il2cpp_get_corlib() == nullptr)
        {
            return false;
        }

        while (!il2cpp_is_vm_thread(nullptr))
        {
            Sleep(1);
        }

        domain = il2cpp_domain_get();
        il2cpp_thread_attach(domain);

        CommonLibImages::Corlib = il2cpp_get_corlib();
        CommonLibImages::System = ResolveImage(domain, OBF("System.dll"));
        CommonLibImages::AssemblyCSharp = ResolveImage(domain, OBF("Assembly-CSharp.dll"));
        CommonLibImages::UnityCoreModule = ResolveImage(domain, OBF("UnityEngine.CoreModule.dll"));
        CommonLibImages::UnityPhysicsModule = ResolveImage(domain, OBF("UnityEngine.PhysicsModule.dll"));
        CommonLibImages::InputLegacyModule = ResolveImage(domain, OBF("UnityEngine.InputLegacyModule.dll"));
        CommonLibImages::Photon3Unity3D = ResolveImage(domain, OBF("Photon3Unity3D.dll"));
        CommonLibImages::SteamworksNet = ResolveImage(domain, OBF("com.rlabrecque.steamworks.net.dll"));
        CommonLibImages::UserSessionManagement = ResolveImage(domain, OBF("UserSessionManagement.dll"));

        //libs = il2cpp_domain_get_assemblies(domain, &libCount); // dumb nigga removing il2cpp_domain_get_assemblies from export table wont fix anything

        /*for(int i = 0; i < libCount; ++i)
        {
            const Il2CppImage* img = il2cpp_assembly_get_image(libs[i]);
            const char* img_name = il2cpp_image_get_name(img);

            if(strcmp(img_name, OBF("Assembly-CSharp.dll")) == 0)
            {
                CommonLibImages::AssemblyCSharp = img;
            }
            if(strcmp(img_name, OBF("UnityEngine.CoreModule.dll")) == 0)
            {
                CommonLibImages::UnityCoreModule = img;
            }
            if(strcmp(img_name, OBF("UnityEngine.InputLegacyModule.dll")) == 0)
            {
                CommonLibImages::InputLegacyModule = img;
            }
            if(strcmp(img_name, OBF("Photon3Unity3D.dll")) == 0)
            {
                CommonLibImages::Photon3Unity3D = img;
            }
            if(strcmp(img_name, OBF("com.rlabrecque.steamworks.net.dll")) == 0)
            {
                CommonLibImages::SteamworksNet = img;
            }
            if(strcmp(img_name, OBF("UserSessionManagement.dll")) == 0)
            {
                CommonLibImages::UserSessionManagement = img;
            }
        }*/

#define DEFAULTS_INIT(field, ns, n) CSharpTypeClass::field = il2cpp_class_from_name(CommonLibImages::Corlib, OBF(ns), OBF(n));

        DEFAULTS_INIT(Array, "System", "Boolean");
        DEFAULTS_INIT(Byte, "System", "Byte");
        DEFAULTS_INIT(Int16, "System", "Int16");
        DEFAULTS_INIT(Int32, "System", "Int32");
        DEFAULTS_INIT(Int64, "System", "Int64");
        DEFAULTS_INIT(Float, "System", "Single");
        DEFAULTS_INIT(Double, "System", "Double");
        DEFAULTS_INIT(Decimal, "System", "Decimal");
        DEFAULTS_INIT(Char, "System", "Char");
        DEFAULTS_INIT(String, "System", "String");
        DEFAULTS_INIT(Object, "System", "Object");
        DEFAULTS_INIT(Array, "System", "Array");

#undef DEFAULTS_INIT
        return true;
    }


    std::hash<const char*> cacheKeyHasher;
    std::unordered_map<uint32_t, Il2CppClass*> classMap;
    std::unordered_map<uint32_t, size_t> fieldCache;

#define CONCAT_CHAR(str0, str1) std::string(std::string(str0) + str1).c_str()


#define REG_CLASS(klass, str) Il2CppUtils::_RegisterClass(klass, str)
#define REG_CLASS_NAMECHECK(klass, name)  if(NAME_CHECK(klass, name)) { REG_CLASS(klass, name); }
#define GET_CLASS(str) Il2CppUtils::GetClass(str)
#define GET_METHOD(klass, methodname) Il2CppUtils::GetMethod(klass, methodname);

    const MethodInfo* GetMethod(Il2CppClass* klass, const char* MethodName, int sameMethodNameSkip = 0) {
        while (klass->methods == nullptr) {
            Sleep(1);
        }
        int nig = 0;
        for (int i = 0; i < klass->method_count; i++) {

            const MethodInfo* method = klass->methods[i];

            if (strcmp(il2cpp_method_get_name(method), MethodName) == 0) {

                if (nig < sameMethodNameSkip) {
                    nig++;
                    continue;
                }

                return method;
            }
        }
    }

    const MethodInfo* GetMethodFromIndex(Il2CppClass* klass, int index) {
        while (klass->methods == nullptr) {
            Sleep(1);
        }
        return klass->methods[index];
    }

    void _RegisterClass(Il2CppClass* klass, const char* name) {
        if (klass == nullptr) {
            LOG_PROPLAM("First Arg (Il2CppClass*) is null");
            return;
        }

        classMap.insert({ cacheKeyHasher(name), klass });
    }
    Il2CppClass* GetClass(const char* name) {
        auto it = classMap.find((uint32_t)cacheKeyHasher(name));

        if (it == classMap.end()) {
            LOG_PROPLAM("Can't find %s.", name);
            return nullptr;
        }

        if (it->second == nullptr) {
            LOG_PROPLAM("%s is null", name);
            return nullptr;
        }

        return it->second;
    }


    std::string ReadList() {

        return "";
    }

    template<typename T>
    T UnboxIl2cppObject(Il2CppObject* obj) {
        return *static_cast<T*>(il2cpp_object_unbox(obj));
    }

    std::string GetMethodModifier(uint32_t flags) {
        std::stringstream outPut;
        auto access = flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;

        switch (access) {
        case METHOD_ATTRIBUTE_PRIVATE:
            outPut << "private ";
            break;
        case METHOD_ATTRIBUTE_PUBLIC:
            outPut << "public ";
            break;
        case METHOD_ATTRIBUTE_FAMILY:
            outPut << "protected ";
            break;
        case METHOD_ATTRIBUTE_ASSEM:
        case METHOD_ATTRIBUTE_FAM_AND_ASSEM:
            outPut << "internal ";
            break;
        case METHOD_ATTRIBUTE_FAM_OR_ASSEM:
            outPut << "protected internal ";
            break;
        }
        if (flags & METHOD_ATTRIBUTE_STATIC) {
            outPut << "static ";
        }
        if (flags & METHOD_ATTRIBUTE_ABSTRACT) {
            outPut << "abstract ";
            if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
                outPut << "override ";
            }
        }
        else if (flags & METHOD_ATTRIBUTE_FINAL) {
            if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
                outPut << "sealed override ";
            }
        }
        else if (flags & METHOD_ATTRIBUTE_VIRTUAL) {
            if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_NEW_SLOT) {
                outPut << "virtual ";
            }
            else {
                outPut << "override ";
            }
        }
        if (flags & METHOD_ATTRIBUTE_PINVOKE_IMPL) {
            outPut << "extern ";
        }

        return outPut.str();
    }

    MethodPtr GetMethodPointerFromIndex(Il2CppClass* klass, int index) {

        if (klass == nullptr) {
            return 0;
        }

        if (klass->method_count <= 0) {
            return 0;
        }

        while (klass->methods == nullptr) {
            Sleep(1);
        }

        const MethodInfo* method = klass->methods[index];

        if (method == nullptr) {
            return 0;
        }

        return (MethodPtr)method->methodPointer;
    }

    MethodPtr GetMethodPointerFromName(Il2CppClass* klass, const char* name, int sameMethodNameSkip = 0) {

        //LOGI("[Info] GetMethodPointerFromName");

        if (klass == nullptr) {
            LOG_PROPLAM("First arg (Il2CppClass) is null. %s", name);
            return 0;
        }

        //const MethodInfo* method = il2cpp_class_get_method_from_name(klass, name, argsCount); // this thing is broken.

        if (klass->method_count <= 0) {
            LOG_PROPLAM("No method founded in %s", il2cpp_class_get_name(klass));
            return 0;
        }

        while (klass->methods == nullptr) {
            Sleep(1);
        }

        int nig = 0;
        for (int i = 0; i < klass->method_count; i++) {

            const MethodInfo* method = klass->methods[i];

            if (strcmp(il2cpp_method_get_name(method), name) == 0) {

                if (nig < sameMethodNameSkip) {
                    nig++;
                    continue;
                }

                return (MethodPtr)method->methodPointer;
            }
        }

        //LOGI("[PROPLAM | GetMethodPointerFromName] Can't find %s", name);
        return 0;
    }

#define HANDLE_NULL_STR(str) std::string(str == nullptr ? "NULL" : str)
    std::string TraceMethod(const SignatureCondition& pattern) {

        std::string out = HANDLE_NULL_STR(pattern.modifier) + HANDLE_NULL_STR(pattern.typeName) + HANDLE_NULL_STR(pattern.name) + " ";

        if (!pattern.paramTypeName.empty()) {

            bool first = true;

            std::string str;

            for (int i = 0; i < std::size(pattern.paramTypeName); i++) {
                str += first ? HANDLE_NULL_STR(pattern.paramTypeName[i]) : ", " + HANDLE_NULL_STR(pattern.paramTypeName[i]);
                first = false;
            }

            out = +"{" + str + "}";
        }

        return out;
    }

    MethodPtr GetMethodPointer(Il2CppClass* klass, const SignatureCondition& pattern, int indexOffset) {

        if (klass == nullptr) {
            return 0;
        }

        //LOGI("Finding %s", TraceMethod(pattern).c_str());

        if (klass->method_count <= 0) {
            return 0;
        }

        while (klass->methods == nullptr) {
            Sleep(1);
        }

        for (int i = 0; i < klass->method_count; i++) {

            const MethodInfo* method = klass->methods[i];

            int checkScore = 0;

            // 0 = fail, 1 = skipped, 2 = success.
            int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

            uint32_t iflags = 0;
            uint32_t flags = il2cpp_method_get_flags(method, &iflags);

            std::string methodName = il2cpp_method_get_name(method);
            std::string methodModif = GetMethodModifier(flags);
            std::string methodTypeName = il2cpp_class_from_type(il2cpp_method_get_return_type(method))->name;
            int methodParamCount = il2cpp_method_get_param_count(method);

            methodModif.pop_back();

            //LOGI("Name Check %s", BOOL_TO_STRING(pattern.name == methodName));
            if (pattern.name == nullptr) {
                test1 = 1;
                checkScore++;
            }
            else if (methodName == pattern.name) {

                test1 = 2;
                checkScore++;
            }

            //LOGI("modifier Check %s", BOOL_TO_STRING(methodModif == pattern.modifier));
            if (pattern.modifier == nullptr) {
                test2 = 1;
                checkScore++;
            }
            else if (methodModif == pattern.modifier) {
                test2 = 2;
                checkScore++;
            }

            //LOGI("modifier Check %s", BOOL_TO_STRING(pattern.typeName == methodTypeName));
            if (pattern.typeName == nullptr) {
                test3 = 2;
                checkScore++;
            }
            else if (methodTypeName == pattern.typeName) {
                test3 = 2;
                checkScore++;
            }

            //LOGI("paramCount Check %s", BOOL_TO_STRING(pattern.paramCount == methodParamCount));
            if (pattern.paramTypeName.size() > 0 && pattern.paramTypeName.size() == methodParamCount) {

                int successParamScore = 0;

                //LOGI("param Check");
                for (int i2 = 0; i2 < pattern.paramTypeName.size(); ++i2) {

                    if (pattern.paramTypeName[i2] != nullptr) {

                        std::string typeName = pattern.paramTypeName[i2];
                        auto paramClass = il2cpp_class_from_type(il2cpp_method_get_param(method, i2));
                        bool is_enum = il2cpp_class_is_enum(paramClass);
                        bool is_value = il2cpp_class_is_valuetype(paramClass);

                        if (typeName == "ENUM" && is_enum) {

                            successParamScore++;
                        }
                        else if (typeName == "VALUE" && is_value && !is_enum) {

                            if (il2cpp_class_is_valuetype(il2cpp_class_from_type(il2cpp_method_get_param(method, i2)))) {

                                successParamScore++;
                            }
                        }
                        else if (typeName == il2cpp_class_from_type(il2cpp_method_get_param(method, i2))->name) {

                            successParamScore++;
                        }

                    }
                    else {
                        successParamScore++;
                    }
                }

                if (successParamScore == pattern.paramTypeName.size()) {
                    test4 = 2;
                    checkScore++;
                }
                else
                {
                    test4 = 0;
                }

            }
            else if (pattern.paramTypeName.size() == 0) {
                test4 = 1;
                checkScore++;
            }
            else {
                test4 = 0;
            }

            //LOGI("checking score %i", checkScore);
            /*LOGI("[Info] %s: Name Check: %i, Modifier Check: %i, TypeName Check: %i, ParamCount check: %i, ParamTypes check: %i, Check Score: %i",
                 methodName.c_str(), test1, test2, test3, test4, test5, checkScore);*/

            if (checkScore >= 4) {

                //LOGI("[Success] Got: %s %s %s | Target: %s %s %s", methodModif.c_str(), methodTypeName.c_str(), methodName.c_str()
                //, pattern.modifier.c_str(), pattern.typeName.c_str(), pattern.name.c_str());
                //LOGI("[Success]  Name Check: %i, Modifier Check: %i, TypeName Check: %i, ParamCount check: %i, ParamTypes check: %i, Check Score: %i",
                //test1, test2, test3, test4, test5, checkScore);

                return (MethodPtr)klass->methods[pattern.CalcNegative ? i - indexOffset : i + indexOffset]->methodPointer;
            }
        }

        return 0;
    }

    MethodPtr GetMethodPointerV2(Il2CppClass* klass, std::string pattern, int indexOffset = 0x0) {
        for (int i = 0; i < klass->method_count; i++) {
            const MethodInfo* method = klass->methods[i];
            if (strcmp(Il2CppDumper::GetMethodSignaturePatternV2(method).c_str(), pattern.c_str())) return (MethodPtr)klass->methods[i + indexOffset]->methodPointer;
        }
        return 0;
    }


    MethodPtr GetMethodPointer(Il2CppClass* klass, const SignaturePattern& pattern) {
        if (pattern.modifier == nullptr) { return Il2CppUtils::GetMethodPointerFromIndex(klass, pattern.Index); }
        return Il2CppUtils::GetMethodPointer(klass, { pattern.modifier, pattern.typeName, pattern.name, pattern.paramTypeName, pattern.CalcNegative }, pattern.Index);
    }

    MethodPtr GetMethodPointer(const char* klass, const SignaturePattern& pattern) {
        return Il2CppUtils::GetMethodPointer(GET_CLASS(klass), pattern);
    }


    // From Sxitxma: Credits to fedesito for the idea to save them in a list and then retrieve em from there
    std::unordered_map<std::string, uint64_t> SavedFieldsList; // Field Name

    uint64_t GetFieldPtr(void* instancePtr, int fieldindex) {
        if (instancePtr == nullptr) { return 0; }
        return (uint64_t)instancePtr + il2cpp_field_get_offset(&static_cast<Il2CppObject*>(instancePtr)->Il2CppClass.klass->fields[fieldindex]);
    }

    uint64_t GetFieldPtr(void* instancePtr, const char* fieldName) {
        if (instancePtr == nullptr) { return 0; }
        Il2CppClass* klass = static_cast<Il2CppObject*>(instancePtr)->Il2CppClass.klass;
        for (int i = 0; i < klass->field_count; i++) {
            FieldInfo field = klass->fields[i];
            if (strcmp(il2cpp_field_get_name(&field), fieldName) == 0) {
                return (uint64_t)instancePtr + il2cpp_field_get_offset(&field);
            }
        }
        return 0x0;
    }

    template <typename T> T& Field(void* instancePtr, const std::string& name, int fieldIndex) { 
        std::string key = name + OBF("::fields[") + std::to_string(fieldIndex) + OBF("]");
        auto it = SavedFieldsList.find(key);
        if (it != SavedFieldsList.end()) { return (T&)(*(T*)((uint64_t)it->second)); }
        SavedFieldsList[key] = GetFieldPtr(instancePtr, fieldIndex);
        return Field<T>(instancePtr, name, fieldIndex);
    }

    template <typename T> T& Field(void* instancePtr, const std::string& name, const std::string& fieldName)
    {
        std::string key = name + OBF("::") + fieldName;
        auto it = SavedFieldsList.find(key);
        if (it != SavedFieldsList.end()) { return (T&)(*(T*)((uint64_t)it->second)); }
        SavedFieldsList[key] = GetFieldPtr(instancePtr, fieldName.c_str());
        return Field<T>(instancePtr, name, fieldName);
    }



    template<typename T>
    T GetStaticField(Il2CppClass* klass, const char* fieldName) {
        void* iter = nullptr;
        while (auto field = il2cpp_class_get_fields(klass, &iter)) { // unoptimized idfc

            if (strcmp(fieldName, il2cpp_field_get_name(field)) == 0) {
                void* var;
                il2cpp_field_static_get_value(field, &var);
                return (T)var;
            }
        }

        return nullptr;
    }

    template<typename T>
    T GetStaticFieldByIndex(Il2CppClass* klass, int index) {

        if (klass == nullptr) {
            return nullptr;
        }

        if (klass->field_count > 0) {
            void* var;
            il2cpp_field_static_get_value(&klass->fields[index], &var);
            return (T)var;
        }

        return nullptr;
    }


    bool CheckContentCount(Il2CppClass* klass, std::pair<uint32_t, uint32_t> fieldCountPair, std::pair<uint32_t, uint32_t>  methodCountPair)
    {
        if (klass == nullptr) {
            LOG_PROPLAM("First arg (Il2CppClass*) is null.");
            return false;
        }

        return klass->field_count >= fieldCountPair.first && klass->field_count <= fieldCountPair.second &&
            klass->method_count >= methodCountPair.first && klass->method_count <= methodCountPair.second; //klass->field_count == fieldCount && klass->method_count == methodCount;
    }

    bool CheckContentCountV2(Il2CppClass* klass, std::pair<int, int> fieldCountPair, std::pair<int, int>  methodCountPair)
    {
        if (FieldCountIsMoreThan(klass, fieldCountPair.first - 1) && FieldCountIsLessThan(klass, fieldCountPair.second + 1) &&
            MethodCountIsMoreThan(klass, methodCountPair.first - 1) && MethodCountIsLessThan(klass, methodCountPair.second + 1)) return true;
        return false;
    }

    float CheckFieldPattern(Il2CppClass* klass, FieldPattern& pattern) {

        if (klass == nullptr) {
            return false;
        }

        int score = 0;

        void* iter = nullptr;
        while (auto field = il2cpp_class_get_fields(klass, &iter)) {

            auto fieldClass = il2cpp_class_from_type(il2cpp_field_get_type(field));

            if (fieldClass == nullptr) {
                continue;
            }

            if (pattern[score] == nullptr) {

                score++;
            }
            else if (strcmp(il2cpp_class_get_name(fieldClass), pattern[score]) == 0) {

                score++;
            }
        }

        return (float)score / (int)pattern.size();
    }

    bool CheckFieldPatternV2(Il2CppClass* klass, std::string patternString) { // Made by Sxitxma
        if (strcmp(Il2CppDumper::dump_field_pattern_v2(klass).c_str(), patternString.c_str()) == 0) return true;
        return false;
    }

    bool CheckFieldPatternV3(Il2CppClass* klass, std::string patternString) { // Made by Sxitxma - ONLY USE IF THE FIELD PATTERN IS REALLY LONG
        return StringContains(Il2CppDumper::dump_field_pattern_v2(klass), patternString);
    }

    // return true if this class has these args, otherwise false
    bool ClassPatternCheck(Il2CppClass* klass, std::pair<uint32_t, uint32_t> fieldCountPair, std::pair<uint32_t, uint32_t> methodCountPair, FieldPattern fieldPattern) {
        if (Il2CppUtils::CheckContentCount(klass, fieldCountPair, methodCountPair) && Il2CppUtils::CheckFieldPattern(klass, fieldPattern) == 1.0) {
            return true;
        }
        return false;
    }
    bool ClassPatternCheck(Il2CppClass* klass, uint32_t fieldCount, uint32_t methodCount, FieldPattern fieldPattern) {
        if (ClassPatternCheck(klass, { fieldCount, fieldCount }, { methodCount, methodCount }, fieldPattern)) {
            return true;
        }
        return false;
    }
    bool ClassPatternCheck(Il2CppClass* klass, uint32_t ClassDataSize, uint32_t fieldCount, uint32_t methodCount, FieldPattern fieldPattern) {
        if (Il2CppUtils::CheckContentCount(klass, { fieldCount, fieldCount }, { methodCount, methodCount }) && Il2CppUtils::CheckFieldPattern(klass, fieldPattern) == 1.0 && CHECK_CLASSIZE(klass, ClassDataSize)) {
            return true;
        }
        return false;
    }
    bool ClassPatternCheck(Il2CppClass* klass, uint32_t ClassDataSize, std::pair<uint32_t, uint32_t> fieldCountPair, std::pair<uint32_t, uint32_t> methodCountPair, FieldPattern fieldPattern) {
        if (Il2CppUtils::CheckContentCount(klass, fieldCountPair, methodCountPair) && Il2CppUtils::CheckFieldPattern(klass, fieldPattern) == 1.0 && CHECK_CLASSIZE(klass, ClassDataSize)) {
            return true;
        }
        return false;
    }
}