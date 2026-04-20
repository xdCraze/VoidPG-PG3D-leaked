#include <map>
#include <codecvt>
#include <execution>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <regex>
#include <psapi.h>
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

#include "Headers/obfusheader.h"

#include "Headers/Unity/Obfuscators.hpp"
#include "Headers/Unity/Defines.hpp"
#include "Headers/Unity/Structures/il2cpp.hpp"
#include "Headers/Unity/Structures/il2cppArray.hpp"
#include "Headers/Unity/Structures/il2cppDictionary.hpp"
#include "Headers/Unity/Structures/System_String.hpp"

#include "Headers/Utils.h"
#include "Headers/Filehandling.h"
#include "Headers/fslog.h"

#include "Headers/il2cpp/il2cpp-utils.h"
#include "Headers/BNM-IL2CPP/BNM.hpp"

#include "ImGui/misc/fonts/museosans.hpp"
#include "ImGui/misc/fonts/fa-solid-900.h"
#include "ImGui/misc/fonts/IconsFontAwesome6.h"

typedef unsigned long long MethodPtr;
typedef Unity::System_String monoString;


void CopyToClipboard(const std::string& text) {
    OpenClipboard(nullptr);
    EmptyClipboard();
    HGLOBAL _hGlobal = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    char* pGlobal = static_cast<char*>(GlobalLock(_hGlobal));
    if (pGlobal != nullptr) {
        memcpy(pGlobal, text.c_str(), text.size() + 1);
        GlobalUnlock(_hGlobal);
        SetClipboardData(CF_TEXT, _hGlobal);
    }
    CloseClipboard();
}

uintptr_t string2Offset(const char* c) {
    int base = 16;
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }
    return strtoull(c, nullptr, base);
}



uint64_t absolute(const char* offset) {
    return /*((uintptr_t)GetModuleHandleA("GameAssembly.dll")*/ il2cpp_base + string2Offset(offset);
}

void HOOK(uint64_t location, LPVOID detour, void* original)
{
    MH_STATUS create_hook = MH_CreateHook((LPVOID*)(location), detour, (LPVOID*)original);
    if (create_hook == MH_OK) MH_EnableHook((LPVOID*)(location));
}

#define HOOK_UPDATE(klass, ptr) HookUpdate(klass, (void *)ptr, (void **)&old##ptr)
void HookUpdate(Il2CppClass* klass, void* ptr, void** orig) {
    SignatureCondition CON{
            OBF("private"),
            OBF("Void"),
            OBF("Update")
    };
    MethodPtr POINTER = Il2CppUtils::GetMethodPointer(klass, CON, 0);
    HOOK(POINTER, ptr, orig);
}
void HookUpdate2(const char* className, LPVOID ptr, void* orig, const char* domainName = OBF("Assembly-CSharp"))
{
    HOOK(BNM::Domain().Assembly(domainName)->Image()->Class(className)->Method(OBF("Update"))->VA(), ptr, orig);
}

BNM::Class* AssemblyCSKlass(const char* classname)
{
    return BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image()->Class(classname);
}


namespace MonoString {
    monoString* New(const char* str) { // available methods: 0, any other value
        /*if (method == 0) */return (monoString*)il2cpp_string_new(str);
        /*
        static SignatureCondition funcC = {
                OBF("private static"),
                OBF("String"),
                OBF("Ctor"),
                {OBF("SByte*"), OBF("Int32"), OBF("Int32")}
        };
        static monoString* (*func)(const char* str, int startIndex, int length) = (monoString * (*)(const char*, int, int))Il2CppUtils::GetMethodPointer(CSharpTypeClass::String, funcC, 0);
        return func(str, 0, strlen(str));
        */
    }
}

namespace wfwefegergej { // Encoding

    Il2CppClass* fegsefafserg() { return static_cast<Il2CppClass*>((void*)BNM::Domain().Assembly(OBF("mscorlib"))->Image()->Class(OBF("System.Text.Encoding"))); }

