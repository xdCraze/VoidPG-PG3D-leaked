#include "WSFuncs.h"


void INIT_LISTS()
{
    ojson niggerlicious = ojson::parse(Json::SerializeObject(RoyaleDictionary())->ToString());       // Royale
    void* OfferItemTypeDictionary = GET_FIELD(void*, wdfjnefjefj() + 0x10);
    ojson niggerlicious2 = ojson::parse(Json::SerializeObject(OfferItemTypeDictionary)->ToString()); // OfferItemType

    for (auto& [key, value] : niggerlicious.items()) {
        int category = static_cast<int>(niggerlicious[key][OBF("Category")]);
        int index = niggerlicious[key][OBF("Index")];
        if (category == CategoryNames_dict[OBF("GlidersRoyaleCategory")]) GliderIndexes.emplace_back(index);
        else if (category == CategoryNames_dict[OBF("RoyaleAvatarsCategory")]) AvatarIndexes.emplace_back(index);
        else if (category == CategoryNames_dict[OBF("TrailRoyaleCategory")]) TrailIndexes.emplace_back(index);
        else if (category == CategoryNames_dict[OBF("TransportRoyaleCategory")]) CarIndexes.emplace_back(index);
    }

    for (int i = 1; i <= 1900; i++) {
        ItemRecord rec = ItemRecord(i * 1000 + 1);
        if (rec.IsRoyale()) {
            ShovelIndexes.emplace_back(rec.Index());
        }
    }

    PetIndexes = niggerlicious2[OBF("Pet")].get<std::vector<int>>();
    GadgetIndexes = niggerlicious2[OBF("Gadget")].get<std::vector<int>>();
    LobbyItemIndexes = niggerlicious2[OBF("LobbyItem")].get<std::vector<int>>();
    ModuleIndexes = niggerlicious2[OBF("Module")].get<std::vector<int>>();
    ModulePointIndexes = niggerlicious2[OBF("ModulePoint")].get<std::vector<int>>();

    ArmorIndexes = niggerlicious2[OBF("Armor")].get<std::vector<int>>();
    HatIndexes = niggerlicious2[OBF("Hat")].get<std::vector<int>>();
    MaskIndexes = niggerlicious2[OBF("Mask")].get<std::vector<int>>();
    CapeIndexes = niggerlicious2[OBF("Cape")].get<std::vector<int>>();
    BootsIndexes = niggerlicious2[OBF("Boots")].get<std::vector<int>>();
}

/*
SxIl2CppList<void*> PhotonViewList()
{
    Il2CppObject* viewList;
    il2cpp_field_static_get_value(&static_cast<Il2CppClass*>((Il2CppClass*)AssemblyCSKlass(OBF("PhotonObjectCacher")))->fields[0x0], &viewList);
    return SxIl2CppList<void*>::GET(viewList);
}

bool get_PlayerIsMine(void* player_move_c)
{
    return Il2CppUtils::Field<bool>(Il2CppUtils::Field<void*>(player_move_c, "Player_move_c", "mySkinName"), "SkinName", "isMine");
}
*/


void (*wedwsdsgdrshe)(void* instance);  // original PixelTime
void wdefgedssfg(void* instance) {      // PixelTime
    if (instance != nullptr) {

        vars::PlayerLVL = efiikkrigrg();

        // I dont want it to call set_timeScale the whole time, even if its set to default nigger
        if (vars::GameSpeed != 1.0) vars::SetGameSpeed = false;
        if (!vars::SetGameSpeed) {
            if (vars::GameSpeed != 1.0) {
                set_timeScale(vars::GameSpeed);
            }
            else {
                set_timeScale(1.0);
                vars::SetGameSpeed = true;
            }
        }

        for (int i = 0; i < vars::CallInUnityThread.size(); i++)
            vars::CallInUnityThread[i]();

        vars::CallInUnityThread.clear();

    }
    wedwsdsgdrshe(instance);
}

