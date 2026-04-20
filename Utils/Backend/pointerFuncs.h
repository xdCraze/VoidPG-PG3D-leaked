#include "classFinder.h"
#include "Headers/FNPointer.h"

enum OfferItemType {
	None = 0,
	Weapon = 10,
	Armor = 20,
	Mask = 30,
	Hat = 40,
	Boots = 50,
	Cape = 60,
	Skin = 65,
	Gadget = 70,
	Pet = 80,
	Egg = 83,
	LobbyItem = 85,
	FortItem = 90,
	Gems = 1000,
	Coins = 1010,
	Leprechaun = 1020,
	WeaponUpgrade = 1030,
	GachaFreeSpin = 1040,
	EventCurrency = 1050,
	VIP = 1060,
	Parts = 1070,
	Royale = 1080,
	BattlePassLevel = 1090,
	BattlePassExp = 1100,
	BattlePassCurrency = 1110,
	GoldenSkin = 1120,
	EventChest = 1130,
	CraftCurrency = 1140,
	Module = 1150,
	ModulePoint = 1155,
	ModuleChest = 1160,
	WeaponSkin1 = 1170,
	ClanCurrency = 1180,
	Coupons = 1190,
	Currency = 1200,
	Character = 1210,
	ClanShields = 1220,
	ClanLootBox = 1230,
	ClanPlaceable = 1240,
	ClanPlaceablePoint = 1250,
	Detail = 1300,
	WeaponLevelUpgrade = 1310,
	PlayerBuff = 1320,
	ClanBuff = 1330,
	WeaponQualityUpgrade = 1340,
	ArmorSkin = 1350,
	ClanBuilding = 1360,
	ClanBuildingPoint = 1370,
	FreeUpgrade = 1380,
	Chest = 1390,
	Exp = 1400,
	Stats = 1410,
	ModeSlots = 1420,
	Executable = 1430,
	Tank = 1440,
	VIP20 = 1450,
	LootBox = 1460,
	Graffiti = 1470,
	PixelPassExp = 1490,
	ClanRankExperience = 1500,
	WearSkin = 1510,
	Applicable = 1520,
	CraftSet = 1530,
	FeatureExp = 1540,
	PackagedItem = 1550,
	Achievement = 1560,
	ExpirySimple = 1570,
	Static = 1580,
	GemsHarvester = 1590,
	TreasureMap = 1600,
};

enum CategoryNames {
	GlidersRoyaleCategory = 160000,
	ShovelsRoyaleCategory = 170000,
	HatsRoyaleCategory = 180000,
	RoyaleAvatarsCategory = 190000,
	TrailRoyaleCategory = 200000,
	TransportRoyaleCategory = 210000
};

// Credits: Soto sapi (or whoever he skidded it from)
struct sjkdnwskjdmeghefef { // AnalyticsParams
	int enum1;
	int enum2;
	int enum3;
	int enum4;
	int enum5;
	int enum6;
	int enum7;
	bool boolean1;
	void* klass1;
	int enum8;
	bool boolean2;
	int enum9;
	void* klass2;
	bool boolean3;
	int enum10;
	int integer1;
};
sjkdnwskjdmeghefef wejdwmdkemwskmedfge = { 0x0, 0x82, 0x18, 0x0, 0x0, 0x0, 0x0, false, nullptr, 0x0, false, 0x0, nullptr, false, 0x1, 0 }; // offerwallParams


typedef struct NiggerParams NiggerParams;
namespace __NiggerParams {
	Pointer<NiggerParams(OfferItemType, monoString*)>_sex;
	Pointer<NiggerParams(OfferItemType, monoString*, int)>__sex;
	Pointer<int(NiggerParams)>___sex; // GetItemIndex
	Pointer<NiggerParams(int)>____sex;
	Pointer<monoString* (NiggerParams)>_____sex; // GetItemString
	Pointer<OfferItemType(NiggerParams)>______sex; // GetOfferItemType
	Pointer<monoString* (NiggerParams*)>_______sex; // ToString
}
struct NiggerParams {
	void* struct1;
	void* class1;
	int integer1;
	void* struct2;
	void* struct3;
	void* struct4;
	int integer2;

	static NiggerParams GetItemType(OfferItemType type, const char* name) {
		return __NiggerParams::_sex(type, MonoString::New(name));
	}

