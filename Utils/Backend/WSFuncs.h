#include "Backend/UtilityFunctions.h"


namespace Functions {

    enum WeaponType {
        WT_NORMAL, // non-craftable weapons (ultimatum, harsh punisher, ...)
        WT_CRAFT,  // craftable weapons only
        WT_BOTH
    };

    enum WearType {
        ARMOR, // not supported for AddWear(WearType, ...)
        HAT,
        MASK,
        CAPE,
        BOOTS,
        ALL_EXCEPT_ARMOR
    };

    enum RoyaleType {
        GLIDER,
        SHOVEL,
        AVATAR,
        TRAIL,
        CAR
    };

    enum CurrencyType {
        ADD_CURRENCY,
        REMOVE_CURRENCY,
        ADD_CONSUMABLE,
        REMOVE_CONSUMABLE,
        SET_EVENTCURRENCY // usually used for Keys
    };

    enum CraftPartType {
        NORMAL,          // used to add for shovels and weapons
        ITEM_CONSUMABLE, // used to add for capes, armors, etc.
        ROYALE,          // all royale except shovels
        AVATAR_SET       // used to add sets like cyber santa, halloween etc.
    };

    namespace Account {
        // ACCOUNT
        static std::string CreateUpdatePlayerLevel(int lvl, int xp = 0);
        static int         BaseLevel(int xp); // returns the base level of the xp you have
        static int         BaseXP(int xp); // returns the base xp of the xp you have
        static std::string SetXP(int xp);
        static std::string AddXP(int xp);
        static std::string SetPlayerLvl(int lvl);
        static std::string AddPlayerLvl(int lvl);

        static std::string CompleteBeginnerTutorial();

        // ARMORY
        static std::string CreateWeaponV2(int index, int lvl = 1, int rarity = 5);
        static std::string AddWeaponsV2(WeaponType WT, int lvl = 1, int rarity = 5, int startIndex = 1, int endIndex = 1900);

        // WEARS
        static bool        WearExists(int wearindex);
        static std::string CreateWear(int index);
        static std::string AddWear(WearType WT, int startIndex, int endIndex);
        static std::string AddArmors(int level = 65, int startIndex = 0, int endIndex = std::size(ArmorIndexes));
        static std::string AddWearSkinsV2(WearType WT = ALL_EXCEPT_ARMOR, int startIndex = 1, int endIndex = 300);
        static std::string AddAllWears(int ArmorLevels = 65);

        // GADGETS
        static std::string AddGadgets(int lvl = 65, int startIndex = 0, int endIndex = std::size(GadgetIndexes));

        // MISC
        static std::string AddWeaponSkinsV2(int startIndex = 1, int endIndex = 800);
        static std::string AddGraffitisV2(int startIndex = 1, int endIndex = 100);

        // ROYALE
        static bool        RoyaleExists(int royaleIndex);
        static std::string CreateRoyale(RoyaleType RT, int index);
        static std::string AddRoyale(RoyaleType RT, int startIndex, int endIndex);
        static std::string AddAllRoyale();

        // UPGRADE ROYALE
        static std::string CreateUpgradeRoyale(int index, int lvl = 5);
        static std::string UpgradeRoyale(RoyaleType RT, int startIndex, int endIndex, int level = 5);
        static std::string UpgradeAllRoyale(int lvl = 5);

        // PETS
        static bool        PetExists(int petIndex);
        static std::string AddPets(int startIndex = 0, int endIndex = std::size(PetIndexes));
        static std::string AddPetParts(int parts = 999, int startIndex = 0, int endIndex = std::size(PetIndexes));
        static std::string UpgradePets(int lvl = 65, int startIndex = 0, int endIndex = std::size(PetIndexes));

        // CRAFT PARTS
        static std::string AddCraftPartsV2(CraftPartType CPT = CraftPartType::NORMAL, int parts = 250, int startIndex = 1, int endIndex = 2000);

        // MODULES
        static std::string AddModules(int parts = 2500, int startIndex = 0, int endIndex = std::size(ModulePointIndexes));
        static std::string CreateUpgradeModule(int index, int lvl, int StopIfHasLlvl = 10);
        static std::string UpgradeModules(int lvl = 10, int StopIfHasLlvl = 10, int startIndex = 0, int endIndex = std::size(ModulePointIndexes));

        // LOBBY ITEMS
        static std::string AddLobbyItems(int startIndex = 0, int endIndex = std::size(LobbyItemIndexes));

        // PLAYER STATS
        static std::string AddModeStat(int ModeType);
        static std::string AddMonthlyStats(int kills, int headshots, int accuracy, bool IsWin = true, int deaths = 0);
        static std::string SetMonthlyStats(int killstreak, int todayWinstreak, int seasonWinstreak, bool IsWin = false); // NOTE: only changes when the set value is higher than the value you have right now
        static std::string AddMatches(int value, bool WinsIncluded = false);

