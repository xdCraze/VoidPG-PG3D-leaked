#pragma once

#include "Headers/Menu/SxitxmaImGui.h"
#include "Backend/functions.h"


namespace vars
{
	// Account Tab
	// Main 1 Subtab
	bool WEAPONS_ManualUnlock = false;
	char WEAPONS_WeaponGalleryNumber[5] = "416";
	int WEAPONS_StartIndex = 1;
	int WEAPONS_EndIndex = 100;
	int WEAPONS_Level = 1;
	int WEAPONS_SelectedRarity = 5;
	struct WEAPONS_RarityStruct {
		const char* Name;
		int Rarity;
		int Level = 1;
		int Index = -1;
	};
	std::vector<WEAPONS_RarityStruct> WEAPONS_RarityCombo = { {"Common", 0}, {"Uncommon", 1}, {"Rare", 2}, {"Epic", 3}, {"Legendary", 4}, {"Mythic", 5} };
	std::vector<WEAPONS_RarityStruct> WEAPONS_request;


	struct CRAFT_PARTS_TypeStruct {
		const char* Name;
		Functions::CraftPartType CPT;
	};
	std::vector<CRAFT_PARTS_TypeStruct> CRAFT_PARTS_TypeCombo = { {"Weapons/Shovels", Functions::CraftPartType::NORMAL}, {"Wears/Gadgets", Functions::ITEM_CONSUMABLE}, {"Royale", Functions::ROYALE}, {"Avatar Sets", Functions::AVATAR_SET} };
	int CRAFT_PARTS_SelectedType = 0;
	int CRAFT_PARTS_StartIndex = 1;
	int CRAFT_PARTS_EndIndex = 2;
	int CRAFT_PARTS_PartsAmount = 250;


	int MISC_WEAPON_SKINS_StartIndex = 1;
	int MISC_WEAPON_SKINS_EndIndex = 2;
	int MISC_GRAFFITIS_StartIndex = 1;
	int MISC_GRAFFITIS_EndIndex = 2;


	int MODULES_StartIndex = 1;
	int MODULES_EndIndex = 2;
	int MODULES_Parts = 2500;
	int MODULES_Lvl = 10;
	int MODULES_LvlCap = 10;

	// Main 2 Subtab
	struct WEARS_TypeStruct {
		const char* Name;
		Functions::WearType WT;
	};
	std::vector<WEARS_TypeStruct> WEARS_TypeCombo = { {"Armors", Functions::ARMOR}, {"Hats", Functions::HAT}, {"Masks", Functions::MASK}, {"Capes", Functions::CAPE}, {"Boots", Functions::BOOTS} };
	int WEARS_SelectedType = 0;
	int WEARS_StartIndex = 1;
	int WEARS_EndIndex = 2;
	int WEARS_ArmorLevel = 65;

	std::vector<WEARS_TypeStruct> WEAR_SKINS_TypeCombo = { {"Armors", Functions::ARMOR}, {"All Except Armors", Functions::ALL_EXCEPT_ARMOR} };
	int WEAR_SKINS_SelectedType = 0;
	int WEAR_SKINS_StartIndex = 1;
	int WEAR_SKINS_EndIndex = 2;

	int GADGETS_StartIndex = 1;
	int GADGETS_EndIndex = 2;
	int GADGETS_Level = 65;

	int PETS_StartIndex = 1;
	int PETS_EndIndex = 2;
	int PETS_Parts = 999;
	int PETS_Level = 65;

	// Royale Subtab
	struct ROYALE_ADDER_TypeStruct {
		const char* Name;
		Functions::RoyaleType RT;
	};
	std::vector<ROYALE_ADDER_TypeStruct> ROYALE_ADDER_TypeCombo = { {"Avatars", Functions::AVATAR}, {"Gliders", Functions::GLIDER}, {"Shovels", Functions::SHOVEL}, {"Trails", Functions::TRAIL}, {"Cars", Functions::CAR} };
	int ROYALE_ADDER_SelectedType = 0;
	int ROYALE_ADDER_StartIndex = 1;
	int ROYALE_ADDER_EndIndex = 2;

	// Max Account Subtab
	// Already Defined in vars.h file
	int MAX_ACC_LVL = 40;

