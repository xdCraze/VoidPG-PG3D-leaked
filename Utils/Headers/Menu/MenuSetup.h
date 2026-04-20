#pragma once

#include "MenuDefs.h"



ImVec2 woeikfufsef[] = {ImVec2(540, 33), ImVec2(490, 33), ImVec2(440, 33) , ImVec2(390, 33)}; // 4 subtabs support
//ImVec2 woeikfufsef[] = {ImVec2(540, 33), ImVec2(470, 33), ImVec2(400, 33), ImVec2(330, 33), ImVec2(260, 33), ImVec2(190, 33), ImVec2(155, 33)}; // 7 subtabs support (change expiry and user info position tho)
void DrawSubTabs(int maintabvalue, int* subtab, std::string labelstart) // NOTE: 4 SubTabs is max
{
    auto _subtabs = Menu::MenuTabs[maintabvalue].Subtabs;
    int _size = (int)_subtabs.size();
    std::string _;
    ImGui::SetCursorPos(woeikfufsef[_size - 1]);
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < (i + 1); j++) {
            _ += labelstart + " _";
        }
        if (ImGui::SubTab(*subtab == _subtabs[i].TabValue, _.c_str(), _subtabs[i].TabName, ImVec2(70, 30))) *subtab = _subtabs[i].TabValue;
        if (_size > 1) ImGui::SameLine();
    }
}

void DrawMenu(const char* User, const char* Expiry)
{
    auto pos = ImVec2{};
    pos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y); //drag

    // add frame glow effect
    ImGui::GetBackgroundDrawList()->AddShadowRect(ImGui::GetWindowPos(), ImVec2(pos.x + 250 + 450, pos.y + 480), ImColor(Menu::MenuBGFGlowColor[0], Menu::MenuBGFGlowColor[1], Menu::MenuBGFGlowColor[2], Menu::MenuBGFGlowColor[3]), Menu::MenuBGFrameThickness, ImVec2(0, 0), 1, 10);

    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x + 132, pos.y + 480), ImColor(15, 13, 15), 10, ImDrawFlags_RoundCornersLeft);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 132, pos.y), ImVec2(pos.x + 132 + 568, pos.y + 480), ImColor(20, 18, 20), 10, ImDrawFlags_RoundCornersRight);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + 132 + 10, pos.y + 10), ImVec2(pos.x + 132 + 10 + 548, pos.y + 10 + 58), ImColor(15, 13, 15), 4);
    
    ImGui::SetWindowFontScale(2.0f);
    ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 132 + 20, pos.y + 10 + 10), ImColor(116, 102, 149), ICON_FA_ID_CARD);
    ImGui::SetWindowFontScale(1.0f);

    ImGui::PushFont(ImGui::Fonts::MuseoSansMain);
    
    ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 132 + 10 + 14 + 30 + 4, pos.y + 10 + 16), ImColor(255, 255, 255), User);
    ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 132 + 10 + 14 + 30 + 4, pos.y + 10 + 30), ImColor(116, 102, 149), "Sub Expiry: ");
    ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 132 + 10 + 14 + 30 + 4 + ImGui::CalcTextSize("Sub Expiry: ").x, pos.y + 10 + 30), ImColor(116, 102, 149), Expiry);

    ImGui::PopFont();

    ImGui::SetWindowFontScale(1.2f);

    // Void
    ImGui::GetWindowDrawList()->AddShadowRect(ImVec2(pos.x + ImGui::CalcTextSize("Void").x + 15, pos.y + 35), ImVec2(pos.x + ImGui::CalcTextSize("Void").x + 30, pos.y + 35), ImColor(255, 255, 255, 120), 40, ImVec2(0, 0), 1, 10);
    ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 38, pos.y + 25), ImColor(255, 255, 255), "Void");
    // PG
    ImGui::GetWindowDrawList()->AddShadowRect(ImVec2(pos.x + ImGui::CalcTextSize("VoidPG").x + 15, pos.y + 35), ImVec2(pos.x + ImGui::CalcTextSize("VoidPG").x + 30, pos.y + 35), ImColor(157, 131, 216, 120), 40, ImVec2(0, 0), 1, 10);
    ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 38 + ImGui::CalcTextSize("Void").x, pos.y + 25), ImColor(157, 131, 216), "PG");
    
    ImGui::SetWindowFontScale(1.0f);
}