        // OTHER
        static std::string AddPixelPass();
        static std::string AddPixelPassXP(int xp);

        static std::string UpdateCurrency(CurrencyType CT, int CurrencyIndex, int Amount, int AddReason = 37);
        static std::string UpdateCurrency(CurrencyType CT, const char* CurrencyString, int Amount, int AddReason = 37);

        static std::string AddOffers(int startIndex = 0, int endIndex = std::size(OfferIndexes), int OfferEndTime = 1794126799);

        static std::string InventoryAddItemSingle(int index, int cause = 115);

        static std::string RegisterGift(int Amount, std::string SenderID, std::string ReceiverID, std::string SenderClanID, ojson ItemData = ojson::array({"17018:1"}));
    };


    namespace Menu {
        // ACCOUNT TAB
        // QUICK ACC MAXING SUBTAB
        static void Account__MaxAccount();
        static void Account__AddDlcSets();

        // OTHER TAB
        // MISC SUBTAB
        static void Misc__SendGift(int Amount, std::string ReceiverID, ojson ItemData = ojson::array({"17018:1"}));
    }
};
















// NAMESPACE: ACCOUNT

/************************************ ACCOUNT ************************************/

static std::string Functions::Account::CreateUpdatePlayerLevel(int lvl, int xp)
{
    if ((lvl < 1) || (lvl > 65)) { return WS::Utils::EmptyCommand().dump(); }
    std::stringstream Sex;
    ojson lvl1 = {
        {"id", 64},
        {"ci", randHex()},
        {"p", {
            {"l", 1},
        }},
        {"h", json::object()},
        {"v", WS::GameVersion},
        {"u", {140, 6}},
    };
    for (int i = 1; i <= lvl; i++) {
        Sex << lvl1.dump() << ",";
        lvl1["p"]["l"] = i + 1;
    }

    ojson lvl2 = {
        {"id", 65},
        {"ci", randHex()},
        {"p", {
            {"e", xp},
            {"ec", 4},
            {"ad", json::object()},
        }},
        {"h", json::object()},
        {"v", WS::GameVersion},
        {"u", {140, 6}},
    };

    ojson lvl3 = {
        {"id", 777},
        {"ci", randHex()},
        {"p", {
            {"eid", 1043},
            {"params", {
                {"ip1", 40},
                {"ip2", 140},
                {"ip3", 2040},
                {"sp1", "MultiplayerMatchReward"},
                {"jp1", {
                    {"v_ProgressRoad", 11},
                    {"v_Tutorial", 12},
                }},
            }},
        }},
        {"h", json::object()},
        {"v", WS::GameVersion},
        {"u", {140, 6}},
    };

    Sex << lvl2.dump() << "," << lvl3.dump();
    return Sex.str();
}

static int Functions::Account::BaseLevel(int xp)
{
    for (int i = 0; i < ProgressRoad.size(); i++) {
        int _xp = ProgressRoad[i] - xp;
        if (_xp > 0) return i - 1;
    }
    return 65;
}

static int Functions::Account::BaseXP(int xp) { return ProgressRoad[BaseLevel(xp)]; }

static std::string Functions::Account::SetXP(int xp)
{
    std::string _;
    if (xp < 0) { return WS::Utils::EmptyCommand().dump(); }
    int lvl = BaseLevel(xp);
    int _xp = xp - ProgressRoad[BaseLevel(xp)];
    if (lvl == 65 && (_xp > 500)) {
        _xp = 500;
    }
    return CreateUpdatePlayerLevel(lvl, _xp);
}

static std::string Functions::Account::AddXP(int xp)
{
    return SetXP(efknedfjrfgh() + xp);
}

static std::string Functions::Account::SetPlayerLvl(int lvl)
{
    return CreateUpdatePlayerLevel(lvl);
}

static std::string Functions::Account::AddPlayerLvl(int lvl)
{
    return CreateUpdatePlayerLevel(efiikkrigrg() + lvl);
}