/*
void NetworkStartTable(void* instance) {
    if (instance != nullptr) {

        if (Utils::keyPressed(VK_F3)) {
            Pointer<void(void*, int, bool, monoString*, int)>SetGadgetEffectActive(absolute("0x1b9fa00"));
            Pointer<void(void*, int, bool, monoString*)>SetModuleGadgetEffectActive(absolute("0x1c06130"));
            Pointer<bool(void*)>IsMyPhotonView(absolute("0x1b331a0"));
            Pointer<void(void*, int, int, Il2CppArray*)>RPC(absolute("0x1b32560"));

            Il2CppObject* niggerliciousObj;
            il2cpp_field_static_get_value(&GET_CLASS(___skibidi::PlayerMoveCList)->fields[0], &niggerliciousObj);

            SxIl2CppList Players = SxIl2CppList<void*>::GET(niggerliciousObj);
            SxIl2CppList<void*> PhotonViews = PhotonViewList();
            
            Players.foreach([&](void* plr) {
                if (plr != nullptr && !get_PlayerIsMine(plr)) {
                    for (int i = 0; i <= 20; i++) {
                        SetModuleGadgetEffectActive(plr, i, true, MonoString::New("gadget_mech"));
                        SetGadgetEffectActive(plr, i, true, MonoString::New("gadget_mech"), 1);
                    }
                }
            });

            SxIl2CppList<void*> MyList;
            PhotonViews.foreach([&](void* view) {
                if (view != nullptr && IsMyPhotonView(view)) {
                    RPC(view, 25, 1, MyList.ToArray());
                    fslog::debug("Called!\n");
                }
            });
        }

    }
}
*/

/*
void (*old_WeaponSounds)(void* instance);
void WeaponSounds(void* instance) {
    if (instance != nullptr) {
        Il2CppUtils::Field<bool>(instance, "WeaponSounds",  "isInvisibleAfterRespawn") = true;
        Il2CppUtils::Field<float>(instance, "WeaponSounds", "invisibleAfterRespawnTime") = 9999.9f;
    }
    old_WeaponSounds(instance);
}
*/


void (*jewfjwdfgklrgjefef)(void* instance); // original wepManager
void wdf3egregweafseg(void* instance) { // wepManager
    if (instance != nullptr) {
        /*
        void* character = Il2CppUtils::Field<void*>(instance, "WeaponManager", "myPlayerMoveC");
        if (character != nullptr) {
            void* networkTable = Il2CppUtils::Field<void*>(character, "NetworkStartTable", 0x11d);
            NetworkStartTable(networkTable);
        }
        */

        if (vars::SendRequest) {
            wjfejikfmekdmwjfe(instance, MonoString::New(OBF("FirstPistol")), 14, false, false, nullptr, wejdwmdkemwskmedfge);
        }

    }
    jewfjwdfgklrgjefef(instance);
}

