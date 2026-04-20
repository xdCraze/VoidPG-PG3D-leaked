#pragma once

#include <iostream>
#include <map>
#include <vector>

/*
struct CurrencyData
{
    const char* Name;
    const char* StringName;
    const char* Type; // Available Options: "c", "i"    (Currency, Item)
    int Index = 0;    // Optional
    int OfferItemTypeIndex = 0;    // Optional
};
std::vector<CurrencyData> curList = {
    {"Coins",						"Coins",				"c",		1015	},
    {"Gems",						"GemsCurrency",			"c",		2015	},
    {"Coupons",						"Coupons",				"c",		7015	},
    {"Clan Silver",					"ClanSilver",			"c",		8015	},
    {"Pixel Pass Tickets",			"PixelPassCurrency",	"c",		26015	},
    {"Pixel Pass XP",				"PixelPassExp",			"c",		25015	},
    {"Helper Goblin",				"cw_tribute_auto",		"i",		2020	},
    {"Small Chest",					"small_chest",			"i",		500015	},
    {"Medium Chest",				"medium_chest",			"i",		501015	},
    {"Big Chest",					"big_chest",			"i",		502015	},
    {"Super Chest",					"super_chest",			"i",		503015	},
};
int CurrentSelectedCurrency = 0;
*/


std::vector<int> GliderIndexes;
std::vector<int> ShovelIndexes;
std::vector<int> AvatarIndexes;
std::vector<int> TrailIndexes;
std::vector<int> CarIndexes;

std::vector<int> ArmorIndexes;
std::vector<int> HatIndexes;
std::vector<int> MaskIndexes;
std::vector<int> CapeIndexes;
std::vector<int> BootsIndexes;

std::vector<int> PetIndexes;
std::vector<int> GadgetIndexes;
std::vector<int> LobbyItemIndexes;
std::vector<int> ModuleIndexes;
std::vector<int> ModulePointIndexes;


int SetIndexes[] = {
    1031,2031,3031,4031,5031,6031,7031,8031,9031,10031,11031,12031,13031,14031,15031,16031,17031,18031,19031,20031,21031,22031,23031,
    24031,25031,26031,27031,28031,29031,30031,31031,32031,33031,34031,35031,36031,37031,38031,39031,40031,41031,42031,43031,44031,
    45031,46031,47031,48031,49031,50031,51031,52031,53031,54031,55031,56031,57031,58031,59031,60031,61031,62031,63031,64031,65031,
    66031,67031,68031,69031,70031,71031,72031,73031,74031,75031,76031,77031,78031,79031,80031,81031,82031,83031,84031,85031,86031,
    87031,88031,89031,90031,91031,92031,93031,94031,95031,96031,97031,98031,99031,100031,101031,/*113031, rgb pioneer set*/114031,115031,116031,117031,
    118031,119031,120031,121031,102031,103031,104031,105031,106031,107031,108031,109031,110031,111031,112031
};

std::vector<int> CraftSetIndexes = { // cyber santa, halloween etc.
    1008, 3008, 7008, 9008
};



int DlcWeaponSkinIndexes[] = {
    496014, 497014, 498014, 499014, 500014, 501014, 502014, 503014, 504014, 505014, 506014, 507014, 508014, 509014, 510014, 511014, 512014, 513014,
    531014, 532014, 534014, 535014, 537014, 538014, 539014, 540014, 541014, 547014
};


int TutorialIndexes[] = {
    0, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800
};


int BannedIndexes[] = {
    1702001, 1703001, 1704001, 1201005,
    496014, 497014, 498014, 499014, 500014, 501014, 502014, 503014, 504014, 505014, 506014, 507014, 508014, 509014, 510014, 511014, 512014, 513014,
    531014, 532014, 534014, 535014, 537014, 538014, 539014, 540014, 541014, 547014
};