    void* kdmkvdslkfcedkgbdrjged() { // get_UTF8
        auto func = (void* (*)())fegsefafserg()->methods[0x3F]->methodPointer; // Index 0x39
        return func();
    }

    monoString* _(void* bytes) { // GetString
        auto func = (monoString * (*)(void*, void*))fegsefafserg()->methods[0x3A]->methodPointer; // Index 0x34
        return func(kdmkvdslkfcedkgbdrjged(), bytes);
    }

    void* __(const char* str) { // GetBytes
        auto func = (void* (*)(void*, monoString*))fegsefafserg()->methods[0x24]->methodPointer; // Index 0x22
        return func(kdmkvdslkfcedkgbdrjged(), MonoString::New(str));
    }

}

enum class ConsoleColor {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    BrightBlack,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite,
    Reset
};
class Sxitxma {
public:
    static void SetColor(ConsoleColor colorName)
    {
        switch (colorName) {
        case ConsoleColor::Black:        printf("\033[30m"); break;
        case ConsoleColor::Red:          printf("\033[31m"); break;
        case ConsoleColor::Green:        printf("\033[32m"); break;
        case ConsoleColor::Yellow:       printf("\033[33m"); break;
        case ConsoleColor::Blue:         printf("\033[34m"); break;
        case ConsoleColor::Magenta:      printf("\033[35m"); break;
        case ConsoleColor::Cyan:         printf("\033[36m"); break;
        case ConsoleColor::White:        printf("\033[37m"); break;
        case ConsoleColor::BrightBlack:  printf("\033[90m"); break;
        case ConsoleColor::BrightRed:    printf("\033[91m"); break;
        case ConsoleColor::BrightGreen:  printf("\033[92m"); break;
        case ConsoleColor::BrightYellow: printf("\033[93m"); break;
        case ConsoleColor::BrightBlue:   printf("\033[94m"); break;
        case ConsoleColor::BrightMagenta:printf("\033[95m"); break;
        case ConsoleColor::BrightCyan:   printf("\033[96m"); break;
        case ConsoleColor::BrightWhite:  printf("\033[97m"); break;
        case ConsoleColor::Reset:        printf("\033[0m"); break;
        default:                         printf("\033[0m"); break;
        }
    }
    static void ResetColor()
    {
        SetColor(ConsoleColor::Reset);
    }
};


