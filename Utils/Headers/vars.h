#include "lists.h"
#include <functional>
#include "Headers/nlohmann/json.h"
#include "../Backend/Backend.h"
#include "Headers/Auth.h"


namespace vars {
	int PlayerLVL = 1;
	bool SecureLvl = false;
	bool AutoLvl65 = true;
	bool ReloadWhenReceived = true;

	float GameSpeed = 1.0f;
	bool SetGameSpeed = false;

	char GetPlayerInfoInput[100] = "";
	bool GetPlayerInfo = false;

	// Dev
	bool SendRequest = false;
	bool SnapshotRequest = false;

	// Functions
	bool AlwaysUpdateSlotsWhenRequestSent = true; // whenever you send a request, it will first update the slots, then it will send your request
	bool AlwaysUpdateSlotsWhenRequestSentV2 = false; // dont edit anything here, its required for above



	std::vector<std::function<void()>> CallInUnityThread;

	ojson SendRequestData;
	std::vector<std::function<void(const char*&, int&)>> WebsocketSendRequest; // event name, send amount


	struct WSResponse
	{
		std::string eventName;
		std::string Payload;
		bool ReloadWhenReceived = false;
		bool NotifyWhenReceived = false;
		const char* ResponseReceivedName = "";
		ImGuiToastType toastType = ImGuiToastType::Info;
		bool ForceSuccessStatus = false;
		std::function<void(ojson, ojson)>OnRequestReceived = [](ojson eifjrifgg, ojson iefjmreif) {}; // request, packet
	};
	std::vector<WSResponse> WSResponses; // for controlling all the responses
	std::vector<WSResponse> WSResponsesV2; // ALL!!! responses are being inserted in here

	// Max Account Subtab
	int CheckAutoMaxLvl()
	{
		return vars::AutoLvl65 ? 65 : vars::PlayerLVL;
	}

	// Other Tab
	// Offers Subtab
	bool OFFERS_FreePaidOffers = false;
	char OFFERS_PaidOffersPrices[7] = "1";
	bool OFFERS_SetPaidOffersPrices = false;

	// Auth Subtab
	char AUTH_PlayerToken[300] = "a";
	bool AUTH_LoginWithToken = false;

	// Misc subtab
	bool FUN__DisableAnalytics = false;
}