std::vector<int> OfferIndexes = {
    397211, 398211, 399211, 400211, 401211, 402211, 403211, 404211, 405211, 406211, 407211, 408211, 428211, 429211, 430211, 431211, 997211, 1546211, 1560211, 1561211, 1562211, 1563211, 1564211, 1565211, 1566211, 1567211, 1568211, 1569211, 1570211, 1571211, 1572211, 1573211, 1574211, 1575211, 1576211, 1577211, 1578211, 1579211, 1580211, 1581211, 1582211, 1583211, 1596211, 1597211, 1598211, 1599211, 1600211, 1601211, 1602211, 1603211, 1841211, 1842211, 1843211, 1844211, 1845211, 1846211, 1847211, 1848211, 1849211, 1850211, 1851211, 1852211, 1853211, 1854211, 1855211, 1856211, 1857211, 1858211, 1859211, 1860211, 1861211, 1862211, 1863211, 1864211, 1865211, 1866211, 1928211, 1938211, 1939211, 1940211, 1941211, 1942211, 1943211, 1944211, 1945211, 1946211, 1947211, 1948211, 1949211, 1950211, 1951211, 1952211, 1953211, 1954211, 1955211, 1956211, 1957211, 1958211, 1959211, 1960211, 1961211
};


std::vector<int> ProgressRoad = {
    -1,              // 0
    0,               // 1
    15,              // 2
    65,              // 3
    170,             // 4
    280,             // 5
    395,             // 6
    515,             // 7
    640,             // 8
    770,             // 9
    910,             // 10
    1055,            // 11
    1210,            // 12
    1370,            // 13
    1540,            // 14
    1715,            // 15
    1900,            // 16
    2095,            // 17
    2300,            // 18
    2515,            // 19
    2750,            // 20
    3000,            // 21
    3270,            // 22
    3560,            // 23
    3870,            // 24
    4195,            // 25
    4540,            // 26
    4905,            // 27
    5290,            // 28
    5690,            // 29
    6110,            // 30
    6550,            // 31
    7010,            // 32
    7485,            // 33
    7980,            // 34
    8495,            // 35
    9030,            // 36
    9580,            // 37
    10150,           // 38
    10740,           // 39
    11350,           // 40
    11975,           // 41
    12620,           // 42
    13285,           // 43
    13970,           // 44
    14670,           // 45
    15390,           // 46
    16130,           // 47
    16890,           // 48
    17665,           // 49
    18460,           // 50
    19275,           // 51
    20110,           // 52
    20960,           // 53
    21830,           // 54
    22720,           // 55
    23630,           // 56
    24555,           // 57
    25550,           // 58
    26465,           // 59
    27450,           // 60
    28450,           // 61
    29470,           // 62
    30510,           // 63
    31570,           // 64
    32645,           // 65
};


std::map<std::string, int> ItemIndex = {
    { "Gems",                       2015},
    { "Keys",                       6015},
    { "Coupons",                    7015},
    { "Player XP",                  15015},
    { "Pixel Pass XP",              25015},
    { "Pixel Pass Tickets",         26015},
    { "Weapon Chest",               192027},
    { "Novice Chest",               500015},
};