void* (*kefnkerfnwejfhjrgjemfwsflkwyfmkowflöawgkmslegh)(void*, monoString*, Il2CppArray*); // original websocket send
void* dwdwdwagbdrjdrfthdxgdtjftkzfgkt(void* thizz, monoString* eN, Il2CppArray* argsArr) // websocket send
{
    const char* awfsegaewsdafsrhseher = OBF("update_progress"); // event name
    int wsdwsldwsofkirgmsdfosgrds = 1; // RequestSendAmount

    std::string ekfweokfeif = Json::Encode((BNM::Object*)argsArr->vector[0])->ToString();
    ojson request = ojson::parse(ekfweokfeif);
    if (StringContains(ekfweokfeif, OBF(R"("id":165)")) && StringContains(ekfweokfeif, OBF(R"("category":"2")"))) { // To Prevent game reloading when sending gifts
        SxIl2CppList<void*> MyList;
        argsArr = MyList.ToArray();
    }

    if (StringContains(ekfweokfeif, OBF(R"("p":{"i":1001, "u":{"l":)"))) {
        if (vars::SendRequest && !vars::WebsocketSendRequest.empty()) {
            if (vars::AlwaysUpdateSlotsWhenRequestSent) {
                if (!vars::AlwaysUpdateSlotsWhenRequestSentV2) {
                    std::stringstream ___;
                    ___ << OBF("{\"player_id\":\"") << iwsdmwoifmefgujerf()->ToString().c_str() << OBF("\"}");
                    SxIl2CppList<void*> MyList = { Json::Decode(MonoString::New(___.str().c_str())) };
                    WS::Slots::Initialize = true;
                    vars::AlwaysUpdateSlotsWhenRequestSentV2 = true;
                    const char* iefieffg = OBF("get_progress");
                    //fslog::debug("{}\n{}\n\n\n", iefieffg, Json::Encode((BNM::Object*)MyList[0])->ToString());
                    return kefnkerfnwejfhjrgjemfwsflkwyfmkowflöawgkmslegh(thizz, MonoString::New(iefieffg), MyList.ToArray());
                }
                vars::AlwaysUpdateSlotsWhenRequestSentV2 = false;
            }

            vars::SendRequest = false;
            for (int i = 0; i < vars::WebsocketSendRequest.size(); i++) {
                vars::WebsocketSendRequest[i](awfsegaewsdafsrhseher, wsdwsldwsofkirgmsdfosgrds);
                for (int j = 0; j < wsdwsldwsofkirgmsdfosgrds; j++) {
                    SxIl2CppList<void*> MyList = { Json::Decode(MonoString::New(vars::SendRequestData.dump().c_str())) };
                    //fslog::debug("{}\n{}\n\n\n", awfsegaewsdafsrhseher, Json::Encode((BNM::Object*)MyList[0])->ToString());
                    kefnkerfnwejfhjrgjemfwsflkwyfmkowflöawgkmslegh(thizz, MonoString::New(awfsegaewsdafsrhseher), MyList.ToArray());
                }
            }
            vars::WebsocketSendRequest.clear();
            return kefnkerfnwejfhjrgjemfwsflkwyfmkowflöawgkmslegh(thizz, MonoString::New(OBF("update_player")), (Il2CppArray*)Json::Decode(MonoString::New(OBF("{}"))));
        }
        return kefnkerfnwejfhjrgjemfwsflkwyfmkowflöawgkmslegh(thizz, MonoString::New(OBF("update_player")), (Il2CppArray*)Json::Decode(MonoString::New(OBF("{}"))));
    }

    void* iefujefuef = kefnkerfnwejfhjrgjemfwsflkwyfmkowflöawgkmslegh(thizz, eN, argsArr);
    return iefujefuef;
};