	static NiggerParams GetItemType(OfferItemType type, const char* name, int amount) {
		return __NiggerParams::__sex(type, MonoString::New(name), amount);
	}

	NiggerParams(OfferItemType type, const char* name, int amount)
	{
		GetItemType(type, name, amount);
	}

	static int GetItemIndex(OfferItemType type, const char* ItemString) {
		return __NiggerParams::___sex(NiggerParams::GetItemType(type, ItemString));
	}

	static NiggerParams GetItemType(int ItemIndex) {
		return __NiggerParams::____sex(ItemIndex);
	}

	static std::string GetItemString(int ItemIndex) {
		return __NiggerParams::_____sex(NiggerParams::GetItemType(ItemIndex))->ToString();
	}

	static OfferItemType GetOfferItemType(int ItemIndex) {
		return __NiggerParams::______sex(NiggerParams::GetItemType(ItemIndex));
	}

	std::string ToString() {
		return __NiggerParams::_______sex(this)->ToString();
	}
};


namespace dkfmwskfmejge { // Packet
	Pointer<monoString* (void*)> ToString;
	Pointer<void* (void*)> Clone;
	Pointer<monoString* (void*)> get_EventName;
	Pointer<void(void*, monoString*)> set_EventName;
	Pointer<monoString* (void*)> get_Payload;
	Pointer<void(void*, monoString*)> set_Payload;
}

namespace Json {
	Pointer<BNM::Object* (monoString*)>Decode; // Converts to Object but not Il2CppDictionary
	Pointer<monoString* (BNM::Object*)>Encode; // Supports Dictionaries and Lists/Arrays too
	Pointer<monoString* (void*)>SerializeObject;
	Pointer<void* (monoString*, void*)>DeserializeObject;
}

namespace PlayerData { // PlayerData
	Pointer<void* ()>I; // Instance
	Pointer<monoString* (void*)>gT; // get Token
	Pointer<monoString* (void*)>gAS; // get Auth Secret
	
	// auth_v2
	Pointer<void(void*)>a1;
	Pointer<void(void*)>a2;
	Pointer<void(void*)>a3;
	Pointer<void(void*)>a4;
	Pointer<void(void*)>a5;
}


Pointer<void(float)>set_timeScale;
Pointer<void(void*, monoString*, int, bool, bool, void*, sjkdnwskjdmeghefef)> wjfejikfmekdmwjfe; // AddWeapon
Pointer<monoString* ()>iwsdmwoifmefgujerf; // GetPlayerID
#define PlayerID iwsdmwoifmefgujerf()->ToString()
Pointer<void(monoString*)>kdjijfujufjjf; // SetPlayerID
Pointer<int()>efiikkrigrg; // GetPlayerLevel
Pointer<int()>efknedfjrfgh; // GetPlayerXP
Pointer<void(void*, int, int, void*, void*)>defkjfjeref; // AddPlayerXP
Pointer<int(void*)>__GML__; // GetModuleLevel
Pointer<void* (void*, NiggerParams)>__MCC__; // ModuleClassConstructor
Pointer<void* ()>wdfjnefjefj; // GetGameDataClassInstance
Pointer<monoString* ()>efergegeg; // GetGameVersion
Pointer<void* ()>RoyaleDictionary;
Pointer<void* (int)>get_ItemRecord;
Pointer<void* (monoString*)>get_ItemRecord_Str;
Pointer<void* (monoString*)>Type__GetType;
Pointer<monoString* (void*)>get_ClanId;
// cant believe this shit took me less than a minute to find
void* get_ClansController()
{
	BNM::Image* assemblyC = BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image();
	BNM::Class* Singleton = assemblyC->Class(OBF("Rilisoft.Singleton`1"))->Inflate({ assemblyC->Class(OBF("ClansController")) });
	BNM::Method* meth = Singleton->Method(OBF("get_Instance"));
	Pointer<void* (BNM::Method*)>get_Instance(meth->VA());
	return get_Instance(meth);
}
std::string GetClanID()
{
	Il2CppObject* obj = (Il2CppObject*)get_ClansController();
	void* ths = GET_FIELD(void*, obj + (uint64_t)il2cpp_field_get_offset(&obj->Il2CppClass.klass->fields[0x11]));
	return get_ClanId(ths)->ToString();
}