std::map<std::string, int> OfferItemType_dict = {
    { "None",                 0    },
    { "Weapons",              10   },
    { "Armor",                20   },
    { "Mask",                 30   },
    { "Hat",                  40   },
    { "Boots",                50   },
    { "Cape",                 60   },
    { "Skin",                 65   },
    { "Gadget",               70   },
    { "Pet",                  80   },
    { "Egg",                  83   },
    { "LobbyItem",            85   },
    { "FortItem",             90   },
    { "Gems",                 1000 },
    { "Coins",                1010 },
    { "Leprechaun",           1020 },
    { "WeaponUpgrade",        1030 },
    { "GachaFreeSpin",        1040 },
    { "EventCurrency",        1050 },
    { "VIP",                  1060 },
    { "Parts",                1070 },
    { "Royale",               1080 },
    { "BattlePassLevel",      1090 },
    { "BattlePassExp",        1100 },
    { "BattlePassCurrency",   1110 },
    { "GoldenSkin",           1120 },
    { "EventChest",           1130 },
    { "CraftCurrency",        1140 },
    { "Module",               1150 },
    { "ModulePoint",          1155 },
    { "ModuleChest",          1160 },
    { "WeaponSkin",           1170 },
    { "ClanCurrency",         1180 },
    { "Coupons",              1190 },
    { "Currency",             1200 },
    { "Character",            1210 },
    { "ClanShields",          1220 },
    { "ClanLootBox",          1230 },
    { "ClanPlaceable",        1240 },
    { "ClanPlaceablePoint",   1250 },
    { "Detail",               1300 },
    { "WeaponLevelUpgrade",   1310 },
    { "PlayerBuff",           1320 },
    { "ClanBuff",             1330 },
    { "WeaponQualityUpgrade", 1340 },
    { "ArmorSkin",            1350 },
    { "ClanBuilding",         1360 },
    { "ClanBuildingPoint",    1370 },
    { "FreeUpgrade",          1380 },
    { "Chest",                1390 },
    { "Exp",                  1400 },
    { "Stats",                1410 },
    { "ModeSlots",            1420 },
    { "Executable",           1430 },
    { "Tank",                 1440 },
    { "VIP20",                1450 },
    { "LootBox",              1460 },
    { "Graffiti",             1470 },
    { "PixelPassExp",         1490 },
    { "ClanRankExperience",   1500 },
    { "WearSkin",             1510 },
    { "Applicable",           1520 },
    { "CraftSet",             1530 },
    { "FeatureExp",           1540 },
    { "PackagedItem",         1550 },
    { "Achievement",          1560 },
    { "ExpirySimple",         1570 },
    { "Static",               1580 },
    { "GemsHarvester",        1590 },
    { "TreasureMap",          1600 },
    { "ProfileBackgroundUI",  1610 },
    { "PortraitFrameUI",      1620 },
    { "PortraitUI",           1630 },
};

std::map<std::string, int> CategoryNames_dict = {
    {"GlidersRoyaleCategory",        160000},
    //{"ShovelsRoyaleCategory",        170000},
    {"HatsRoyaleCategory",           180000},
    {"RoyaleAvatarsCategory",        190000},
    {"TrailRoyaleCategory",          200000},
    {"TransportRoyaleCategory",      210000},
};


std::map<std::string, int> SlotIndex = {
    { "PlayerInfo",                         1},
    { "Currency",                           3},
    { "Leveling",                           4},
    { "LobbyCraft",                         6},
    { "SkinsIds",                           10},
    { "BattleRoyaleIds",                    11},
    { "Wear",                               13},
    { "Gadgets",                            16},
    { "BattleRoyaleVehicle",                25},
    { "ModuleStorage",                      27},
    { "WeaponsV17",                         28},
    { "WeaponSkinV2",                       32},
    { "Gifts",                              36},
    { "ModulesInfo",                        37},
    { "Armor",                              43},
    { "PetsV3",                             53},
    { "Tutorial",                           56},
};