	// Stats Tab
	// Main Subtab
	enum MONTHLY_TYPEENUM {
		KILLS = 204783,
		DEATHS = 304783, // Killrate
		HEADSHOTS = 937453,
		ACCURACY = 937535,
		KILLSTREAK = 3946,
		WINSTREAK = 29476325,
		WINS = 3873485,
		MATCHES = 934738,
	};
	struct MONTHLY_TypeStruct {
		const char* Name;
		const char* UpdateValueName;
		MONTHLY_TYPEENUM StatType;
	};
	std::vector<MONTHLY_TypeStruct> MONTHLY_TypeCombo = {
		{"Kills", "Add", KILLS},
		{"Killrate", "Add", DEATHS},
		{"Headshots", "Add", HEADSHOTS},
		{"Accuracy", "Add", ACCURACY},
		{"Killstreak", "Set", KILLSTREAK},
		{"Winstreak", "Set", WINSTREAK},
		{"Wins", "Add", WINS},
		{"Matches", "Add", MATCHES}
	};
	int MONTHLY_SelectedType = 0;
	char MONTHLY_UpdateAmount[6] = "1";


	struct MODES_TypeStruct {
		const char* Name;
		int ModeIndex;
	};
	std::vector<MODES_TypeStruct> MODES_TypeCombo = { {"Deathmatch", 0}, {"Teamfight", 2}, {"Battle Royale", 20}, {"Free Play", 31}, {"Capture", 4}, {"Duels", 8}, {"Teamstrike", 16} };
	int MODES_SelectedType = 0;
	char MODES_AddAmount[5] = "500";

	// Other Tab
	// Offers Subtab
	// Paid Offers: Already Defined in vars.h file
	int OFFERS_StartIndex = 1;
	int OFFERS_EndIndex = 2;


	struct CURRENCY_TypeStruct {
		const char* Name;
		int Index;
	};
	std::vector<CURRENCY_TypeStruct> CURRENCY_TypeCombo = {
		{"Coins", 1015},
		{"Gems", 2015},
		{"Coupons", 7015},
		{"Pixel Pass Tickets", 26015},
		{"Clan Silver", 8015}
	};
	int CURRENCY_SelectedType = 0;
	char CURRENCY_AddAmount[8] = "1";


	// Misc Subtab
	// Fun
	char FUN_TargetID[30];

	// Auth Subtab
	// Token Info: Already Defined in vars.h file
	// Auth Info
	char AUTH_PlayerID[30];
	char AUTH_PlayerSecret[100];

	// Account Generator
	int AUTH_GenerateAccountsAmount = 1;

	// Settings Tab
	// Already Defined in vars.h file
}

namespace Menu {
	int MainTabValue;
	struct SubTab {
		int TabValue;
		const char* TabName;
	};
	struct MenuTab {
		int TabValue;
		const char* TabIcon;
		const char* TabName;
		std::vector<SubTab> Subtabs = { {0, "Main"} };
	};
	std::vector<MenuTab> MenuTabs = {
		{ // [0] = Account Tab
			0, ICON_FA_USER, "Account", {
				{0, "Main"},
				{1, "Main 2"},
				{2, "Royale"},
				{3, "Max Acc"},
			},
		},
		{ // [1] = Stats Tab
			1, ICON_FA_CHART_BAR, "Stats", {
				{0, "Main"},
			}
		},
		{ // [2] = Other Tab
			2, "...", "Other", {
				{0, "Game"},
				{1, "Misc"},
				{2, "Auth"},
			}
		},
		{ // [3] = Settings Tab
			3, ICON_FA_GEAR, "Settings", {
				{0, "Main"},
				{1, "Menu"},
			}
		}
	};
	int AccountSubTabs;
	int StatsSubTabs;
	int OtherSubTabs;
	int DevSubTabs;
	int SettingsSubTabs;

	//float MenuBGFGlowColor[] = { 0.f, 0.f, 255.f, 0.6f };
	float MenuBGFGlowColor[4] = { 223.f, 223.f, 238.f, 0.75f };
	float MenuBGFrameThickness = 200.0f;

	const float ClearBGColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	bool BlackBackground = false;

	ImVec2 MenuChildSize = ImVec2(268, 200);
	ImVec2 MenuFullChildSize = ImVec2(542, 400);
	ImVec2 MenuHalfChildSize1 = ImVec2(274, 400);
	ImVec2 MenuHalfChildSize2 = ImVec2(268, 400);

	ImVec2 MenuChildPos1 = ImVec2(150, 81);
	ImVec2 MenuChildPos2 = ImVec2(150 + MenuChildSize.x + 12, 81);
	ImVec2 MenuChildPos3 = ImVec2(150, 81 + MenuChildSize.y + 6);
	ImVec2 MenuChildPos4 = ImVec2(MenuChildPos2.x, MenuChildPos3.y);
}



void Backend::UnloadImGui()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}