std::map<char, std::string> nfedkfmrjgnfnrhghrg = {
    {'a', "ofkrfgo"}, {'b', "ekgerjg"}, {'c', "wfefgrehrh"}, {'d', "wefegerhgo"},
    {'e', OBF("olekfekgrgh")}, {'f', "keefolerg"}, {'g', "odfkewdwoef"}, {'h', "010009wfe"},
    {'i', "dwef101201kaswso"}, {'j', OBF("sikdmwsjd")}, {'k', OBF("dontwwdrfhelp")}, {'l', OBF("uuid")},
    {'m', "ewkfeowsdegegw"}, {'n', "wpfker"}, {'o', "dkbnrbm"}, {'p', "mvkmvbekbeg"},
    {'q', "wsolfefcfolg"}, {'r', "lwfkmekgehg"}, {'s', OBF("odefgjret4")}, {'t', "ifejmfgr"},
    {'u', "oegjr"}, {'v', "aasdk"}, {'w', "plzheikxlp"}, {'x', "oekmfgrefgr"},
    {'y', "kijh"}, {'z', "dokenmgkg"}, {OBF(' '), OBF("02446eofgkm462erg")}, {'/', "0:kw2"},
    {':', "ejfmeddfe"}, {',', "::::::"}, {'.', "sailhhtrhyangegeghetrynagetsefefgomefuuegeglyang"},
    {';', "wdwdewfefeogjkrg"}, {'1', "edfeoegkmrgl"}, {'2', "wdwoesagkmrgl"}, {'3', "wdwfdwsfewfeg"},
    {'4', "oegkmrgl"}, {'5', "fwdwdoiegkrh"}, {'6', OBF("WhatTheSkibidiSigma")}, {'7', "eofgrmhg"},
    {'8', "feogekmg"}, {'9', "wfrhztjtrege"}, {'0', "wfeoigkeofegrg"}, {'ä', "eifjergiergmwfdweg"},
    {'ö', "eiogneikfeogmrhg"}, {'ü', "ieifmrkgrgrg"}, {'-', "dfiorfgkoeflkrghrt"}, {'|', "odfkeodfkeogrg"},
    {'*', "fgowewskfer"}, {'+', "owekmfoergefergr"}, {'!', "oefeodefrgrg"}, {'=', "efkwdwlfoerglwefeg"},
    {'?', "doefowskwodkeogerg"}, {'{', OBF("wofemgkemfsedfrg")}, {'}', OBF("dekfgnrfwdegfrg")},
    {'[', "oekmrgleferfgewf"}, {']', "oekmrgleferfgewfwefgwf"}, {'(', "weikfmedweoferofgwfwfw"},
    {')', "weikfmedweoferofgwfwfwsdwfw"}, {'<', "weikfmedweofswsfeerofgwfwfw"}, {'>', "weikfmedweofswsfwfefgewfeerofgwfwfwsd2"},
    {'$', "weikfmedweofswsfwfefgewfeerofwdfwf"}, {'%', "weikfmedweofswsfwdwwfefgewfeerof"}, {'&', "weikfmedweofs123434532wsfwfefgewfeerof"},
    {'#', "weikfmedweofs123434532"}, {'@', "ikefkwodeferfgwedf"}, {'^', "weikfmedweofs123434532wikf"}, {'_', OBF("ichkanndeutsch")},
    {'~', "weikfmedweofs123434234534523"}, {'`', "weikfmedweofs123434532wir353"}, {'´', "weikfmedweofs12343453438525"}, {'¨', "weikfmedweofs12343453249835"}
};


std::string irjfejfrnhgnrhjfjrgjrng(std::string wdmjnedfjkmefj) { // Sxitxma69 encode (std::string string)
    std::string dfeddeferfgrg;
    for (char efujehfeufjfg : wdmjnedfjkmefj) {
        if (nfedkfmrjgnfnrhghrg.find(efujehfeufjfg) != nfedkfmrjgnfnrhghrg.end()) {
            dfeddeferfgrg += nfedkfmrjgnfnrhghrg[efujehfeufjfg];
        }
        else {
            dfeddeferfgrg += efujehfeufjfg;
        }
    }
    return dfeddeferfgrg;
}

std::string ednferjnfejfnehjfnehfn(std::string wdmjnedfjkmefj, int rinrujnfgregrgn) { // Sxitxma69 encode (std::string string, int EncodeTimes)
    std::string _ = irjfejfrnhgnrhjfjrgjrng(wdmjnedfjkmefj);
    if (rinrujnfgregrgn < 2) return _;
    for (int i = 0; i < rinrujnfgregrgn - 1; i++)
        _ = irjfejfrnhgnrhjfjrgjrng(_);

    return _;
}


// StringContains (str, ValToFind): behave true as false and false as true
bool ofmefnrjhfgn(std::string eknfmerjfrhfgr, std::string wefnefherfhebfe)
{
    if (eknfmerjfrhfgr.find(wefnefherfhebfe) != std::string::npos) { return false; }
    return true;
}