void DrawMainMenu()
{
    std::vector<Menu::MenuTab> _MenuTabs = Menu::MenuTabs;
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    ImGui::SetNextWindowSize(ImVec2(800, 600));
    ImGui::Begin(OBF("##voidPG"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDecoration);
    {
        DrawMenu(vars::ekfmwfmfiweiwd, vars::wwofmiejfewdfj);

        ImGui::SetWindowFontScale(0.8f);
        ImGui::SetCursorPos(ImVec2(20, 87));
        ImGui::BeginGroup();
        {
            for (int i = 0; i < Menu::MenuTabs.size(); i++) {
                if (ImGui::Tab(Menu::MainTabValue == Menu::MenuTabs[i].TabValue, Menu::MenuTabs[i].TabIcon, Menu::MenuTabs[i].TabName, ImVec2(122, 27))) Menu::MainTabValue = Menu::MenuTabs[i].TabValue;
            }
        }
        ImGui::EndGroup();
        ImGui::SetWindowFontScale(1.0f);

        const char* dikfnhjefb = OBF("update_progress");

        if (Menu::MainTabValue == _MenuTabs[0].TabValue) // ACCOUNT TAB
        {
            int _TabValue = _MenuTabs[0].TabValue;
            auto _Subtabs = _MenuTabs[_TabValue].Subtabs;
            ImGui::PushFont(ImGui::Fonts::MuseoSansMain);
            DrawSubTabs(_TabValue, &Menu::AccountSubTabs, "a");

            if (Menu::AccountSubTabs == _Subtabs[0].TabValue) { // MAIN SUBTAB
                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("wdefrg", OBF("Modules"), Menu::MenuChildSize); // MODULES CHILD
                {
                    int niggerdivian = (int)ModuleIndexes.size();
                    ImGui::CustomSliderInt("wefjednf", "Start", &vars::MODULES_StartIndex, 1, niggerdivian);
                    ImGui::CustomSliderInt("efefrgss", "End", &vars::MODULES_EndIndex, 2, niggerdivian + 1);
                    ImGui::CustomSliderInt("wdiedfsf", "Parts", &vars::MODULES_Parts, 1000, 5000);
                    if (vars::MODULES_StartIndex >= vars::MODULES_EndIndex) vars::MODULES_StartIndex = vars::MODULES_EndIndex - 1;

                    if (ImGui::CustomButton("___�...", OBF("Add Modules"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddModules(vars::MODULES_Parts, vars::MODULES_StartIndex - 1, vars::MODULES_EndIndex - 1), OBF("Add Modules"));

                    ImGui::NewLine();
                    ImGui::CustomSliderInt("ienfef", "Level", &vars::MODULES_Lvl, 1, 10);
                    ImGui::CustomSliderInt("wfikefer", "Level Cap", &vars::MODULES_LvlCap, 1, 10);

                    if (ImGui::CustomButton("___�efef..", OBF("Add Levels"))) QuickMenuSend(dikfnhjefb, Functions::Account::UpgradeModules(vars::MODULES_Lvl, vars::MODULES_LvlCap, vars::MODULES_StartIndex - 1, vars::MODULES_EndIndex - 1), OBF("Upgrade Modules"));
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("awdoawefjse", "Misc", Menu::MenuChildSize); // MISC CHILD
                {
                    ImGui::CustomSliderInt("dwdwdd", "Start", &vars::MISC_WEAPON_SKINS_StartIndex, 1, 799);
                    ImGui::CustomSliderInt("eifedf", "End", &vars::MISC_WEAPON_SKINS_EndIndex, 2, 800);
                    if (vars::MISC_WEAPON_SKINS_StartIndex >= vars::MISC_WEAPON_SKINS_EndIndex) vars::MISC_WEAPON_SKINS_StartIndex = vars::MISC_WEAPON_SKINS_EndIndex - 1;

                    if (ImGui::CustomButton("_wsdwf__�...", OBF("Add Weapon Skins"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddWeaponSkinsV2(vars::MISC_WEAPON_SKINS_StartIndex, vars::MISC_WEAPON_SKINS_EndIndex), OBF("Add Weapon Skins"));

                    ImGui::NewLine();
                    ImGui::CustomSliderInt("awfaegwfw", "Start", &vars::MISC_GRAFFITIS_StartIndex, 1, 99);
                    ImGui::CustomSliderInt("dwdegsegf", "End", &vars::MISC_GRAFFITIS_EndIndex, 2, 100);
                    if (vars::MISC_GRAFFITIS_StartIndex >= vars::MISC_GRAFFITIS_EndIndex) vars::MISC_GRAFFITIS_StartIndex = vars::MISC_GRAFFITIS_EndIndex - 1;

                    if (ImGui::CustomButton("___wdfejnf", OBF("Add Graffitis"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddGraffitisV2(vars::MISC_GRAFFITIS_StartIndex, vars::MISC_GRAFFITIS_EndIndex), OBF("Add Graffitis"));
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos3);
                ImGui::CustomBeginChild("kwewhdefh", "Weapons", Menu::MenuChildSize); // WEAPONS CHILD
                {
                    ImGui::Checkbox("Manual Unlock", &vars::WEAPONS_ManualUnlock);
                    if (vars::WEAPONS_ManualUnlock) {
                        ImGui::SameLine();
                        ImGui::CustomInputText("ekfnejfbner", "Weapon Gallery Number", vars::WEAPONS_WeaponGalleryNumber, std::size(vars::WEAPONS_WeaponGalleryNumber));
                    }
                    else {
                        ImGui::CustomSliderInt("efnerf", "Start", &vars::WEAPONS_StartIndex, 1, 1999);
                        ImGui::CustomSliderInt("eifef", "End", &vars::WEAPONS_EndIndex, 2, 2000);

                        if (vars::WEAPONS_StartIndex >= vars::WEAPONS_EndIndex) vars::WEAPONS_StartIndex = vars::WEAPONS_EndIndex - 1;
                    }

                    ImGui::NewLine(); ImGui::SameLine();
                    ImGui::CustomCombo<vars::WEAPONS_RarityStruct>("Weapon Rarity", vars::WEAPONS_RarityCombo, &vars::WEAPONS_SelectedRarity, vars::WEAPONS_RarityCombo[vars::WEAPONS_SelectedRarity].Name);
                    ImGui::SliderInt("Weapon Level", &vars::WEAPONS_Level, 1, 65);
                    if (vars::WEAPONS_Level > vars::PlayerLVL) vars::WEAPONS_Level = vars::PlayerLVL;

                    int rarity = vars::WEAPONS_RarityCombo[vars::WEAPONS_SelectedRarity].Rarity;

                    if (vars::WEAPONS_ManualUnlock) {
                        if (ImGui::CustomButton("__..", "Add to List")) {
                            bool _continue = true;
                            int ___ = ItemRecord::GetIndex(std::stoi(vars::WEAPONS_WeaponGalleryNumber)); // Weapon Index
                            std::string _____ = ItemRecord(___).Name(); // Weapon Name
                            auto vec = vars::WEAPONS_request;

                            for (int i = 0; i < vec.size(); i++) {
                                if (vec[i].Index == ___) {
                                    ImGui::InsertNotification({ ImGuiToastType::Error, 2000, OBF("Weapon %s already Exists!"), _____.c_str() });
                                    _continue = false;
                                }
                            }

                            if (_continue) {
                                if (_____.empty()) {
                                    ImGui::InsertNotification({ ImGuiToastType::Error, 2000, OBF("Couldn't find Gallery Number %s"), vars::WEAPONS_WeaponGalleryNumber });
                                }
                                else {
                                    vars::WEAPONS_request.push_back({ "", rarity, vars::WEAPONS_Level, ___ });
                                    ImGui::InsertNotification({ ImGuiToastType::Success, 2000, (OBF("Added ") + _____ + OBF(" (") + std::to_string(___) + OBF(") to the List!")).c_str() });
                                }
                            }
                        }

                        ImGui::SameLine(); if (ImGui::CustomButton("__wedkejnf", "Clear List")) {
                            vars::WEAPONS_request.clear();
                            ImGui::InsertNotification({ ImGuiToastType::Success, 2000, "Cleared List!" });
                        }

                        if (ImGui::CustomButton("__...", OBF("Add List")) && !vars::WEAPONS_request.empty()) {
                            std::string _;
                            auto __ = vars::WEAPONS_request;
                            if (!__.empty()) {
                                for (int i = 0; i < __.size(); i++) {
                                    _ += Functions::Account::CreateWeaponV2(__[i].Index, __[i].Level, __[i].Rarity) + ",";
                                }
                                vars::WEAPONS_request.clear();
                                _.pop_back(); QuickMenuSend(dikfnhjefb, _, OBF("Add Manual Weapons"));
                            }
                            else {
                                ImGui::InsertNotification({ ImGuiToastType::Error, 2000, OBF("List is Empty!") });
                            }
                        }
                    }
                    else {
                        if (ImGui::CustomButton("__ehjf..", OBF("Add Weapons"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddWeaponsV2(Functions::WT_BOTH, vars::WEAPONS_Level, rarity, vars::WEAPONS_StartIndex, vars::WEAPONS_EndIndex), OBF("Add Weapons"));
                    }
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos4);
                ImGui::CustomBeginChild("efefgerg", "Craft Parts", Menu::MenuChildSize); // CRAFT PARTS CHILD
                {
                    ImGui::NewLine(); ImGui::SameLine();
                    ImGui::CustomCombo<vars::CRAFT_PARTS_TypeStruct>("Craft Part Type", vars::CRAFT_PARTS_TypeCombo, &vars::CRAFT_PARTS_SelectedType, vars::CRAFT_PARTS_TypeCombo[vars::CRAFT_PARTS_SelectedType].Name, ImColor(100, 84, 138), 130.0f, 0, []() {
                        if (vars::CRAFT_PARTS_SelectedType != -1) { // always reset when the type combo is clicked/opened
                            vars::CRAFT_PARTS_StartIndex = 1;
                            vars::CRAFT_PARTS_EndIndex = 2;
                        }
                    });

                    auto parttype = vars::CRAFT_PARTS_TypeCombo[vars::CRAFT_PARTS_SelectedType].CPT;
                    bool IsNormal = (parttype == Functions::NORMAL);
                    bool IsRoyale = (parttype == Functions::ROYALE);
                    bool IsAvatarSet = (parttype == Functions::AVATAR_SET); int AvatarSetSize = (int)CraftSetIndexes.size();

                    ImGui::CustomSliderInt("nmejjfhr", "Start", &vars::CRAFT_PARTS_StartIndex, 1, IsNormal ? 1999 : IsRoyale ? 1399 : IsAvatarSet ? AvatarSetSize : 149);
                    ImGui::CustomSliderInt("efujefhe", "End", &vars::CRAFT_PARTS_EndIndex, 2, IsNormal ? 2000 : IsRoyale ? 1400 : IsAvatarSet ? AvatarSetSize + 1 : 150);
                    ImGui::CustomSliderInt("defrjgef", "Amount", &vars::CRAFT_PARTS_PartsAmount, 1, 250);

                    if (vars::CRAFT_PARTS_StartIndex >= vars::CRAFT_PARTS_EndIndex) vars::CRAFT_PARTS_StartIndex = vars::CRAFT_PARTS_EndIndex - 1;

                    if (ImGui::CustomButton("wdefef_-..", OBF("Add Parts"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddCraftPartsV2(parttype, vars::CRAFT_PARTS_PartsAmount, vars::CRAFT_PARTS_StartIndex, vars::CRAFT_PARTS_EndIndex), OBF("Add Craft Parts"));
                    ImGui::NewLine();
                }
                ImGui::EndChild();
            }


            else if (Menu::AccountSubTabs == _Subtabs[1].TabValue) { // MAIN 2 SUBTAB
                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("sidfnejfhedd", "Wears", Menu::MenuChildSize); // WEARS CHILD
                {
                    ImGui::NewLine(); ImGui::SameLine();
                    ImGui::CustomCombo<vars::WEARS_TypeStruct>("Wear Type", vars::WEARS_TypeCombo, &vars::WEARS_SelectedType, vars::WEARS_TypeCombo[vars::WEARS_SelectedType].Name, ImColor(100, 84, 138), 100.0f, 0, []() {
                        if (vars::WEARS_SelectedType != -1) { // always reset when the type combo is clicked/opened
                            vars::WEARS_StartIndex = 1;
                            vars::WEARS_EndIndex = 2;
                        }
                    });

                    auto weartype = vars::WEARS_TypeCombo[vars::WEARS_SelectedType].WT;
                    bool IsArmor = (weartype == Functions::ARMOR); int ArmorSize = (int)ArmorIndexes.size();
                    bool IsHat = (weartype == Functions::HAT);     int HatSize = (int)HatIndexes.size();
                    bool IsMask = (weartype == Functions::MASK);   int MaskSize = (int)MaskIndexes.size();
                    bool IsCape = (weartype == Functions::CAPE);   int CapeSize = (int)CapeIndexes.size();
                    bool IsBoots = (weartype == Functions::BOOTS); int BootsSize = (int)BootsIndexes.size();

                    ImGui::CustomSliderInt("kdnfgher", "Start", &vars::WEARS_StartIndex, 1, IsArmor ? ArmorSize : IsHat ? HatSize : IsMask ? MaskSize : IsCape ? CapeSize : BootsSize);
                    ImGui::CustomSliderInt("aksnfsrh", "End", &vars::WEARS_EndIndex, 2, (IsArmor ? ArmorSize : IsHat ? HatSize : IsMask ? MaskSize : IsCape ? CapeSize : BootsSize) + 1);

                    if (vars::WEARS_StartIndex >= vars::WEARS_EndIndex) vars::WEARS_StartIndex = vars::WEARS_EndIndex - 1;

                    if (IsArmor) {
                        ImGui::CustomSliderInt("ifnejffwd", "Armor Level", &vars::WEARS_ArmorLevel, 1, 65);
                    }

                    if (ImGui::CustomButton("efkjrgjfrjg", OBF("Add Wears"))) {
                        if (IsArmor) QuickMenuSend(dikfnhjefb, Functions::Account::AddArmors(vars::WEARS_ArmorLevel, vars::WEARS_StartIndex - 1, vars::WEARS_EndIndex - 1), OBF("Add Wears"));
                        else QuickMenuSend(dikfnhjefb, Functions::Account::AddWear(weartype, vars::WEARS_StartIndex - 1, vars::WEARS_EndIndex - 1), OBF("Add Wears"));
                    }
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("djkfeoken", "Wear Skins", Menu::MenuChildSize); // WEAR SKINS CHILD
                {
                    ImGui::NewLine(); ImGui::SameLine();
                    ImGui::CustomCombo<vars::WEARS_TypeStruct>("Wear Skin Type", vars::WEAR_SKINS_TypeCombo, &vars::WEAR_SKINS_SelectedType, vars::WEAR_SKINS_TypeCombo[vars::WEAR_SKINS_SelectedType].Name, ImColor(100, 84, 138), 130.0f, 0, []() {
                        if (vars::WEAR_SKINS_SelectedType != -1) { // always reset when the type combo is clicked/opened
                            vars::WEAR_SKINS_StartIndex = 1;
                            vars::WEAR_SKINS_EndIndex = 2;
                        }
                        });

                    auto weartype = vars::WEAR_SKINS_TypeCombo[vars::WEAR_SKINS_SelectedType].WT;
                    bool IsArmor = (weartype == Functions::ARMOR);

                    ImGui::CustomSliderInt("nmejjfhr", "Start", &vars::WEAR_SKINS_StartIndex, 1, IsArmor ? 99 : 299);
                    ImGui::CustomSliderInt("efujefhe", "End", &vars::WEAR_SKINS_EndIndex, 2, IsArmor ? 100 : 300);

                    if (vars::WEAR_SKINS_StartIndex >= vars::WEAR_SKINS_EndIndex) vars::WEAR_SKINS_StartIndex = vars::WEAR_SKINS_EndIndex - 1;

                    if (ImGui::CustomButton("jkvbefzhe", OBF("Add Wear Skins"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddWearSkinsV2(weartype, vars::WEAR_SKINS_StartIndex, vars::WEAR_SKINS_EndIndex), OBF("Add Wear Skins"));
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos3);
                ImGui::CustomBeginChild("efkedmejf", "Gadgets", Menu::MenuChildSize); // GADGETS CHILD
                {
                    int niggerdivian = (int)GadgetIndexes.size();
                    ImGui::CustomSliderInt("fkwsmfjr", "Start", &vars::GADGETS_StartIndex, 1, niggerdivian);
                    ImGui::CustomSliderInt("sdjcnmsj", "End", &vars::GADGETS_EndIndex, 2, niggerdivian + 1);
                    ImGui::CustomSliderInt("ekerfndw", "Level", &vars::GADGETS_Level, 1, 65);

                    if (vars::GADGETS_StartIndex >= vars::GADGETS_EndIndex) vars::GADGETS_StartIndex = vars::GADGETS_EndIndex - 1;

                    if (ImGui::CustomButton("ovjnezhbfr", OBF("Add Gadgets"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddGadgets(vars::GADGETS_Level, vars::GADGETS_StartIndex - 1, vars::GADGETS_EndIndex - 1), OBF("Add Gadgets"));
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos4);
                ImGui::CustomBeginChild("eijfwefhjrb", "Pets", Menu::MenuChildSize); // PETS CHILD
                {
                    int niggerdivian = (int)PetIndexes.size();
                    ImGui::CustomSliderInt("weoifjer", "Start", &vars::PETS_StartIndex, 1, niggerdivian);
                    ImGui::CustomSliderInt("wsjdwedh", "End", &vars::PETS_EndIndex, 2, niggerdivian + 1);
                    ImGui::CustomSliderInt("weikdnhb", "Parts", &vars::PETS_Parts, 100, 999);

                    if (vars::PETS_StartIndex >= vars::PETS_EndIndex) vars::PETS_StartIndex = vars::PETS_EndIndex - 1;

                    if (ImGui::CustomButton("wdowjd", OBF("Add Pets"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddPets(vars::PETS_StartIndex - 1, vars::PETS_EndIndex - 1), OBF("Add Pets"));
                    ImGui::SameLine(); if (ImGui::CustomButton("edkwfwdh", OBF("Add Pet Parts"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddPetParts(vars::PETS_Parts, vars::PETS_StartIndex - 1, vars::PETS_EndIndex - 1), OBF("Add Pet Parts"));

                    ImGui::NewLine();
                    ImGui::CustomSliderInt("fefesfsf", OBF("Level"), &vars::PETS_Level, 1, 65);
                    if (ImGui::CustomButton("ienfhef", OBF("Set Pets Level"))) QuickMenuSend(dikfnhjefb, Functions::Account::UpgradePets(vars::PETS_Level, vars::PETS_StartIndex - 1, vars::PETS_EndIndex - 1), OBF("Set Pets Level"));
                    ImGui::NewLine();
                }
                ImGui::EndChild();
            }


            else if (Menu::AccountSubTabs == _Subtabs[2].TabValue) { // ROYALE SUBTAB
                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("wjkdnerhfhe", OBF("Royale Adder"), Menu::MenuChildSize); // MAIN ROYALE CHILD
                {
                    ImGui::NewLine(); ImGui::SameLine();
                    ImGui::CustomCombo<vars::ROYALE_ADDER_TypeStruct>("Royale Type", vars::ROYALE_ADDER_TypeCombo, &vars::ROYALE_ADDER_SelectedType, vars::ROYALE_ADDER_TypeCombo[vars::ROYALE_ADDER_SelectedType].Name, ImColor(100, 84, 138), 100.0f, 0, []() {
                        if (vars::ROYALE_ADDER_SelectedType != -1) { // always reset when the type combo is clicked/opened
                            vars::ROYALE_ADDER_StartIndex = 1;
                            vars::ROYALE_ADDER_EndIndex = 2;
                        }
                        });
                    auto royaletype = vars::ROYALE_ADDER_TypeCombo[vars::ROYALE_ADDER_SelectedType].RT;
                    bool IsAvatars = (royaletype == Functions::AVATAR); int AvatarSize = (int)AvatarIndexes.size();
                    bool IsGlider = (royaletype == Functions::GLIDER);  int GliderSize = (int)GliderIndexes.size();
                    bool IsShovel = (royaletype == Functions::SHOVEL);  int ShovelSize = (int)ShovelIndexes.size();
                    bool IsTrail = (royaletype == Functions::TRAIL);    int TrailSize = (int)ShovelIndexes.size();
                    bool IsCar = (royaletype == Functions::CAR);        int CarSize = (int)CarIndexes.size();

                    ImGui::CustomSliderInt("ewferfge", "Start", &vars::ROYALE_ADDER_StartIndex, 1, IsAvatars ? AvatarSize : IsGlider ? GliderSize : IsShovel ? ShovelSize : IsTrail ? TrailSize : CarSize);
                    ImGui::CustomSliderInt("awkdseah", "End", &vars::ROYALE_ADDER_EndIndex, 2, (IsAvatars ? AvatarSize : IsGlider ? GliderSize : IsShovel ? ShovelSize : IsTrail ? TrailSize : CarSize) + 1);

                    if (vars::ROYALE_ADDER_StartIndex >= vars::ROYALE_ADDER_EndIndex) vars::ROYALE_ADDER_StartIndex = vars::ROYALE_ADDER_EndIndex - 1;

                    if (ImGui::CustomButton("efkjrgjfrjg", OBF("Add Royale"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddRoyale(royaletype, vars::ROYALE_ADDER_StartIndex - 1, vars::ROYALE_ADDER_EndIndex - 1), OBF("Add Royale"));
                    if (IsGlider || IsCar) {
                        ImGui::SameLine();
                        if (ImGui::CustomButton("wegfkrnfjrgb", OBF("Upgrade Royale"))) QuickMenuSend(dikfnhjefb, Functions::Account::UpgradeRoyale(royaletype, vars::ROYALE_ADDER_StartIndex - 1, vars::ROYALE_ADDER_EndIndex - 1), OBF("Upgrade Royale"));
                    }
                }
                ImGui::EndChild();
            }


            else if (Menu::AccountSubTabs == _Subtabs[3].TabValue) { // MAX ACC SUBTAB
                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("wdefrgkdssdw", OBF("Quick Account Maxing 1"), ImVec2(274, 400));
                {
                    ImGui::HoverItemText("ONLY FOR THIS TAB!\n\nTurned On = Everything that needs a lvl to be added (e.g.: Armors) will be added with Lvl 65\nTurned Off = Everything will be added with your Player Level", "\t\t\t\t\t\t\t\t\t(?)");
                    ImGui::AddCursorPos(ImVec2(0, -20.6)); ImGui::Checkbox(OBF("Auto Lvl 65"), &vars::AutoLvl65);

                    if (ImGui::CustomButton("segsegseg", OBF("Add Weapons"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddWeaponsV2(Functions::WT_BOTH, vars::PlayerLVL), OBF("Add All Weapons"));

                    ImGui::SameLine();
                    if (ImGui::CustomButton("afsefddsg", OBF("Add Modules"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddModules(), OBF("Add All Modules"));

                    if (ImGui::CustomButton("awfrjsefd", OBF("Add Parts"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddCraftPartsV2(), OBF("Add All Craft Parts"));

                    ImGui::SameLine();
                    if (ImGui::CustomButton("efiejfgzr", OBF("Upgrade Modules"))) QuickMenuSend(dikfnhjefb, Functions::Account::UpgradeModules(), OBF("Max Upgrade All Modules"));

                    if (ImGui::CustomButton("efrefwede", OBF("Add Wears"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddAllWears(vars::CheckAutoMaxLvl()), OBF("Add All Wears"));

                    ImGui::SameLine();
                    if (ImGui::CustomButton("jdfbnehfve", OBF("Add Wear Skins"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddWearSkinsV2() + "," + Functions::Account::AddWearSkinsV2(Functions::ARMOR, 1, 100), OBF("Add All Wear Skins"));

                    if (ImGui::CustomButton("sefsefsed", OBF("Add Gadgets"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddGadgets(vars::CheckAutoMaxLvl()), OBF("Add All Gadgets"));

                    ImGui::SameLine();
                    if (ImGui::CustomButton("awkdjefzhb", OBF("Add Lobby Items"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddLobbyItems(), OBF("Add All Lobby Items"));

                    if (ImGui::CustomButton("segewfsgx", OBF("Add Weapon Skins"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddWeaponSkinsV2(), OBF("Add All Weapon Skins"));

                    ImGui::SameLine();
                    if (ImGui::CustomButton("edkfenjfberf", OBF("Max Pixel Pass"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddPixelPass() + "," + Functions::Account::AddPixelPassXP(30000), OBF("Max Pixel Pass"));

                    if (ImGui::CustomButton("awfrawfaw", OBF("Add Graffitis"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddGraffitisV2(), OBF("Add All Graffitis"));
                    if (ImGui::CustomButton("sefgsgseg", OBF("Add Royale"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddAllRoyale(), OBF("Add All Royale"));
                    if (ImGui::CustomButton("efsegseex", OBF("Upgrade Royale"))) QuickMenuSend(dikfnhjefb, Functions::Account::UpgradeAllRoyale(), OBF("Max Upgrade All Royale"));
                    if (ImGui::CustomButton("afsefgesg", OBF("Add Pets"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddPets(), OBF("Add All Pets"));
                    if (ImGui::CustomButton("efjdjnfzh", OBF("Upgrade Pets"))) QuickMenuSend(dikfnhjefb, Functions::Account::UpgradePets(vars::CheckAutoMaxLvl()), OBF("Upgrade All Pets"));
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("efjkrndfghjrtbg", OBF("Quick Account Maxing 2"), ImVec2(268, 400));
                {
                    if (ImGui::CustomButton("ewdejfbne", OBF("Complete Tutorial"))) QuickMenuSend(dikfnhjefb, Functions::Account::CompleteBeginnerTutorial(), OBF("Complete Beginner Tutorial"));
                    if (ImGui::CustomButton("wkjdfjfef", OBF("Add All DLC Sets"))) Functions::Menu::Account__AddDlcSets();
                    if (ImGui::CustomButton("wdegeregf", OBF("Max Account"))) Functions::Menu::Account__MaxAccount();

                    ImGui::NewLine(); ImGui::CustomSliderInt("eifnefdwed", "Level", &vars::MAX_ACC_LVL, 1, 65);
                    if (ImGui::CustomButton("wdmwfkejfefjn", OBF("Set Level"))) QuickMenuSend(dikfnhjefb, Functions::Account::SetPlayerLvl(vars::MAX_ACC_LVL), OBF("Set Player LVL"), true, true, [&](ojson Request, ojson Packet) {
                        vars::SecureLvl = true;
                    });
                }
                ImGui::EndChild();
            }

            ImGui::PopFont();
        }


        else if (Menu::MainTabValue == _MenuTabs[1].TabValue) // STATS TAB
        {
            int _TabValue = _MenuTabs[1].TabValue;
            auto _Subtabs = _MenuTabs[_TabValue].Subtabs;
            ImGui::PushFont(ImGui::Fonts::MuseoSansMain);
            DrawSubTabs(_TabValue, &Menu::StatsSubTabs, "_s_");

            if (Menu::StatsSubTabs == _Subtabs[0].TabValue) { // MAIN SUBTAB

                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("lmfjgnhrg__", OBF("Monthly"), Menu::MenuChildSize); // MONTHLY CHILD
                {
                    ImGui::NewLine(); ImGui::SameLine();
                    ImGui::CustomCombo<vars::MONTHLY_TypeStruct>("Stat Type", vars::MONTHLY_TypeCombo, &vars::MONTHLY_SelectedType, vars::MONTHLY_TypeCombo[vars::MONTHLY_SelectedType].Name);
                    ImGui::NewLine(); ImGui::SameLine(); ImGui::CustomInputText("wdfkefgnrhug", (std::string(vars::MONTHLY_TypeCombo[vars::MONTHLY_SelectedType].UpdateValueName) + " Value").c_str(), vars::MONTHLY_UpdateAmount, std::size(vars::MONTHLY_UpdateAmount));
                    if (ImGui::CustomButton("kweneikf_nerjfg", "Update Stats")) {
                        std::string _okay_ = std::string(vars::MONTHLY_UpdateAmount);
                        switch (vars::MONTHLY_TypeCombo[vars::MONTHLY_SelectedType].StatType) {
                        case vars::KILLS:
                            QuickMenuSend(dikfnhjefb, Functions::Account::AddMonthlyStats(std::stoi(_okay_), 0, 0), OBF("Add Player Kills"));
                            break;
                        case vars::DEATHS:
                            if (_okay_[0] == '-') _okay_.erase(0, 1);
                            else _okay_ = "-" + _okay_;
                            QuickMenuSend(dikfnhjefb, Functions::Account::AddMonthlyStats(0, 0, 0, true, std::stoi(_okay_)), OBF("Add Player Killrate"));
                            break;
                        case vars::HEADSHOTS:
                            QuickMenuSend(dikfnhjefb, Functions::Account::AddMonthlyStats(0, std::stoi(_okay_), 0), OBF("Add Player Headshots"));
                            break;
                        case vars::ACCURACY:
                            QuickMenuSend(dikfnhjefb, Functions::Account::AddMonthlyStats(0, 0, std::stoi(_okay_)), OBF("Add Player Accuracy"));
                            break;
                        case vars::KILLSTREAK:
                            QuickMenuSend(dikfnhjefb, Functions::Account::SetMonthlyStats(std::stoi(_okay_), 0, 0), OBF("Set Player Winstreak"));
                            break;
                        case vars::WINSTREAK:
                            QuickMenuSend(dikfnhjefb, Functions::Account::SetMonthlyStats(0, std::stoi(_okay_), 0), OBF("Set Player Winstreak"));
                            break;
                        case vars::WINS:
                            QuickMenuSend(dikfnhjefb, Functions::Account::AddMatches(std::stoi(_okay_), true), OBF("Add Player Wins"));
                            break;
                        case vars::MATCHES:
                            QuickMenuSend(dikfnhjefb, Functions::Account::AddMatches(std::stoi(_okay_)), OBF("Add Player Matches"));
                            break;
                        }
                    }
                }
                ImGui::EndChild();



                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("efrferdsergesrg", OBF("Modes"), Menu::MenuChildSize); // MODES CHILD
                {
                    ImGui::NewLine(); ImGui::SameLine();
                    ImGui::CustomCombo<vars::MODES_TypeStruct>("Mode Type", vars::MODES_TypeCombo, &vars::MODES_SelectedType, vars::MODES_TypeCombo[vars::MODES_SelectedType].Name);
                    ImGui::NewLine(); ImGui::SameLine(); ImGui::CustomInputText("ormgirnfgmr", "Add Amount", vars::MODES_AddAmount, std::size(vars::MODES_AddAmount));
                    try {
                        if (std::stoi(std::string(vars::MODES_AddAmount)) > 500) strcpy_s(vars::MODES_AddAmount, "500");
                    }
                    catch (std::invalid_argument err) {
                        // do nothing my nigga
                    }

                    if (ImGui::CustomButton("edujdfbefh", OBF("Add Stats"))) {
                        int modetype = vars::MODES_TypeCombo[vars::MODES_SelectedType].ModeIndex;
                        vars::AlwaysUpdateSlotsWhenRequestSent = false;
                        vars::SendRequest = true;
                        const char* ekdnmwejfbnf = OBF("update_player");
                        std::string _soefjneifrgief = OBF("Add Mode Stats: ") + std::string(vars::MODES_TypeCombo[vars::MODES_SelectedType].Name);
                        int igjriujfjeigf = std::stoi(std::string(vars::MODES_AddAmount)); // int add amount
                        if (igjriujfjeigf > 1) {
                            for (int i = 0; i < igjriujfjeigf - 1; i++) {
                                WS::Utils::AddRequest(ekdnmwejfbnf, Functions::Account::AddModeStat(modetype), 1, false, false);
                            }
                        }
                        WS::Utils::AddRequest(ekdnmwejfbnf, Functions::Account::AddModeStat(modetype), 1, false, vars::ReloadWhenReceived, true, _soefjneifrgief.c_str(), ImGuiToastType::Info, false, [](ojson _r, ojson _p) { vars::AlwaysUpdateSlotsWhenRequestSent = true; });
                        WS::Utils::NotifyRequestSent(_soefjneifrgief.c_str());

                    }
                    ImGui::NewLine();
                }
                ImGui::EndChild();

            }

            ImGui::PopFont();
        }


        else if (Menu::MainTabValue == _MenuTabs[2].TabValue) // OTHER TAB
        {
            int _TabValue = _MenuTabs[2].TabValue;
            auto _Subtabs = _MenuTabs[_TabValue].Subtabs;
            ImGui::PushFont(ImGui::Fonts::MuseoSansMain);
            DrawSubTabs(_TabValue, &Menu::OtherSubTabs, "oooo_");

            if (Menu::OtherSubTabs == _Subtabs[0].TabValue) { // GAME SUBTAB

                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("mekdfnmeujfnrg", OBF("Offers"), Menu::MenuChildSize); // OFFFERS CHILD
                {
                    int niggerdivian = (int)OfferIndexes.size();
                    ImGui::CustomSliderInt("wefkendfjenfe", "Start", &vars::OFFERS_StartIndex, 1, niggerdivian);
                    ImGui::CustomSliderInt("edjikfnejfned", "End", &vars::OFFERS_EndIndex, 2, niggerdivian + 1);

                    if (vars::OFFERS_StartIndex >= vars::OFFERS_EndIndex) vars::OFFERS_StartIndex = vars::OFFERS_EndIndex - 1;

                    if (ImGui::CustomButton("efoefjerif", OBF("Add Offers"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddOffers(vars::OFFERS_StartIndex - 1, vars::OFFERS_EndIndex - 1), OBF("Add Offers"));
                    ImGui::SameLine(); if (ImGui::CustomButton("eekndfeferh", OBF("Remove Offers"))) QuickMenuSend(dikfnhjefb, Functions::Account::AddOffers(vars::OFFERS_StartIndex - 1, vars::OFFERS_EndIndex - 1, 1732126736), OBF("Remove Offers"));
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("rdfeferfgerg", OBF("Paid Offers"), Menu::MenuChildSize); // PAID OFFERS CHILD
                {
                    ImGui::SameLine(); ImGui::Text(OBF("NOTE: Disable Steam Overlay \n and Reload Game to take Effect")); ImGui::NewLines(2);
                    ImGui::SameLine(); ImGui::CustomInputText("erfmgrjkgfg", OBF("Paid Offers Prices"), vars::OFFERS_PaidOffersPrices, std::size(vars::OFFERS_PaidOffersPrices));
                    ImGui::Checkbox(OBF("Set Paid Offers Prices"), &vars::OFFERS_SetPaidOffersPrices);

                    ImGui::Checkbox(OBF("Free Paid Offers"), &vars::OFFERS_FreePaidOffers);
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos3);
                ImGui::CustomBeginChild("wefkenfujnef", OBF("Currency"), Menu::MenuChildSize); // CURRENCY CHILD
                {
                    ImGui::SameLine();
                    ImGui::CustomCombo<vars::CURRENCY_TypeStruct>("Currency Type", vars::CURRENCY_TypeCombo, &vars::CURRENCY_SelectedType, vars::CURRENCY_TypeCombo[vars::CURRENCY_SelectedType].Name);
                    ImGui::NewLine(); ImGui::SameLine(); ImGui::CustomInputText("wefejknfejfnherf", "Amount", vars::CURRENCY_AddAmount, std::size(vars::CURRENCY_AddAmount));

                    if (ImGui::CustomButton("fkmefnejfef", OBF("Add Currency"))) {
                        try {
                            int CurAmount = std::stoi(std::string(vars::CURRENCY_AddAmount));
                            QuickMenuSend(dikfnhjefb, Functions::Account::UpdateCurrency(Functions::ADD_CURRENCY, vars::CURRENCY_TypeCombo[vars::CURRENCY_SelectedType].Index, CurAmount), OBF("Add Currency"));
                        }
                        catch (std::invalid_argument err) {
                            ImGui::InsertNotification({ ImGuiToastType::Error, 2000, OBF("Make sure the Input is a number value!") });
                        }
                    }
                    ImGui::NewLine();
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos4);
                ImGui::CustomBeginChild("efkefjenfehf", OBF("Item Currency"), Menu::MenuChildSize); // ITEM CURRENCY CHILD
                {
                    ImGui::SameLine(); ImGui::Text("Next Update...");
                }
                ImGui::EndChild();

            }

            if (Menu::OtherSubTabs == _Subtabs[1].TabValue) { // MISC SUBTAB

                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("kjnfkejmgjn", OBF("Miscellaneous"), Menu::MenuHalfChildSize1); // Miscellaneous CHILD
                {
                    if (ImGui::CustomButton("jeoikfeitfjr", OBF("Veteran Badge"))) {
                        vars::AlwaysUpdateSlotsWhenRequestSent = false;
                        const char* NotifyName = OBF("Add Veteran Badge");
                        vars::SendRequest = WS::Utils::AddRequest(dikfnhjefb, Functions::Account::InventoryAddItemSingle(700015), 1, false, vars::ReloadWhenReceived, true, NotifyName, ImGuiToastType::Info, false, [](ojson _r, ojson _p) { vars::AlwaysUpdateSlotsWhenRequestSent = true; });
                        WS::Utils::NotifyRequestSent(NotifyName);
                    }
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("edfefxrhgrgr", OBF("Fun"), Menu::MenuHalfChildSize1); // Miscanellous CHILD
                {
                    ImGui::Checkbox(OBF("Disable Analytics"), &vars::FUN__DisableAnalytics);

                    ImGui::NewLines(2);
                    ImGui::SameLine();

                    ImGui::CustomInputText("ewsjjndiekdf", OBF("Target ID"), vars::FUN_TargetID, std::size(vars::FUN_TargetID));
                    
                    ImGui::NewLines(2);
                    ImGui::SameLine();
                    ImGui::Text(OBF("CRASH PLAYER: TARGET MUST BE ON PC"));
                    if (ImGui::CustomButton("iejdikwef", OBF("Try Crash"))) Functions::Menu::Misc__SendGift(1000, vars::FUN_TargetID);
                    if (ImGui::CustomButton("ekdkwofer", OBF("Try Get Info"))) {
                        vars::GetPlayerInfo = true;
                        vars::AlwaysUpdateSlotsWhenRequestSent = false;
                        ojson req = { {OBF("player_id"), vars::FUN_TargetID} };
                        const char* NotifyName = OBF("Get Target Info");
                        vars::SendRequest = WS::Utils::AddRequest(OBF("get_progress"), req.dump(), 1, false, false, true, NotifyName, ImGuiToastType::Info, false, [](ojson _r, ojson _p) {
                            vars::AlwaysUpdateSlotsWhenRequestSent = true;
                            ImGui::InsertNotification({ ImGuiToastType::Success, 2000, OBF("Check the console!") });
                        });
                        WS::Utils::NotifyRequestSent(NotifyName);
                    }
                }
                ImGui::EndChild();

            }

            if (Menu::OtherSubTabs == _Subtabs[2].TabValue) { // AUTH SUBTAB

                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("klfngrkgnjrgn", OBF("Token Info (TEMPORARY)"), Menu::MenuChildSize); // TOKEN CHILD
                {
                    if (ImGui::CustomButton("dfpw�f", OBF("Output Token"))) {
                        fslog::info(OBF("YOUR PLAYER TOKEN\n{}\n\n"), PlayerData::gT(PlayerData::I())->ToString());
                        ImGui::InsertNotification({ ImGuiToastType::Success, 2000, OBF("Check the console!") });
                    };

                    ImGui::NewLines(2); ImGui::SameLine();
                    ImGui::CustomInputText("eewfrefgseg", OBF("Target Token"), vars::AUTH_PlayerToken, std::size(vars::AUTH_PlayerToken));
                    if (ImGui::CustomButton("jksejdowfujw", OBF("Login"))) {
                        vars::CallInUnityThread.push_back([](){
                            ZIDFJEFKEFIEFGE();
                        });
                        vars::AUTH_LoginWithToken = true;
                    }
                }
                ImGui::EndChild();
                

                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("ujdbfjekgnhj", OBF("Auth Info"), Menu::MenuChildSize); // AUTH SECRET CHILD
                {
                    if (ImGui::CustomButton("dfdfegpw�f", OBF("Output Auth Info"))) {
                        fslog::info(OBF("AUTH INFO\nID: {}\nSecret: {}\n\n"), iwsdmwoifmefgujerf()->ToString(), PlayerData::gAS(PlayerData::I())->ToString());
                        ImGui::InsertNotification({ ImGuiToastType::Success, 2000, OBF("Check the console!") });
                    };

                    ImGui::NewLines(2); ImGui::SameLine();
                    ImGui::CustomInputText("efegrtherfe", OBF("Target ID"), vars::AUTH_PlayerID, std::size(vars::AUTH_PlayerID));

                    ImGui::NewLine(); ImGui::SameLine(); 
                    ImGui::CustomInputText("edfwfdrhgef", OBF("Target Secret"), vars::AUTH_PlayerSecret, std::size(vars::AUTH_PlayerSecret));

                    if (ImGui::CustomButton("njedfiwjduwe", OBF("Login"))) {
                        ImGui::InsertNotification({ ImGuiToastType::Info, 2000, OBF("Trying to Login...") });
                        vars::CallInUnityThread.push_back([]() {
                            WIDFJEFKEFIEFGE(vars::AUTH_PlayerID, vars::AUTH_PlayerSecret);
                            ZIDFJEFKEFIEFGE();
                            ImGui::InsertNotification({ ImGuiToastType::Success, 2000, OBF("Logging attempt done!") });
                        });
                    }
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos3);
                ImGui::CustomBeginChild("eswsjhbdwejfb", OBF("Account Generator"), Menu::MenuChildSize); // ACCOUNT GENERATOR CHILD
                {
                    ImGui::SameLine();
                    ImGui::Text(OBF("NOTE: You can login to generated PG3D\nAccounts just by ID (no Secret required)"));

                    ImGui::NewLine();
                    ImGui::CustomSliderInt("eoifjwiodefg", OBF("Generate Amount"), &vars::AUTH_GenerateAccountsAmount, 1, 10);
                    if (ImGui::CustomButton("kernmkoemgf", OBF("Generate"))) {
                        const char* niggerliciousEventName = OBF("create_character");
                        const char* NotifyName = OBF("Generate Account(s)");
                        vars::AlwaysUpdateSlotsWhenRequestSent = false;
                        vars::SendRequest = WS::Utils::AddRequest(OBF("unlock_character"), OBF(R"({"count":9999})"), 1, false, false, false, "", ImGuiToastType::Info, false, [niggerliciousEventName, NotifyName](ojson _r, ojson _p) {
                            vars::SendRequest = WS::Utils::AddRequest(niggerliciousEventName, OBF("{}"), vars::AUTH_GenerateAccountsAmount - 1, false, false);
                            vars::SendRequest = WS::Utils::AddRequest(niggerliciousEventName, OBF("{}"), 1, false, false, true, NotifyName, ImGuiToastType::Info, false, [](ojson _r, ojson _p) {
                                vars::AlwaysUpdateSlotsWhenRequestSent = true;
                            });
                        });
                        WS::Utils::NotifyRequestSent(NotifyName);
                    }

                    if (ImGui::CustomButton("wedwfegsef", OBF("Output Infos"))) {
                        const char* ierjfief = OBF("Output Generated Accounts");
                        vars::AlwaysUpdateSlotsWhenRequestSent = false;
                        vars::SendRequest = WS::Utils::AddRequest(OBF("get_binded_ids"), OBF(R"({"with_info":1})"), 1, false, false, true, ierjfief, ImGuiToastType::Info, false, [](ojson _r, ojson _p) {
                            vars::AlwaysUpdateSlotsWhenRequestSent = true;
                            ojson Accounts = _p[1][OBF("user_characters")][OBF("ids")];
                            fslog::info(OBF("Total Created Accounts Count: {}\n\n"), (int)Accounts.size());
                            for (int i = 0; i < Accounts.size(); i++) {
                                ojson Account = Accounts[i];
                                printf(OBF("ID: %s\nAuth-Secret: %s\n\n"), std::string(Account[OBF("id")]).c_str(), std::string(Account[OBF("hash")]).c_str());
                            }
                        });
                        WS::Utils::NotifyRequestSent(ierjfief);
                    }
                }
                ImGui::EndChild();

            }

            ImGui::PopFont();
            }


        else if (Menu::MainTabValue == _MenuTabs[3].TabValue) // SETTINGS TAB
        {
            int _TabValue = _MenuTabs[3].TabValue;
            auto _Subtabs = _MenuTabs[_TabValue].Subtabs;
            ImGui::PushFont(ImGui::Fonts::MuseoSansMain);
            DrawSubTabs(_TabValue, &Menu::SettingsSubTabs, "s");

            if (Menu::SettingsSubTabs == _Subtabs[0].TabValue) { // MAIN SUBTAB

                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("wdwdfefe", OBF("Misc"), Menu::MenuChildSize); // MISC CHILD
                {
                    if (ImGui::CustomButton("_wfwejbefjenfjenfhjef.", OBF("Dump Game"))) {
                        std::string _ = OBF("dump-");
                        _ += efergegeg()->ToString().c_str();
                        _ += OBF("_VoidPG.cs");
                        Il2CppDumper::Dump(_.c_str());
                    }
                    ImGui::SameLine(); if (ImGui::CustomButton("_.wsfedg.", OBF("Dump OITs"))) {
                        FILE* file;
                        fopen_s(&file, "OfferItemTypeDump.json", "w+");
                        std::ofstream out(file);

                        auto dictI = *(Unity::il2cppDictionary<int, Unity::il2cppArray<int>*>**)((uint64_t)wdfjnefjefj() + 0x10);
                        auto dictS = *(Unity::il2cppDictionary<int, Unity::il2cppArray<monoString*>*>**)((uint64_t)wdfjnefjefj() + 0x18);

                        json dictIndex = json::parse(Json::Encode((BNM::Object*)dictI)->ToString());
                        json dictStr = json::parse(Json::Encode((BNM::Object*)dictS)->ToString());

                        out << "{\n";
                        for (auto const& entry : OfferItemType_dict) {
                            out << "\t\"" << entry.first << "\": {\n";
                            for (int i = 0; i < dictIndex[entry.first].size(); i++) {
                                out << "\t\t\"" << dictIndex[entry.first][i] << "\": " << dictStr[entry.first][i];
                                if (i < dictIndex[entry.first].size() - 1) {
                                    out << ",";
                                }
                                out << "\n";
                            }
                            out << "\t}";
                            if (entry.first != OfferItemType_dict.rbegin()->first) {
                                out << ",";
                            }
                            out << "\n\n";
                        }
                        out << "}";

                        fclose(file);
                    }

                    if (ImGui::CustomButton("_...", OBF("Close Game"))) Backend::UnloadImGui();

                    ImGui::NewLine(); ImGui::SliderFloat(OBF("Game Speed"), &vars::GameSpeed, 0, 100, "%fx");
                    if (ImGui::CustomButton("jerferf", OBF("Reset"))) vars::GameSpeed = 1.0f;
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("edwdef", OBF("Websocket"), Menu::MenuChildSize); // WEBSOCKET CHILD
                {
                    if (ImGui::CustomButton("wdefefge", OBF("Reload Game"))) WS::Utils::ReloadGame();
                    ImGui::Checkbox(OBF("Reload when Requests are being Received"), &vars::ReloadWhenReceived);
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos3);
                ImGui::CustomBeginChild("wdwefrefj", OBF("Player Info"), Menu::MenuChildSize); // PLAYER INFO CHILD
                {
                    if (ImGui::CustomButton("dofjiefnhbre", OBF("Logout"))) {
                        vars::UserData.Delete();
                        Backend::UnloadImGui();
                    }

                    if (ImGui::CustomButton("erkfmerikfjerufj", OBF("Update Slots"))) WS::Slots::INIT(false, OBF("Update Slots"));
                }
                ImGui::EndChild();


                ImGui::SetCursorPos(Menu::MenuChildPos4); // INFO CHILD
                ImGui::CustomBeginChild("wdwfefg", "Info", Menu::MenuChildSize); // PLAYER INFO CHILD
                {
                    if (ImGui::CustomButton("jgnujefgr", "Discord Server 1")) system("start https://discord.gg/q6bau7nrbW");
                    ImGui::SameLine(); if (ImGui::CustomButton("edwdefeew", "Discord Server 2")) system("start https://discord.gg/voidpg");

                    ImGui::NewLines(2); ImGui::SameLine(); ImGui::Text("CREDITS:\n\nSxitxma: Menu, Improved Auth\nLeminare: Bought Auth and Menu UI\nYeetDisDude: Auth\nDc$: Menu UI");
                }
                ImGui::EndChild();
            }


            else if (Menu::SettingsSubTabs == _Subtabs[1].TabValue) { // MENU SUBTAB
                ImGui::SetCursorPos(Menu::MenuChildPos1);
                ImGui::CustomBeginChild("sjfrkgrtg", "Menu Background", Menu::MenuChildSize);
                {
                    ImGui::SliderFloat("Glow Thickness", &Menu::MenuBGFrameThickness, 100, 500);
                    ImGui::NewLine(); ImGui::SameLine(); ImGui::ColorEdit3("Glow Color", Menu::MenuBGFGlowColor);
                    if (ImGui::CustomButton("emdfkef", "Reset All")) {
                        Menu::MenuBGFrameThickness = 200;
                        Menu::MenuBGFGlowColor[0] = Menu::MenuBGFGlowColor[1] = 223.f;
                        Menu::MenuBGFGlowColor[2] = 238.f;
                        Menu::MenuBGFGlowColor[3] = 0.75f;
                    }

                    ImGui::NewLine();
                    ImGui::Checkbox("Black Screen", &Menu::BlackBackground);
                }
                ImGui::EndChild();

                ImGui::SetCursorPos(Menu::MenuChildPos2);
                ImGui::CustomBeginChild("dkfmrkgrtg", "Menu Widgets", Menu::MenuChildSize);
                {
                    ImGui::SliderFloat("Buttons Size", &ImGui::_ButtonSize, 50, 150);
                    ImGui::SliderFloat("Buttons Width", &ImGui::_ButtonWidth, 10, 40);
                    ImGui::SameLine(); ImGui::AddCursorPos(ImVec2(-7, 0)); if (ImGui::CustomButton("efewfrg", "Reset All")) {
                        ImGui::_ButtonSize = 106.5;
                        ImGui::_ButtonWidth = 28;
                    }
                }
                ImGui::EndChild();
            }

            ImGui::PopFont();
        }

    }
    ImGui::End();
}