void WIDFJEFKEFIEFGE(const char* eifjiefe, const char* iermfedefgirjg) // Login To Account (id, auth secret)
{
	Pointer<void(void*, monoString*)>diofkrujgnerfmeugr; diofkrujgnerfmeugr = Il2CppUtils::GetMethodPointer(___skibidi::___aa, { nullptr, nullptr, nullptr, {}, 0x8 });
	Pointer<void(void*, monoString*)>efrfefrgrgh; efrfefrgrgh = Il2CppUtils::GetMethodPointer(___skibidi::___aa, { nullptr, nullptr, nullptr, {}, 0xA });
	diofkrujgnerfmeugr(PlayerData::I(), MonoString::New(eifjiefe)); // set id
	if (!std::string(iermfedefgirjg).empty()) { efrfefrgrgh(PlayerData::I(), MonoString::New(iermfedefgirjg)); } // set auth secret
	//efrfefrgrgh(PlayerData::I(), MonoString::New(iermfedefgirjg));
	//kdjijfujufjjf(MonoString::New(eifjiefe));// -> not needed anymore and this shit forces you to restart game to take effect
}

void ZIDFJEFKEFIEFGE() // auth_v2 (call this when you change auth secret / auth id or hook the token dictionary)
{
	void* ths = PlayerData::I();
	using namespace PlayerData;
	a1(ths);
	a2(ths);
	a3(ths);
	a4(ths);
	a5(ths);
	a1(ths);
	a1(ths);
}