void (*ifrmfowekdoekgfioerjmfiewmfirkgrefwefe)(void*, void*, void*, void*); // original websocket receive
void efdowkmdoedfkowdikefmikwedwdefwef(void* instance, void* socket, void* packet, void* param) { // websocket receive
    ojson PacketJ = ojson::parse(dkfmwskfmejge::ToString(packet)->ToString());
    vars::WSResponsesV2.push_back({ PacketJ[0], PacketJ[1].dump() });
    //const char* _eN = dkfmwskfmejge::get_EventName(packet)->ToString().c_str(); idk why but when I try to make a variable for it, it just doesnt work properly

    bool _erase = false;
    
    for (int i = 0; i < vars::WSResponses.size(); i++) {
        if (strcmp(vars::WSResponses[i].eventName.c_str(), dkfmwskfmejge::get_EventName(packet)->ToString().c_str()) == 0) {
            bool FailedStatus;
            if (static_cast<int>(ojson::parse(vars::WSResponses[i].Payload)[OBF("req_id")]) == static_cast<int>(PacketJ[1][OBF("req_id")])) {
                if (vars::WSResponses[i].ForceSuccessStatus) FailedStatus = false;
                else FailedStatus = (StringContains(PacketJ.dump(), OBF("\"err")) || StringContains(PacketJ.dump(), OBF("fail")));

                if (vars::WSResponses[i].NotifyWhenReceived) {
                    ImGui::InsertNotification({ vars::WSResponses[i].toastType, 2000, OBF("Received Request: %s\nStatus: %s"), vars::WSResponses[i].ResponseReceivedName, FailedStatus ? OBF("ERROR") : OBF("SUCCESS") });
                    _erase = true;
                }
                if (vars::WSResponses[i].ReloadWhenReceived) WS::Utils::ReloadGame();
                vars::WSResponses[i].OnRequestReceived(ojson::parse(vars::WSResponses[i].Payload), PacketJ);
                if (_erase) { vars::WSResponses.erase(vars::WSResponses.begin() + i); _erase = false; }
            }
        }
    }
    


    if (strcmp(dkfmwskfmejge::get_EventName(packet)->ToString().c_str(), OBF("get_progress")) == 0) {
        if (WS::Slots::Initialize) {
            WS::Slots::Initialize = false;
            auto JSONsex = PacketJ[1][OBF("slots")];

            WS::Slots::Pets             =           JSONsex[std::to_string(SlotIndex[OBF("PetsV3")]).c_str()];
            WS::Slots::Royale           =           JSONsex[std::to_string(SlotIndex[OBF("BattleRoyaleIds")]).c_str()];
            WS::Slots::RoyaleCars       =           JSONsex[std::to_string(SlotIndex[OBF("BattleRoyaleVehicle")]).c_str()];
            WS::Slots::Gadgets          =           JSONsex[std::to_string(SlotIndex[OBF("Gadgets")]).c_str()];
            WS::Slots::Wears            =           JSONsex[std::to_string(SlotIndex[OBF("Wear")]).c_str()];
            WS::Slots::Armors           =           JSONsex[std::to_string(SlotIndex[OBF("Armor")]).c_str()];
            WS::Slots::Tutorial         =           JSONsex[std::to_string(SlotIndex[OBF("Tutorial")]).c_str()];
            WS::Slots::Weapons          =           JSONsex[std::to_string(SlotIndex[OBF("WeaponsV17")]).c_str()];
            WS::Slots::LobbyItems       =           JSONsex[std::to_string(SlotIndex[OBF("LobbyCraft")]).c_str()];

            
            // Init ModuleInfo (WS method is so shit)
            auto eflemdekgjrgjsef = il2cpp_object_new(GET_CLASS(___skibidi::_____aa));
            for (int i = 0; i < ModuleIndexes.size(); i++) {
                __MCC__(eflemdekgjrgjsef, NiggerParams::GetItemType(Module, NiggerParams::GetItemString(ModuleIndexes[i]).c_str()));
                int eijmfeikfjrgf = __GML__(eflemdekgjrgjsef); // module lvl
                WS::Slots::ModulesInfo[std::to_string(ModuleIndexes[i])] = (eijmfeikfjrgf == 0) ? 1 : eijmfeikfjrgf;
            }
            
            return ifrmfowekdoekgfioerjmfiewmfirkgrefwefe(instance, socket, packet, param);
        }

        if (vars::GetPlayerInfo) {
            Sxitxma::SetColor(ConsoleColor::BrightYellow);
            if (StringContains(PacketJ.dump(), OBF("fail"))) {
                printf(OBF("Failed to get User Info: User doesn't seem to Exist!\n\n\n\n"));
                Sxitxma::ResetColor();
                vars::GetPlayerInfo = false;
                return ifrmfowekdoekgfioerjmfiewmfirkgrefwefe(instance, socket, packet, param);
            }
            auto JSONsex = PacketJ[1][OBF("slots")];
            std::string name = JSONsex[OBF("1")][OBF("n")];

            if (name.length() > 1 && name.front() == '"' && name.back() == '"') {
                name.erase(0, 1);
                name.erase(name.size() - 1);
            }

            printf(OBF("[GET USER INFO BY ID]\n"));

            ojson sifjweifkiergief = JSONsex[OBF("3")];
            ojson sdedfwfegergwfef = JSONsex[OBF("4")];

            int level = (int)sdedfwfegergwfef[OBF("l")];
            int xp = (int)sdedfwfegergwfef[OBF("e")];

            std::cout << OBF("NAME: ") << name << "\n"
                      << OBF("COINS: ") << sifjweifkiergief[OBF("Coins")] << "\n"
                      << OBF("GEMS: ") << sifjweifkiergief[OBF("GemsCurrency")] << "\n"
                      << OBF("PLAYER LVL: ") << level << "\n"
                      << OBF("PLAYER EXP: ") << ((level == 65) ? xp : ProgressRoad[(size_t)level] + xp) << "\n\n\n";
            Sxitxma::ResetColor();
            vars::GetPlayerInfo = false;
            return ifrmfowekdoekgfioerjmfiewmfirkgrefwefe(instance, socket, packet, param);
        }
    }
    
    return ifrmfowekdoekgfioerjmfiewmfirkgrefwefe(instance, socket, packet, param);
}