// StringContainsV2 in case some nigger hooks StringContains
std::string ekfmefjerhfgrehg(std::string eknfejfehjfehjf, std::string efkmekfmejfnejhfnef)
{
    if (eknfejfehjfehjf.find(efkmekfmejfnejhfnef) != std::string::npos) {
        return irjfejfrnhgnrhjfjrgjrng(OBF("String does contain you fucking bitch")); // Sifejmfgrlwfkmekgehgdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergwefegerhgodkbnrbmolekfekgrghodefgjret402446eofgkm462ergwfefgrehrhdkbnrbmwpfkerifejmfgrofkrfgodwef101201kaswsowpfker02446eofgkm462ergkijhdkbnrbmoegjr02446eofgkm462ergkeefolergoegjrwfefgrehrhdontwwdrfhelpdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergekgerjgdwef101201kaswsoifejmfgrwfefgrehrh010009wfe
    }
    return irjfejfrnhgnrhjfjrgjrng(OBF("String does not contain you fucking bitch")); // Sifejmfgrlwfkmekgehgdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergwefegerhgodkbnrbmolekfekgrghodefgjret402446eofgkm462ergwpfkerdkbnrbmifejmfgr02446eofgkm462ergwfefgrehrhdkbnrbmwpfkerifejmfgrofkrfgodwef101201kaswsowpfker02446eofgkm462ergkijhdkbnrbmoegjr02446eofgkm462ergkeefolergoegjrwfefgrehrhdontwwdrfhelpdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergekgerjgdwef101201kaswsoifejmfgrwfefgrehrh010009wfe
}

std::string FormatString(const char* format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    std::vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return std::string(buffer);
}


// MEMORY UTILS

bool IsHooked(HANDLE _handle, void* address, SIZE_T bytesToCheck = 16)
{
    if (bytesToCheck > 50) throw OBF("Bytes out of Range (50)");
    if (_handle == nullptr || address == nullptr) { return false; }
    unsigned char bytes[50];
    BOOL IE0 = 0;
    if (!ReadProcessMemory(_handle, (LPVOID)address, bytes, bytesToCheck, 0)) { return false; }//exit(EXIT_FAILURE); }
    for (int i = 0; i < bytesToCheck; i++)
    {
        if (bytes[i] == 0x48 || bytes[i] == 0xFF)
        {
            if (bytes[i + 1] == 0xB8 || bytes[i + 1] == 0xE0)
            {
                return true;
            }
        }

        if (bytes[i] == 0xE9) {
            //int32_t offset = *(int32_t*)&bytes[i + 1]; 
            //std::cout << "Detected JMP hook at offset " << std::hex << offset << std::endl;
            return true;
        }
    }
    return false;
}

void DetectHook(void* address, HANDLE _handle = GetCurrentProcess())
{
    if (IsHooked(_handle, address)) {
        exit(200);
        RunBackend.Unload();
    }
}


namespace HookTracer
{
    constexpr BYTE JMP = 0xE9;
    const BYTE gapBytes[3] = { 0xCC, 0xCC, 0xCC };
    static std::vector<uintptr_t> WhitelistedOffsets = {};

    void LogOffsetFromTrampoline(BYTE* trampolineAddress)
    {
        MEMORY_BASIC_INFORMATION memInfo;
        if (VirtualQuery(trampolineAddress, &memInfo, sizeof(memInfo)))
        {
            BYTE* base = (BYTE*)memInfo.AllocationBase;
            uintptr_t offset = trampolineAddress - base;

            std::cout << "[HOOK DETECTED]" << std::endl;
            std::cout << "method offset: 0x" << std::hex << offset << std::endl;
            std::cout << "sus jmp address: " << (void*)trampolineAddress << "\n\n";
        }
    }

    PIMAGE_SECTION_HEADER FindIl2CppSection(const std::unique_ptr<BYTE[]>& moduleBytes, PIMAGE_NT_HEADERS ntHeader)
    {
        const char* TARGET_SECTION = OBF("il2cpp");

        int sectionCount = ntHeader->FileHeader.NumberOfSections;
        PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(ntHeader);

        for (int i = 0; i < sectionCount; ++i, ++section)
        {
            if (strcmp((const char*)section->Name, TARGET_SECTION) == 0)
            {
                return section;
            }
        }

        return nullptr;
    }