void Pointers() {

	auto _P = GET_CLASS(___skibidi::______aa_____);
	auto _WM = GET_CLASS(___skibidi::______aa__);
	auto _ADC = GET_CLASS(___skibidi::___aa);
	auto _ITS = GET_CLASS(___skibidi::______aa);

	BNM::Image* AssemblyC = BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image();
	BNM::Image* UnityEngineCore = BNM::Domain().Assembly(OBF("UnityEngine.CoreModule"))->Image();
	BNM::Image* NewtonsoftJson = BNM::Domain().Assembly(OBF("Newtonsoft.Json"))->Image();
	BNM::Image* mscorlib = BNM::Domain().Assembly(OBF("mscorlib"))->Image();

	efergegeg = UnityEngineCore->Class(OBF("UnityEngine.Application"))->Method(OBF("get_version"))->VA();


	__NiggerParams::_sex(
		_ITS,
		{ OBF("internal static"), nullptr, nullptr, {OBF("ENUM"), OBF("String")} }
	);
	__NiggerParams::__sex(
		_ITS,
		{ OBF("internal static"), nullptr, nullptr, {OBF("ENUM"), OBF("String"), OBF("Int32")} }
	);
	__NiggerParams::___sex(
		_ITS,
		{ OBF("internal"), OBF("Int32"), nullptr, {} }
	);
	__NiggerParams::____sex(
		_ITS,
		{ nullptr, nullptr, nullptr, {}, 0x0 }
	);
	__NiggerParams::_____sex(
		_ITS,
		{ OBF("internal"), OBF("String"), nullptr, {} }
	);
	__NiggerParams::______sex(
		_ITS,
		{ OBF("internal"), OBF("OfferItemType"), nullptr, {} }
	);
	__NiggerParams::_______sex(
		_ITS,
		{ OBF("public override"), OBF("String"), OBF("ToString"), {} }
	);


	dkfmwskfmejge::ToString(
		_P,
		{ OBF("public override"), OBF("String"), OBF("ToString"), {} }
	);
	dkfmwskfmejge::Clone(
		_P,
		{ OBF("internal"), OBF("Packet"), OBF("Clone"), {} }
	);
	dkfmwskfmejge::get_EventName(
		_P,
		{ OBF("public"), OBF("String"), OBF("get_EventName"), {} }
	);
	dkfmwskfmejge::set_EventName(
		_P,
		{ OBF("private"), OBF("Void"), OBF("set_EventName"), {"String"} }
	);
	dkfmwskfmejge::get_Payload(
		_P,
		{ OBF("public"), OBF("String"), OBF("get_Payload"), {} }
	);
	dkfmwskfmejge::set_Payload(
		_P,
		{ OBF("private"), OBF("Void"), OBF("set_Payload"), {"String"}, 0x0 }
	);


	Json::Encode = AssemblyC->Class(OBF("BestHTTP.JSON.Json"))->Method(OBF("Encode"))->VA();
	Json::Decode = AssemblyC->Class(OBF("BestHTTP.JSON.Json"))->Method(OBF("Decode"))->VA();
	Json::SerializeObject = NewtonsoftJson->Class(OBF("Newtonsoft.Json.JsonConvert"))->Method(OBF("SerializeObject"))->VA();
	Json::DeserializeObject = Il2CppUtils::GetMethodPointer((Il2CppClass*)NewtonsoftJson->Class(OBF("Newtonsoft.Json.JsonConvert")), { OBF("public static"), OBF("Object"), OBF("DeserializeObject"), {OBF("String"), OBF("Type")} });


	PlayerData::I(
		_ADC,
		{ nullptr, nullptr, nullptr, {}, 0x19 }
	);
	PlayerData::gT(
		_ADC,
		{ OBF("private"), OBF("Void"), nullptr, {OBF("ENUM")}, 0x1 }
	);
	PlayerData::gAS(
		_ADC,
		{ OBF("internal"), OBF("Void"), nullptr, {OBF("String")}, 0x1 }
	);

	const char* pri = OBF("private");
	const char* IEnumerator = OBF("IEnumerator");
	PlayerData::a1( _ADC, { pri, IEnumerator, nullptr, {}, -0x2 } );
	PlayerData::a2( _ADC, { pri, IEnumerator, nullptr, {}, -0x1 } );
	PlayerData::a3( _ADC, { pri, IEnumerator, nullptr, {}, 0x2 } );
	PlayerData::a4( _ADC, { pri, IEnumerator, nullptr, {}, 0x3 } );
	PlayerData::a5( _ADC, { pri, IEnumerator, nullptr, {}, 0x4 } );


	set_timeScale = UnityEngineCore->Class(OBF("UnityEngine.Time"))->Method(OBF("set_timeScale"))->VA();


	wjfejikfmekdmwjfe(
		_WM,
		{ OBF("internal"), OBF("Void"), nullptr, {OBF("String"), OBF("ENUM"), OBF("Boolean"), OBF("Boolean"), nullptr, nullptr} }
	);

	iwsdmwoifmefgujerf(
		___skibidi::____aa,
		{ nullptr, nullptr, nullptr, {}, 0x2 }
	);

	kdjijfujufjjf(
		___skibidi::____aa,
		{ nullptr, nullptr, nullptr, {}, 0x3 }
	);

	efiikkrigrg(
		___skibidi::______aa____,
		{ nullptr, nullptr, nullptr, {}, 0x6 }
	);

	efknedfjrfgh(
		___skibidi::______aa____,
		{ nullptr, nullptr, nullptr, {}, 0x8 }
	);

	defkjfjeref(
		___skibidi::______aa____,
		{ nullptr, nullptr, nullptr, {}, 0x1c }
	);

	__GML__(
		___skibidi::_____aa,
		{ nullptr, nullptr, nullptr, {}, 0x5 }
	);

	__MCC__(
		___skibidi::_____aa,
		{ OBF("internal"), OBF("Void"), OBF(".ctor"), {nullptr} }
	);

	wdfjnefjefj(
		___skibidi::___aa_,
		{ nullptr, nullptr, nullptr, {}, 0x47 }
	);

	RoyaleDictionary(
		___skibidi::___aa___,
		{ OBF("public static"), OBF("Dictionary`2"), nullptr, {} }
	);

	get_ItemRecord(
		___skibidi::______bb____,
		{ OBF("public static"), OBF("ItemRecord"), nullptr, {OBF("String")}, -0x1 }
	);

	get_ItemRecord_Str(
		___skibidi::______bb____,
		{ OBF("public static"), OBF("ItemRecord"), nullptr, {OBF("String")} }
	);

	Type__GetType = Il2CppUtils::GetMethodPointer((Il2CppClass*)mscorlib->Class(OBF("System.Type")), { OBF("public static"), OBF("Type"), OBF("GetType"), {OBF("String")} });

	Il2CppObject* ClansController = (Il2CppObject*)get_ClansController();
	Il2CppObject* ClanInfo = GET_FIELD(Il2CppObject*, ClansController + (uint64_t)il2cpp_field_get_offset(&ClansController->Il2CppClass.klass->fields[0x11]));
	get_ClanId = (uintptr_t)ClanInfo->Il2CppClass.klass->methods[0x0]->methodPointer;
}