// SLOTS
/*

    public const 不丈万丝一三丘丐专 PlayerInfo = 1; // Index: 0x1 Offset: 0x0
    public const 不丈万丝一三丘丐专 Rating = 2; // Index: 0x2 Offset: 0x0
    public const 不丈万丝一三丘丐专 Currency = 3; // Index: 0x3 Offset: 0x0
    public const 不丈万丝一三丘丐专 Leveling = 4; // Index: 0x4 Offset: 0x0
    public const 不丈万丝一三丘丐专 Achievement = 5; // Index: 0x5 Offset: 0x0
    public const 不丈万丝一三丘丐专 LobbyCraft = 6; // Index: 0x6 Offset: 0x0
    public const 不丈万丝一三丘丐专 Campaign = 7; // Index: 0x7 Offset: 0x0
    public const 不丈万丝一三丘丐专 PlayerEquipment = 9; // Index: 0x8 Offset: 0x0
    public const 不丈万丝一三丘丐专 SkinsIds = 10; // Index: 0x9 Offset: 0x0
    public const 不丈万丝一三丘丐专 BattleRoyaleIds = 11; // Index: 0xa Offset: 0x0
    public const 不丈万丝一三丘丐专 CustomSkin = 12; // Index: 0xb Offset: 0x0
    public const 不丈万丝一三丘丐专 Wear = 13; // Index: 0xc Offset: 0x0
    public const 不丈万丝一三丘丐专 UtilityDictionary = 14; // Index: 0xd Offset: 0x0
    public const 不丈万丝一三丘丐专 UtilityIds = 15; // Index: 0xe Offset: 0x0
    public const 不丈万丝一三丘丐专 Gadgets = 16; // Index: 0xf Offset: 0x0
    public const 不丈万丝一三丘丐专 WeaponSkin = 17; // Index: 0x10 Offset: 0x0
    public const 不丈万丝一三丘丐专 GameEvents = 19; // Index: 0x11 Offset: 0x0
    public const 不丈万丝一三丘丐专 GME = 20; // Index: 0x12 Offset: 0x0
    public const 不丈万丝一三丘丐专 GatchaGifts = 21; // Index: 0x13 Offset: 0x0
    public const 不丈万丝一三丘丐专 Details = 24; // Index: 0x14 Offset: 0x0
    public const 不丈万丝一三丘丐专 BattleRoyaleVehicle = 25; // Index: 0x15 Offset: 0x0
    public const 不丈万丝一三丘丐专 Inventory = 26; // Index: 0x16 Offset: 0x0
    public const 不丈万丝一三丘丐专 ModuleStorage = 27; // Index: 0x17 Offset: 0x0
    public const 不丈万丝一三丘丐专 WeaponsV17 = 28; // Index: 0x18 Offset: 0x0
    public const 不丈万丝一三丘丐专 FirstUpsV17 = 29; // Index: 0x19 Offset: 0x0
    public const 不丈万丝一三丘丐专 Offers = 30; // Index: 0x1a Offset: 0x0
    public const 不丈万丝一三丘丐专 RankSlot = 31; // Index: 0x1b Offset: 0x0
    public const 不丈万丝一三丘丐专 WeaponSkinV2 = 32; // Index: 0x1c Offset: 0x0
    public const 不丈万丝一三丘丐专 GameTask = 33; // Index: 0x1d Offset: 0x0
    public const 不丈万丝一三丘丐专 AlmanachSlot = 34; // Index: 0x1e Offset: 0x0
    public const 不丈万丝一三丘丐专 InAppValidatorSlot = 35; // Index: 0x1f Offset: 0x0
    public const 不丈万丝一三丘丐专 Gifts = 36; // Index: 0x20 Offset: 0x0
    public const 不丈万丝一三丘丐专 ModulesInfo = 37; // Index: 0x21 Offset: 0x0
    public const 不丈万丝一三丘丐专 ClanItems = 38; // Index: 0x22 Offset: 0x0
    public const 不丈万丝一三丘丐专 ClanFinishingUpgrades = 40; // Index: 0x23 Offset: 0x0
    public const 不丈万丝一三丘丐专 InventoryExpiry = 41; // Index: 0x24 Offset: 0x0
    public const 不丈万丝一三丘丐专 MailBoxRewards = 42; // Index: 0x25 Offset: 0x0
    public const 不丈万丝一三丘丐专 Armor = 43; // Index: 0x26 Offset: 0x0
    public const 不丈万丝一三丘丐专 ArmorSkins = 44; // Index: 0x27 Offset: 0x0
    public const 不丈万丝一三丘丐专 KillRate = 45; // Index: 0x28 Offset: 0x0
    public const 不丈万丝一三丘丐专 BlackMarket = 46; // Index: 0x29 Offset: 0x0
    public const 不丈万丝一三丘丐专 ClanStorePromotion = 47; // Index: 0x2a Offset: 0x0
    public const 不丈万丝一三丘丐专 PetsV3 = 53; // Index: 0x2b Offset: 0x0
    public const 不丈万丝一三丘丐专 RankV2 = 54; // Index: 0x2c Offset: 0x0
    public const 不丈万丝一三丘丐专 TrophyRoad = 55; // Index: 0x2d Offset: 0x0
    public const 不丈万丝一三丘丐专 Tutorial = 56; // Index: 0x2e Offset: 0x0
    public const 不丈万丝一三丘丐专 MatchHistory = 57; // Index: 0x2f Offset: 0x0
    public const 不丈万丝一三丘丐专 ConstructableOffers = 58; // Index: 0x30 Offset: 0x0
    public const 不丈万丝一三丘丐专 WeaponSkinsNotification = 59; // Index: 0x31 Offset: 0x0
    public const 不丈万丝一三丘丐专 GameEventDropChance = 60; // Index: 0x32 Offset: 0x0
    public const 不丈万丝一三丘丐专 MapSecretsSlot = 62; // Index: 0x33 Offset: 0x0
    public const 不丈万丝一三丘丐专 ManualOffers = 64; // Index: 0x34 Offset: 0x0
    public const 不丈万丝一三丘丐专 DoubleOffers = 65; // Index: 0x35 Offset: 0x0
    public const 不丈万丝一三丘丐专 Vip20 = 66; // Index: 0x36 Offset: 0x0
    public const 不丈万丝一三丘丐专 Loadouts = 67; // Index: 0x37 Offset: 0x0
    public const 不丈万丝一三丘丐专 GachaNoviceGift = 68; // Index: 0x38 Offset: 0x0
    public const 不丈万丝一三丘丐专 Piggy = 69; // Index: 0x39 Offset: 0x0
    public const 不丈万丝一三丘丐专 NoviceDoubleOffers = 70; // Index: 0x3a Offset: 0x0
    public const 不丈万丝一三丘丐专 ProgressRoad = 71; // Index: 0x3b Offset: 0x0
    public const 不丈万丝一三丘丐专 Attributes = 72; // Index: 0x3c Offset: 0x0
    public const 不丈万丝一三丘丐专 UniversalPromotion = 73; // Index: 0x3d Offset: 0x0
    public const 不丈万丝一三丘丐专 PixelPass = 74; // Index: 0x3e Offset: 0x0
    public const 不丈万丝一三丘丐专 GameModeHub = 75; // Index: 0x3f Offset: 0x0
    public const 不丈万丝一三丘丐专 Shop = 76; // Index: 0x40 Offset: 0x0
    public const 不丈万丝一三丘丐专 BattleStatistic = 77; // Index: 0x41 Offset: 0x0
    public const 不丈万丝一三丘丐专 Subscription20 = 78; // Index: 0x42 Offset: 0x0
    public const 不丈万丝一三丘丐专 Promocode = 79; // Index: 0x43 Offset: 0x0
    public const 不丈万丝一三丘丐专 InappTransaction = 81; // Index: 0x44 Offset: 0x0
    public const 不丈万丝一三丘丐专 WearSkins = 82; // Index: 0x45 Offset: 0x0
    public const 不丈万丝一三丘丐专 RouletteAds = 83; // Index: 0x46 Offset: 0x0
    public const 不丈万丝一三丘丐专 PlayerStatsV2 = 84; // Index: 0x47 Offset: 0x0
    public const 不丈万丝一三丘丐专 ConstructableAdsOffers = 85; // Index: 0x48 Offset: 0x0
    public const 不丈万丝一三丘丐专 ClanWarV2 = 86; // Index: 0x49 Offset: 0x0
    public const 不丈万丝一三丘丐专 CardRoulette = 87; // Index: 0x4a Offset: 0x0
    public const 不丈万丝一三丘丐专 ConfrontationEvent = 90; // Index: 0x4b Offset: 0x0
    public const 不丈万丝一三丘丐专 TemplateEventsSlot = 91; // Index: 0x4c Offset: 0x0
    public const 不丈万丝一三丘丐专 ConfrontationEventV2 = 92; // Index: 0x4d Offset: 0x0
    public const 不丈万丝一三丘丐专 GameModeShop = 93; // Index: 0x4e Offset: 0x0
    public const 不丈万丝一三丘丐专 GMHRecommendation = 95; // Index: 0x4f Offset: 0x0
    public const 不丈万丝一三丘丐专 GMHTournament = 96; // Index: 0x50 Offset: 0x0
    public const 不丈万丝一三丘丐专 SteamDlcShop = 97; // Index: 0x51 Offset: 0x0
    public const 不丈万丝一三丘丐专 ViewedEntry = 98; // Index: 0x52 Offset: 0x0
    public const 不丈万丝一三丘丐专 CardRouletteV2 = 99; // Index: 0x53 Offset: 0x0
    public const 不丈万丝一三丘丐专 PersonalizedEvents = 100; // Index: 0x54 Offset: 0x0

*/