int (*wefjiewfujrefgzherfg)(NiggerParams);
int jsncusdnfuedrnfghredfg(NiggerParams instance)
{
    int val = wefjiewfujrefgzherfg(instance);
    if (__NiggerParams::___sex(instance) == 10015 && vars::OFFERS_SetPaidOffersPrices) {
        try {
            int _v = std::stoi(std::string(vars::OFFERS_PaidOffersPrices));
            return _v;
        }
        catch (std::invalid_argument err) {
            return val;
        }
    }
    return val;
}

int (*efeikdeujfgrhguhrg)(NiggerParams);
int feikjnfejfnhrefgerhf(NiggerParams instance)
{
    int value = efeikdeujfgrhguhrg(instance);
    if (value == 10015 && vars::OFFERS_FreePaidOffers) {
        return 11015;
    }
    return value;
}


// Crash If any dangerous dlls are being injected
/* this here is the best one cuz it detects any hooks being made so it bypasses detections through manual mapping too
* only proplam in this shit here is that some retarded niggers with skill issues get crash issue bc of this so dont use it

bool VirtualProtect__DontCrash = true;
BOOL(WINAPI* old_HookedVirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
BOOL WINAPI HookedVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
    if (!VirtualProtect__DontCrash) {
        exit(200);
        RunBackend.Unload();
    }
    VirtualProtect__DontCrash = false;
    return old_HookedVirtualProtect(lpAddress, dwSize, flNewProtect, lpflOldProtect);
}
*/

void*(*old_getTokenDictionary)(void*, void*);
void* getTokenDictionary(void* ths, void* byteArr) {
    if (vars::AUTH_LoginWithToken) {
        void* idk = old_getTokenDictionary(ths, byteArr);
        ImGui::InsertNotification({ ImGuiToastType::Info, 2000, OBF("Trying to Login...") });
        Il2CppDictionary MyDict = Il2CppDictionary<void*, void*>::GetDict((BNM::Object*)idk);
        MyDict.EditValue(MonoString::New(OBF("token")), MonoString::New(vars::AUTH_PlayerToken));
        vars::AUTH_LoginWithToken = false;
        ImGui::InsertNotification({ ImGuiToastType::Success, 2000, OBF("Logging attempt done!") });
        return MyDict.get_Dict();
    }
    return old_getTokenDictionary(ths, byteArr);
};

void (*old_SendAnalytics)(void*, int, void*);
void SendAnalytics(void* ths, int AnalID, void* dict) {
    if (vars::FUN__DisableAnalytics) dict = nullptr;
    return old_SendAnalytics(ths, AnalID, dict);
}