    bool IsWhitelisted(BYTE* trampolineAddress)
    {
        MEMORY_BASIC_INFORMATION memInfo;
        if (VirtualQuery(trampolineAddress, &memInfo, sizeof(memInfo)))
        {
            BYTE* base = (BYTE*)memInfo.AllocationBase;
            uintptr_t offset = trampolineAddress - base;

            for (uintptr_t Offset : WhitelistedOffsets) {
                if (Offset == offset) {
                    return true;
                }
            }
        }
        return false;
    }

    void DetectHooks(bool compareGameAssembly = true)
    {
        HMODULE hModule = GetModuleHandleA(OBF("GameAssembly.dll"));
        MODULEINFO moduleInfo;
        GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo));

        BYTE* baseAddress = (BYTE*)moduleInfo.lpBaseOfDll;
        DWORD imageSize = moduleInfo.SizeOfImage;

        std::unique_ptr<BYTE[]> gameAssemblyBytes = std::make_unique<BYTE[]>(imageSize);
        memcpy(gameAssemblyBytes.get(), baseAddress, imageSize);

        PIMAGE_NT_HEADERS ntHeader = ImageNtHeader(gameAssemblyBytes.get());
        PIMAGE_SECTION_HEADER il2CppSection = FindIl2CppSection(gameAssemblyBytes, ntHeader);

        std::string_view sectionView(
            (char*)gameAssemblyBytes.get() + il2CppSection->VirtualAddress,
            il2CppSection->SizeOfRawData
        );

        std::vector<uint8_t*> jmps;
        for (size_t it = sectionView.find(JMP, 0); it != sectionView.npos; it = sectionView.find(JMP, ++it))
        {
            jmps.emplace_back(baseAddress + il2CppSection->VirtualAddress + it);
        }

        BYTE fileBytes[5] = { 0 };
        std::ifstream gameAssemblyFilestream("GameAssembly.dll", std::ios::binary);
        for (BYTE* jmp : jmps)
        {
            if (compareGameAssembly)
            {
                DWORD offset = (DWORD)(jmp - baseAddress);
                DWORD sectionOffset = offset - il2CppSection->VirtualAddress;
                DWORD fileOffset = il2CppSection->PointerToRawData + sectionOffset;

                gameAssemblyFilestream.seekg(fileOffset, std::ios::beg);
                gameAssemblyFilestream.read((char*)fileBytes, 5);

                if (!memcmp(jmp, fileBytes, 5)) continue;
                if (IsWhitelisted(jmp)) continue;

                MEMORY_BASIC_INFORMATION memInfo;
                if (VirtualQuery(jmp, &memInfo, sizeof(memInfo)))
                {
                    BYTE* base = (BYTE*)memInfo.AllocationBase;
                    uintptr_t offset = jmp - base;

                    if (jmp - base == 0x1912412) continue;
                }

                //LogOffsetFromTrampoline(jmp);
                exit(200);
                RunBackend.Unload();
            }
            else
            {
                int jmpOffset;
                memcpy(&jmpOffset, jmp + 1, 4);
                uint8_t* jmpDest = jmp + (jmpOffset + 5);

                if (jmpDest < baseAddress || jmpDest > baseAddress + imageSize)
                {
                    MEMORY_BASIC_INFORMATION memInfo;
                    if (memcmp(jmp - 3, gapBytes, 3)) continue;

                    if (!VirtualQuery(jmp, &memInfo, sizeof(memInfo))) continue;
                    if (memInfo.Protect != PAGE_EXECUTE_READ) continue;

                    if (!VirtualQuery(jmpDest, &memInfo, sizeof(memInfo))) continue;
                    if (memInfo.Protect != PAGE_EXECUTE_READWRITE) continue;
                    if (IsWhitelisted(jmp)) continue;

                    if ((jmp - (BYTE*)memInfo.AllocationBase) == 0x1912412) continue;

                    //LogOffsetFromTrampoline(jmp);
                    exit(200);
                    RunBackend.Unload();
                }
            }
        }
    }
}