static std::string Functions::Account::CompleteBeginnerTutorial()
{
    std::string _;
    ojson oijfief = WS::Utils::__create(253, { {"t", 0} });
    for (int i = 0; i < std::size(TutorialIndexes); i++) {
        if (StringContains(WS::Slots::Tutorial.dump(), std::to_string(TutorialIndexes[i]))) continue;
        oijfief["p"]["t"] = TutorialIndexes[i];
        _ += oijfief.dump() + ",";
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ ARMORY ************************************/

static std::string Functions::Account::CreateWeaponV2(int index, int lvl, int rarity)
{
    return WS::Utils::__create(132, {
        {"i", index},
        {"u", {{"l", lvl}, {"r", rarity}}},
        {"oc", 9999}
    }).dump();
}

static std::string Functions::Account::AddWeaponsV2(WeaponType WT, int lvl, int rarity, int startIndex, int endIndex)
{
    std::string _;
    //bool shouldContinue = false;
    std::string WD = WS::Slots::Weapons.dump();
    for (int i = startIndex; i <= endIndex; i++) {
        int __ = i * 1000 + 1;
        ItemRecord WepRecord = ItemRecord(__);
/* old ass method
for (int j = 0; j < std::size(ShovelIndexes); j++) {
    if (__ == ShovelIndexes[j]) { shouldContinue = true; break; };
}
*/
        if (WepRecord.IsRoyale()) continue;
        //if (shouldContinue) { shouldContinue = false; continue; };

        switch (WT) {
        case WT_NORMAL: if (!WepRecord.IsCraft() && !WepRecord.IsCraftFromSet() && !WepRecord.IsClansCraft()) { _ += CreateWeaponV2(__, lvl, rarity) + ","; } break;
        case WT_CRAFT: if (WepRecord.IsCraft() || WepRecord.IsCraftFromSet() || WepRecord.IsClansCraft()) { _ += CreateWeaponV2(__, lvl, rarity) + ","; } break;
        case WT_BOTH: _ += CreateWeaponV2(__, lvl, rarity) + ","; break;
        }
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ WEARS ************************************/

static bool Functions::Account::WearExists(int wearindex)
{
    ojson list = WS::Slots::Wears["w"];
    for (int i = 0; i < list.size(); i++) { if (static_cast<int>(list[i]) == wearindex) return true; }
    return false;
}

static std::string Functions::Account::CreateWear(int index)
{
    return WS::Utils::__create(31, {
        {"w", "a*" + std::to_string(index)}
    }).dump();
}

static std::string Functions::Account::AddWear(WearType WT, int startIndex, int endIndex)
{
    std::string _ = "";
    for (int i = startIndex; i < endIndex; i++) {
        switch (WT) {
        case HAT:
            if (WearExists(HatIndexes[i])) continue;
            _ += CreateWear(HatIndexes[i]) + ",";
            break;
        case MASK:
            if (WearExists(MaskIndexes[i])) continue;
            _ += CreateWear(MaskIndexes[i]) + ",";
            break;
        case CAPE:
            if (WearExists(CapeIndexes[i])) continue;
            _ += CreateWear(CapeIndexes[i]) + ",";
            break;
        case BOOTS:
            if (WearExists(BootsIndexes[i])) continue;
            _ += CreateWear(BootsIndexes[i]) + ",";
            break;
        }
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

static std::string Functions::Account::AddArmors(int level, int startIndex, int endIndex)
{
    ojson iefjief = WS::Utils::__create(191, { {"a", 0}, {"u", level} });
    std::string _ = "";
    for (int i = startIndex; i < endIndex; i++) {
        iefjief["p"]["a"] = ArmorIndexes[i];
        _ += iefjief.dump() + ",";
    }
    _.pop_back(); return _;
}

static std::string Functions::Account::AddWearSkinsV2(WearType WT, int startIndex, int endIndex)
{
    ojson iefjief = WS::Utils::__create(84, { {"i", 0} });
    std::string _ = "";
    for (int i = startIndex; i < endIndex; i++) {
        switch (WT) {
        case ALL_EXCEPT_ARMOR:
            iefjief["p"]["i"] = i * 1000 + 29;
            _ += iefjief.dump() + ",";
            break;
        case ARMOR:
            iefjief["p"]["i"] = i * 1000 + 23;
            _ += iefjief.dump() + ",";
            break;
        }
    }
    _.pop_back(); return _;
}

static std::string Functions::Account::AddAllWears(int ArmorLevels)
{
    return AddWear(HAT, 0, (int)HatIndexes.size()) + "," + AddWear(MASK, 0, (int)std::size(MaskIndexes)) + "," +
        AddWear(CAPE, 0, (int)std::size(CapeIndexes)) + "," + AddWear(BOOTS, 0, (int)std::size(BootsIndexes)) +
        "," + AddArmors(ArmorLevels);
}

/************************************ GADGETS ************************************/

static std::string Functions::Account::AddGadgets(int lvl, int startIndex, int endIndex)
{
    std::string _;
    ojson iwdjief = WS::Utils::__create(33, { {"g", 0}, {"u", lvl} });
    for (int i = startIndex; i < endIndex; i++) {
        if (StringContains(WS::Slots::Gadgets.dump(), "\"" + std::to_string(GadgetIndexes[i]) + "\"")) {
            ojson ijief = WS::Utils::__create(358, { {"g", GadgetIndexes[i]} });
            ojson ijiesf = WS::Utils::__create(10, { {"c", "Coins"}, {"v", 1}, {"ca", 37} });
            ojson ijiesaf = WS::Utils::__create(66, { {"c", "Coins"}, {"v", 1}, {"ca", 63} });
            _ += ijief.dump() + "," + ijiesf.dump() + "," + ijiesaf.dump() + ",";
        };
        iwdjief["p"]["g"] = GadgetIndexes[i];
        _ += iwdjief.dump() + ",";
    };
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ MISC ************************************/

static std::string Functions::Account::AddWeaponSkinsV2(int startIndex, int endIndex)
{
    std::string _;
    ojson kedfkef = WS::Utils::__create(84, { {"i", 0} });
    bool ShouldContinue = false;
    for (int i = startIndex; i <= endIndex; i++) {
        //if ((i >= 496 && i <= 513) || (i >= 531 && i <= 541) || (i == 547)) { continue; }
        for (int j = 0; j < std::size(DlcWeaponSkinIndexes); j++) { if (DlcWeaponSkinIndexes[j] == i * 1000 + 14) { ShouldContinue = true; break; } }
        if (ShouldContinue) { ShouldContinue = false; continue; }
        kedfkef["p"]["i"] = i * 1000 + 14;
        _ += kedfkef.dump() + ",";
    }
    _.pop_back(); return _;
}

static std::string Functions::Account::AddGraffitisV2(int startIndex, int endIndex)
{
    std::string _;
    ojson edkfmerifg = WS::Utils::__create(84, { {"i", 0} });
    for (int i = startIndex; i <= endIndex; i++) {
        edkfmerifg["p"]["i"] = i * 1000 + 28;
        _ += edkfmerifg.dump() + ",";
    }
    _.pop_back(); return _;
}

/************************************ ROYALES ************************************/

static bool Functions::Account::RoyaleExists(int royaleIndex)
{
    ojson list = WS::Slots::Royale;
    for (int i = 0; i < list.size(); i++) { if (static_cast<int>(list[i]) == royaleIndex) return true; }
    return false;
}

static std::string Functions::Account::CreateRoyale(RoyaleType RT, int index)
{
    std::string _;
    switch (RT) {
    case GLIDER:
        return WS::Utils::__create(130, { {"i", index}, {"u", 0} }).dump();
    case SHOVEL:
        return WS::Utils::__create(132, { {"i", index}, {"u", {{"l", 1}, {"r", 5}}} }).dump();
    case AVATAR:
        return WS::Utils::__create(28, { {"1", std::to_string(index)} }).dump();
    case TRAIL:
        return WS::Utils::__create(28, { {"1", std::to_string(index)} }).dump();
    case CAR:
        return WS::Utils::__create(130, { {"i", index}, {"u", 0} }).dump();
    }
    return WS::Utils::EmptyCommand().dump();
}

static std::string Functions::Account::AddRoyale(RoyaleType RT, int startIndex, int endIndex)
{
    std::string _ = "";
    std::string RCD = WS::Slots::RoyaleCars.dump();
    std::string WD = WS::Slots::Weapons.dump();
    for (int i = startIndex; i < endIndex; i++) {
        switch (RT) {
        case GLIDER:
            if (StringContains(RCD, "\"" + std::to_string(GliderIndexes[i]) + "\"")) { continue; }
            _ += CreateRoyale(GLIDER, GliderIndexes[i]) + ",";
            break;
        case SHOVEL:
            if (StringContains(WD, "\"" + std::to_string(ShovelIndexes[i]) + "\"")) { continue; }
            _ += CreateRoyale(SHOVEL, ShovelIndexes[i]) + ",";
            break;
        case AVATAR:
            if (RoyaleExists(AvatarIndexes[i]) || AvatarIndexes[i] == 1201005) continue;
            _ += CreateRoyale(AVATAR, AvatarIndexes[i]) + ",";
            break;
        case TRAIL:
            if (RoyaleExists(TrailIndexes[i])) continue;
            _ += CreateRoyale(TRAIL, TrailIndexes[i]) + ",";
            break;
        case CAR:
            if (StringContains(RCD, "\"" + std::to_string(CarIndexes[i]) + "\"")) { continue; }
            _ += CreateRoyale(CAR, CarIndexes[i]) + ",";
            break;
        }
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

static std::string Functions::Account::AddAllRoyale()
{
    return AddRoyale(GLIDER, 0, (int)std::size(GliderIndexes)) + "," + AddRoyale(SHOVEL, 0, (int)std::size(ShovelIndexes)) + "," +
        AddRoyale(AVATAR, 0, (int)std::size(AvatarIndexes)) + "," + AddRoyale(TRAIL, 0, (int)std::size(TrailIndexes)) + "," +
        AddRoyale(CAR, 0, (int)std::size(CarIndexes));
}

/************************************ UPGRADE ROYALES ************************************/

static std::string Functions::Account::CreateUpgradeRoyale(int index, int lvl)
{
    std::string RCD = WS::Slots::RoyaleCars.dump();
    int owkweifki; // Lvl of that item
    if (WS::Slots::RoyaleCars["v"][std::to_string(index)].is_null()) { return WS::Utils::EmptyCommand().dump(); }
    owkweifki = WS::Slots::RoyaleCars["v"][std::to_string(index)];
    if (StringContains(RCD, "\"" + std::to_string(index) + "\"") && (owkweifki < 4)) {
        return WS::Utils::__create(130, { {"i", index}, {"u", lvl - 1} }).dump();
    }
    return WS::Utils::EmptyCommand().dump();
}

static std::string Functions::Account::UpgradeRoyale(RoyaleType RT, int startIndex, int endIndex, int level)
{
    std::string _;
    for (int i = startIndex; i < endIndex; i++) {
        switch (RT) {
        case GLIDER:
            _ += CreateUpgradeRoyale(GliderIndexes[i]) + ",";
            break;
        case CAR:
            _ += CreateUpgradeRoyale(CarIndexes[i]) + ",";
            break;
        }
    }
    _.pop_back(); return _;
}

static std::string Functions::Account::UpgradeAllRoyale(int lvl)
{
    return UpgradeRoyale(GLIDER, 0, (int)GliderIndexes.size(), lvl) + "," + UpgradeRoyale(CAR, 0, (int)CarIndexes.size(), lvl);
}

/************************************ PETS ************************************/

static bool Functions::Account::PetExists(int petIndex)
{
    ojson list = WS::Slots::Pets["p"];
    for (int i = 0; i < list.size(); i++) { if (static_cast<int>(list[i]["i"]) == petIndex) return true; }
    return false;
}

static std::string Functions::Account::AddPets(int startIndex, int endIndex)
{
    std::string _;
    ojson eifkeif = WS::Utils::__create(229, { {"i", 0}, {"n", ""} });
    for (int i = startIndex; i < endIndex; i++) {
        if (PetExists(PetIndexes[i])) continue;
        eifkeif["p"]["i"] = PetIndexes[i];
        _ += eifkeif.dump() + ",";
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

static std::string Functions::Account::AddPetParts(int parts, int startIndex, int endIndex)
{
    std::string _;
    ojson eifkeif = WS::Utils::__create(232, { {"i", 0}, {"a", parts} });
    for (int i = startIndex; i < endIndex; i++) {
        if (PetExists(PetIndexes[i])) {
            eifkeif["p"]["i"] = PetIndexes[i];
            _ += eifkeif.dump() + ",";
        }
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

static std::string Functions::Account::UpgradePets(int lvl, int startIndex, int endIndex)
{
    std::string _;
    ojson eifkeif = WS::Utils::__create(230, { {"i", 0}, {"l", lvl} });
    for (int i = startIndex; i < endIndex; i++) {
        if (PetExists(PetIndexes[i])) {
            eifkeif["p"]["i"] = PetIndexes[i];
            _ += eifkeif.dump() + ",";
        }
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ CRAFTING PARTS ************************************/

static std::string Functions::Account::AddCraftPartsV2(CraftPartType CPT, int parts, int startIndex, int endIndex)
{
    std::string _;
    std::string WD = WS::Slots::Weapons.dump();
    ojson iekfe = WS::Utils::__create(120, { {"i", 0}, {"d", parts} });
    for (int i = startIndex; i < endIndex; i++) {
        int ___;
        switch (CPT) {
        case NORMAL:
            ___ = i * 1000 + 1;
            if (StringContains(WD, "\"" + std::to_string(___) + "\"")) continue;
            iekfe["p"]["i"] = ___;
            _ += iekfe.dump() + ",";
            break;
        case ITEM_CONSUMABLE:
            iekfe = WS::Utils::__create(80, { {"t", 1300}, { "i", 0 }, {"c", parts} });
            ___ = i * 1000 + 21;
            iekfe["p"]["i"] = ___;
            _ += iekfe.dump() + ",";
            break;
        case ROYALE:
            ___ = i * 1000 + 5;
            iekfe["p"]["i"] = ___;
            _ += iekfe.dump() + ",";
            break;
        case AVATAR_SET:
            ___ = CraftSetIndexes[i - 1];
            iekfe["p"]["i"] = ___;
            _ += iekfe.dump() + ",";
            break;
        }
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ MODULES ************************************/

static std::string Functions::Account::AddModules(int parts, int startIndex, int endIndex)
{
    std::string _;
    ojson iefiwfiefk = WS::Utils::__create(80, { {"t", 1155}, {"i", 0}, {"c", parts}, {"sc", 1} });
    for (int i = startIndex; i < endIndex; i++) {
        iefiwfiefk["p"]["i"] = ModulePointIndexes[i];
        _ += iefiwfiefk.dump() + ",";
    }
    _.pop_back(); return _;
}

static std::string Functions::Account::CreateUpgradeModule(int index, int lvl, int StopIfHasLlv)
{
    std::string _;
    ojson wffefgrgf = WS::Utils::__create(66, { {"c", "Coins"}, {"v", 0}, {"ca", 72} });
    ojson iwejfiekf = WS::Utils::__create(87, { {"i", index} });
    int oekiwefke = WS::Slots::ModulesInfo[std::to_string(index)]; // Module LVL
    //if (oekiwefke == 0 || (oekiwefke >= StopIfHasLlv)) return ""; THIS ONLY UPGRADES MODULES THAT THE USER ALREADY HAS
    if (oekiwefke >= StopIfHasLlv) return "";
    for (int i = 0; i < lvl; i++) {
        oekiwefke = WS::Slots::ModulesInfo[std::to_string(index)];
        if (oekiwefke < StopIfHasLlv) {
            _ += wffefgrgf.dump() + "," + iwejfiekf.dump() + ",";
            WS::Slots::ModulesInfo[std::to_string(index)] = oekiwefke + 1;
        }
        else {
            break;
        }
    }
    if (!_.empty()) { _.pop_back(); return _; }
    return "";
}

static std::string Functions::Account::UpgradeModules(int lvl, int StopIfHasLlvl, int startIndex, int endIndex)
{
    std::string _;
    for (int i = startIndex; i < endIndex; i++) {
        std::string __ = CreateUpgradeModule(ModuleIndexes[i], lvl, StopIfHasLlvl);
        if (__.empty()) continue;
        _ += __ + ",";
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ LOBBY ITEMS ************************************/

static std::string Functions::Account::AddLobbyItems(int startIndex, int endIndex)
{
    std::string _;
    ojson iwdjief = WS::Utils::__create(20, { {"D", {{
        {"i", 0}, {"c", 1}
    }}} });
    for (int i = startIndex; i < endIndex; i++) {
        if (StringContains(WS::Slots::LobbyItems.dump(), ":" + std::to_string(LobbyItemIndexes[i]))) continue;
        iwdjief["p"]["D"][0]["i"] = LobbyItemIndexes[i];
        _ += iwdjief.dump() + ",";
    };
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ PLAYER STATS ************************************/

static std::string Functions::Account::AddModeStat(int ModeIndex)
{
    ojson eifjerikfe = {
        {"mode", ModeIndex}
    };
    return eifjerikfe.dump();
}

static std::string Functions::Account::AddMonthlyStats(int kills, int headshots, int accuracy, bool IsWin, int deaths)
{
    return WS::Utils::__create(370, {
        {"k", kills},
        {"d", deaths},
        {"w", IsWin},
        {"hds", headshots},
        {"h", accuracy}, // for accuracy: decrease: negative value, increase: positive value
        {"s", 0},
        {"ks", 0},
        {"c", false},
        {"tw", 0},
        {"sw", 0},
        {"sid", ""},
        {"dk", "8-1-2024"}
    }).dump();
}

static std::string Functions::Account::SetMonthlyStats(int killstreak, int todayWinstreak, int seasonWinstreak, bool IsWin)
{
    return WS::Utils::__create(370, {
        {"k", 0},
        {"d", 0},
        {"w", IsWin},
        {"hds", 0},
        {"h", 0},
        {"s", 0},
        // Set Part
        {"ks", killstreak},
        {"c", false},
        {"tw", todayWinstreak}, // winstreak
        {"sw", seasonWinstreak},
        {"sid", ""},
        {"dk", "8-1-2024"}
        }).dump();
}

static std::string Functions::Account::AddMatches(int value, bool WinsIncluded)
{
    std::string _;
    for (int i = 0; i < value; i++) {
        _ += Functions::Account::AddMonthlyStats(0, 0, 0, WinsIncluded) + ",";
    }
    if (_.empty()) return WS::Utils::EmptyCommand().dump();
    _.pop_back(); return _;
}

/************************************ OTHER ************************************/

static std::string Functions::Account::AddPixelPassXP(int xp) { return WS::Utils::__create(326, { {"e", xp} }).dump(); }
static std::string Functions::Account::AddPixelPass() { return WS::Utils::__create(324, {}, true).dump(); }


static std::string Functions::Account::UpdateCurrency(CurrencyType CT, const char* CurrencyString, int Amount, int AddReason)
{
    return WS::Utils::__create(10, { {"c", CurrencyString}, {"v", Amount}, {"ca", AddReason} }).dump();
}
static std::string Functions::Account::UpdateCurrency(CurrencyType CT, int CurrencyIndex, int Amount, int AddReason) { return UpdateCurrency(CT, NiggerParams::GetItemString(CurrencyIndex).c_str(), Amount, AddReason); }


static std::string Functions::Account::AddOffers(int startIndex, int endIndex, int OfferEndTime)
{
    std::string _;
    ojson dictionary = WS::Utils::__create(313, {
        {"i", 0},
        {"s", 1727622728},
        {"c", 0},
        {"p", 1727622728},
        {"e", OfferEndTime}
        });
    for (int i = startIndex; i < endIndex; i++) {
        dictionary["p"]["i"] = OfferIndexes[i];
        _ += dictionary.dump() + ",";
    }
    _.pop_back(); return _;
}


static std::string Functions::Account::InventoryAddItemSingle(int index, int cause)
{
    return WS::Utils::__create(84, {
        {"i", index},
        {"ca", cause}
    }).dump();
}


static ojson GenerateGiftData(std::string SenderID, std::string ReceiverID, std::string SenderClanID, ojson ItemData)
{
    /*
    std::time_t timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    int timestamp = static_cast<int>(timenow);
    */
    std::stringstream IdData;
    IdData << SenderID << "." << generateRandomNumber(1533954095, 1733954095) << ".1";
    return {
        {OBF("id"), IdData.str()},
        {OBF("v"), 1},
        {OBF("from"), SenderID},
        {OBF("for"), ReceiverID},
        {OBF("clan"), SenderClanID},
        {OBF("data"), ItemData},
        {OBF("pid"), OBF("1")},
        {OBF("ppl"), OBF("GameOffer")},
    };
}

static std::string Functions::Account::RegisterGift(int Amount, std::string SenderID, std::string ReceiverID, std::string SenderClanID, ojson ItemData)
{
    ojson command = WS::Utils::__create(165, {
        {OBF("category"), OBF("1")},
        {OBF("gifts"), ojson::array()}
    });

    ojson params = WS::Utils::__create(81, {
        {OBF("t"), 1230},
        {OBF("i"), 17018},
        {OBF("c"), 1}
    });

    ojson params2 = params; params2[OBF("id")] = 80;

    for (int i = 0; i < Amount; i++) { command["p"][OBF("gifts")].push_back(GenerateGiftData(SenderID, ReceiverID, SenderClanID, ItemData)); }

    return params2.dump() + "," + params.dump() + "," + command.dump();
}








// NAMESPACE: MENU

/************************************ QUICK ACC MAXING ************************************/

static void Functions::Menu::Account__MaxAccount()
{
    namespace Mods = Functions::Account;
    const char* _soefjneifrgief = OBF("Max Account");
    const char* wdfnmejfefg = OBF("update_progress"); // EventName
    vars::SendRequest = WS::Utils::AddRequest(wdfnmejfefg, Mods::AddWeaponsV2(Functions::WT_NORMAL, vars::PlayerLVL) + "," + Mods::AddCraftPartsV2(), 1, true, false, true, OBF("Max Account Step 1"), ImGuiToastType::Info, false, [_soefjneifrgief, wdfnmejfefg](ojson _r, ojson _p) {
        vars::SendRequest = WS::Utils::AddRequest(wdfnmejfefg, Mods::AddWeaponSkinsV2() + "," + Mods::AddGraffitisV2(), 1, true, false, true, OBF("Max Account Step 2"), ImGuiToastType::Info, false, [_soefjneifrgief, wdfnmejfefg](ojson _r, ojson _p) {
            vars::SendRequest = WS::Utils::AddRequest(wdfnmejfefg, Mods::AddAllWears(vars::CheckAutoMaxLvl()) + "," + Mods::AddAllRoyale(), 1, true, false, true, OBF("Max Account Step 3"), ImGuiToastType::Info, false, [_soefjneifrgief, wdfnmejfefg](ojson _r, ojson _p) {
                vars::SendRequest = WS::Utils::AddRequest(wdfnmejfefg, Mods::AddGadgets(vars::CheckAutoMaxLvl()) + "," + Mods::AddPets() + "," + Mods::AddModules() + "," + Functions::Account::AddWearSkinsV2() + "," + Functions::Account::AddWearSkinsV2(ARMOR, 1, 100) + "," + Functions::Account::AddLobbyItems(), 1, true, false, true, OBF("Max Account Step 4"), ImGuiToastType::Info, false, [_soefjneifrgief, wdfnmejfefg](ojson _r, ojson _p) {
                    vars::SendRequest = WS::Utils::AddRequest(wdfnmejfefg, Mods::UpgradeAllRoyale(), 1, true, false, true, OBF("Max Account Step 5"), ImGuiToastType::Info, false, [_soefjneifrgief, wdfnmejfefg](ojson _r, ojson _p) {
                        vars::SendRequest = WS::Utils::AddRequest(wdfnmejfefg, Mods::UpgradePets(vars::CheckAutoMaxLvl()), 1, true, false, true, OBF("Max Account Step 6 (LAST STEP)"), ImGuiToastType::Info, false, [_soefjneifrgief, wdfnmejfefg](ojson _r, ojson _p) {
                            vars::SendRequest = WS::Utils::AddRequest(wdfnmejfefg, Mods::UpgradeModules(), 1, true, vars::ReloadWhenReceived, true, _soefjneifrgief);
                        });
                    });
                });
            });
        });
    });
    WS::Utils::NotifyRequestSent(_soefjneifrgief);
}

static void Functions::Menu::Account__AddDlcSets()
{
    vars::AlwaysUpdateSlotsWhenRequestSent = false;
    vars::SendRequest = true;
    const char* ekdnmwejfbnf = OBF("update_progress");
    const char* _soefjneifrgief = OBF("Add All DLC Sets");
    for (int i = 0; i < 3; i++) {
        ojson idk = WS::Utils::__singleCreate(132, { {OBF("i"), BannedIndexes[i]}, {OBF("u"), {{OBF("l"), vars::PlayerLVL}, {OBF("r"), 5}}}, {OBF("oc"), 9999} });
        WS::Utils::AddRequest(ekdnmwejfbnf, idk.dump(), 1, false, false);
    }
    if (!StringContains(WS::Slots::Royale.dump(), OBF("1201005"))) WS::Utils::AddRequest(ekdnmwejfbnf, OBF(R"({"id":28, "i":"f8aa34a3", "p":{"1":"1201005", "ca":153}})"), 1, false, false);
    for (int i = 4; i < std::size(BannedIndexes) - 1; i++) {
        ojson idk = WS::Utils::__singleCreate(84, { {OBF("i"), BannedIndexes[i]}, {OBF("ca"), 153} });
        WS::Utils::AddRequest(ekdnmwejfbnf, idk.dump(), 1, false, false);
    }
    ojson idk = WS::Utils::__singleCreate(84, { {OBF("i"), BannedIndexes[std::size(BannedIndexes) - 1]}, {OBF("ca"), 153} });
    WS::Utils::AddRequest(ekdnmwejfbnf, idk.dump(), 1, false, vars::ReloadWhenReceived, true, _soefjneifrgief, ImGuiToastType::Info, false, [](ojson _r, ojson _p) { vars::AlwaysUpdateSlotsWhenRequestSent = true; });

    WS::Utils::NotifyRequestSent(_soefjneifrgief);
}

static void Functions::Menu::Misc__SendGift(int Amount, std::string ReceiverID, ojson ItemData)
{
    vars::AlwaysUpdateSlotsWhenRequestSent = false;
    const char* NotifyName = OBF("Crash Player");
    vars::SendRequest = WS::Utils::AddRequest(OBF("update_progress"), Functions::Account::RegisterGift(Amount, PlayerID.c_str(), ReceiverID, GetClanID().c_str(), ItemData), 1, true, false, false, "", ImGuiToastType::Info, false, [NotifyName](ojson _r, ojson _p) {
        ojson gifts = _r[OBF("p")][OBF("c")][2]["p"][OBF("gifts")];
        vars::SendRequest = WS::Utils::AddRequest(OBF("create_gifts"), ojson{ {OBF("gifts"), gifts} }.dump(), 1, false, false, true, NotifyName, ImGuiToastType::Info, false, [NotifyName, gifts](ojson _r, ojson _p) {
            ojson cmd = WS::Utils::__create(167, {
                {OBF("category"), "1"},
                {OBF("gifts"), ojson::array()}
            });

            for (int i = 0; i < gifts.size(); i++) {
                cmd[OBF("p")][OBF("gifts")].push_back(gifts[i][OBF("id")]);
            }

            vars::SendRequest = WS::Utils::AddRequest(OBF("update_progress"), cmd.dump(), 1, false, false, false, "", ImGuiToastType::Info, false, [](ojson _r, ojson _p) {
                vars::AlwaysUpdateSlotsWhenRequestSent = true;
            });
        });
    });
    WS::Utils::NotifyRequestSent(NotifyName);
}