void Hooks() {

    BNM::Image* AssemblyC = BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image();
    const char* upd = OBF("Update");

    uintptr_t PixelTime__Update = (uintptr_t)AssemblyC->Class(OBF("PixelTime"))->Method(upd)->RVA();
    uintptr_t WeaponManager__Update = (uintptr_t)AssemblyC->Class(OBF("WeaponManager"))->Method(upd)->RVA();
    uintptr_t ws_send = (uintptr_t)AssemblyC->Class(OBF("BestHTTP.SocketIO.Socket"))->Method(OBF("Emit"))->RVA();
    uintptr_t ws_receive = (uintptr_t)Il2CppUtils::GetMethodPointer(___skibidi::______aa___, { OBF("private"), OBF("Void"), nullptr, {OBF("Socket"), OBF("Packet"), OBF("Object[]")} }) - il2cpp_base;
    uintptr_t item_count_value = (uintptr_t)Il2CppUtils::GetMethodPointer(GET_CLASS(___skibidi::______aa), { OBF("private"), OBF("Void"), nullptr, {nullptr}, 0x2 }) - il2cpp_base;
    uintptr_t item_type_value = (uintptr_t)Il2CppUtils::GetMethodPointer(GET_CLASS(___skibidi::______aa), { OBF("internal"), OBF("Int32"), nullptr, {} }) - il2cpp_base;
    uintptr_t token_return_dictionary = (uintptr_t)Il2CppUtils::GetMethodPointer(GET_CLASS(___skibidi::___aa), { OBF("private"), OBF("Dictionary`2"), nullptr, {OBF("Byte[]")} }) - il2cpp_base;
    uintptr_t send_analytics = (uintptr_t)Il2CppUtils::GetMethodPointer(GET_CLASS(___skibidi::AnalyticsController), { OBF("internal"), OBF("Void"), nullptr, {OBF("Int32"), OBF("Dictionary`2")} }) - il2cpp_base;

    auto nigger = &HookTracer::WhitelistedOffsets;
    nigger->emplace_back(PixelTime__Update);
    nigger->emplace_back(WeaponManager__Update);
    nigger->emplace_back(ws_send);
    nigger->emplace_back(ws_receive);
    nigger->emplace_back(item_count_value);
    nigger->emplace_back(item_type_value);
    nigger->emplace_back(token_return_dictionary);
    nigger->emplace_back(send_analytics);

    // DETECT HOOKS BEFORE APPLYING YOUR HOOKS
    DetectHook((void*)(ws_send + il2cpp_base));
    DetectHook((void*)(ws_receive + il2cpp_base));

    // APPLY HOOKS
    HOOK(PixelTime__Update + il2cpp_base, &wdefgedssfg, &wedwsdsgdrshe);
    HOOK(WeaponManager__Update + il2cpp_base, &wdf3egregweafseg, &jewfjwdfgklrgjefef);

    HOOK(ws_send + il2cpp_base, &dwdwdwagbdrjdrfthdxgdtjftkzfgkt, &kefnkerfnwejfhjrgjemfwsflkwyfmkowflöawgkmslegh);
    HOOK(ws_receive + il2cpp_base, &efdowkmdoedfkowdikefmikwedwdefwef, &ifrmfowekdoekgfioerjmfiewmfirkgrefwefe);

    HOOK(item_count_value + il2cpp_base, &jsncusdnfuedrnfghredfg, &wefjiewfujrefgzherfg); // Item Count Value
    HOOK(item_type_value + il2cpp_base, &feikjnfejfnhrefgerhf, &efeikdeujfgrhguhrg); // Item Type Value/Index
    
    HOOK(token_return_dictionary + il2cpp_base, &getTokenDictionary, &old_getTokenDictionary);

    HOOK(send_analytics + il2cpp_base, &SendAnalytics, &old_SendAnalytics);

    //HOOK(absolute("0x48ce70"), &GetPlacementState, &old_GetPlacementState);
    //HOOK(absolute("0x48d030"), &IsReady, &old_IsReady);
    //HOOK(absolute("0x48d1a0"), &SupportedOrientations, &old_SupportedOrientations);

    //HookUpdate2("WeaponSounds", &WeaponSounds, &old_WeaponSounds);

    //HOOK((uint64_t)GetProcAddress(GetModuleHandleA(OBF("kernel32.dll")), OBF("VirtualProtect")), &HookedVirtualProtect, &old_HookedVirtualProtect);
    //HOOK((uint64_t)GetProcAddress(GetModuleHandleA(OBF("kernel32.dll")), OBF("LoadLibraryA")), &HookedLoadLibraryA, &old_HookedLoadLibraryA);
    //HOOK((uint64_t)GetProcAddress(GetModuleHandleA(OBF("kernel32.dll")), OBF("LoadLibraryW")), &HookedLoadLibraryW, &old_HookedLoadLibraryW);
    //HOOK((uint64_t)GetProcAddress(GetModuleHandleA(OBF("kernel32.dll")), OBF("LoadLibraryExA")), &HookedLoadLibraryExA, &old_HookedLoadLibraryExA);
    //HOOK((uint64_t)GetProcAddress(GetModuleHandleA(OBF("kernel32.dll")), OBF("LoadLibraryExW")), &HookedLoadLibraryExW, &old_HookedLoadLibraryExW);

    //Encrypt Method: HOOK(Il2CppUtils::GetMethodPointer(___skibidi::______aa______, {"public", "Byte[]", nullptr, {"Byte[]", "Boolean"}}), &woferjgoekfdoerkgergf, &ioefkoepfklrogkefkoefg);
    //WebsocketManager Send Method: HOOK(Il2CppUtils::GetMethodPointer(___skibidi::______aa___, {"internal", "Int32", nullptr, {"String", "Dictionary`2"}}), &wdfrgedekgrdngkdrsmfger, &efrgwedfrgrfefedrgrfdsrgdrg);

}