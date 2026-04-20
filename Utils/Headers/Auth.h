#pragma once

#include <iostream>
#include <sstream>
#include <wincrypt.h>

#include "httpSx.h"
#include "Headers/nlohmann/json.h"

using json = nlohmann::json;
using ojson = nlohmann::ordered_json;

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/buffer.h>

#define WIN32_LEAN_AND_MEAN
//#define OPENSSL_USE_STATIC_LIBS

#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")



std::string openssl_sha(const char* data) {
	std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
	unsigned int len;
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	if (!ctx) {
		return "";
	}
	if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1 ||
		EVP_DigestUpdate(ctx, data, strlen(data)) != 1 ||
		EVP_DigestFinal_ex(ctx, hash.data(), &len) != 1) {
		EVP_MD_CTX_free(ctx);
		return "";
	}
	EVP_MD_CTX_free(ctx);
	std::stringstream ss;
	for (unsigned int i = 0; i < len; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
	}
	return ss.str();
}

std::string md5(const std::string& content) {
	EVP_MD_CTX* context = EVP_MD_CTX_new();
	const EVP_MD* md = EVP_md5();
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;
	std::string output;

	EVP_DigestInit_ex(context, md, NULL);
	EVP_DigestUpdate(context, content.c_str(), content.length());
	EVP_DigestFinal_ex(context, md_value, &md_len);
	EVP_MD_CTX_free(context);

	output.resize(md_len * 2);
	for (unsigned int i = 0; i < md_len; ++i)
		sprintf_s(&output[i * 2], output.size() - i * 2 + 1, OBF("%02x"), md_value[i]);
	return output;
}


std::string jhedbfujewnbghbe(const std::vector<unsigned char>& hedbfuewgherfg) { // Base64 encode (vector input)
	BIO* b64 = BIO_new(BIO_f_base64());
	BIO* bio = BIO_new(BIO_s_mem());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // Don't use newlines
	bio = BIO_push(b64, bio);

	if (BIO_write(bio, hedbfuewgherfg.data(), static_cast<int>(hedbfuewgherfg.size())) <= 0) {
		BIO_free_all(bio);
		throw std::runtime_error("");
	}

	if (BIO_flush(bio) <= 0) {
		BIO_free_all(bio);
		throw std::runtime_error("");
	}

	BUF_MEM* bufferPtr;
	BIO_get_mem_ptr(bio, &bufferPtr);

	std::string encodedData(bufferPtr->data, bufferPtr->length);
	BIO_free_all(bio);
	return encodedData;
}

std::string irtjfgiejg(std::string ekojfeufg) // Base64 encode (string input)
{
	return jhedbfujewnbghbe(std::vector<unsigned char>(ekojfeufg.begin(), ekojfeufg.end()));
}

#define b64encode(str) irtjfgiejg(str)

std::vector<unsigned char> rkowefirgrgnr(const std::string& efegrhgrh) { // Base64 decode (const string encodedB64)
	BIO* bio = BIO_new_mem_buf(efegrhgrh.data(), static_cast<int>(efegrhgrh.size()));
	BIO* b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // Dont use newlines
	bio = BIO_push(b64, bio);

	std::vector<unsigned char> decoded(efegrhgrh.size());
	int decodedLen = BIO_read(bio, decoded.data(), static_cast<int>(efegrhgrh.size()));
	if (decodedLen < 0) {
		throw std::runtime_error("");
	}
	decoded.resize(decodedLen);

	BIO_free_all(bio);
	return decoded;
}

// string Base64 decode (const string encodedB64)
std::string edikeiofe(const std::string jkemnfenjf)
{
	std::vector<unsigned char> roegjeif = rkowefirgrgnr(jkemnfenjf);
	return std::string(roegjeif.begin(), roegjeif.end());
}

#define b64decode(encodedStr) edikeiofe(encodedStr)



std::string wdejdnwjkdfmnejfbn() { // getMAC
	std::string macAddress;
	IP_ADAPTER_INFO* AdapterInfo = nullptr;
	ULONG outBufLen = sizeof(IP_ADAPTER_INFO);

	AdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(malloc(outBufLen));
	if (AdapterInfo == nullptr) {
		return "";
	}

	if (GetAdaptersInfo(AdapterInfo, &outBufLen) == ERROR_BUFFER_OVERFLOW) {
		free(AdapterInfo);
		AdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(malloc(outBufLen));
		if (AdapterInfo == nullptr) {
			return "";
		}
	}

	if (GetAdaptersInfo(AdapterInfo, &outBufLen) == NO_ERROR) {
		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
		do {
			char mac[18];
			sprintf_s(mac, OBF("%02X:%02X:%02X:%02X:%02X:%02X"),
				pAdapterInfo->Address[0], pAdapterInfo->Address[1],
				pAdapterInfo->Address[2], pAdapterInfo->Address[3],
				pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
			macAddress = mac;

			pAdapterInfo = pAdapterInfo->Next;
		} while (pAdapterInfo);
	}

	free(AdapterInfo);
	return macAddress;
}


std::string kmedwdkefjfedmefj() { // GetDeviceID
	DWORD kwemjkfjnrfrf;
	GetVolumeInformationA(OBF("C:\\"), NULL, 0, &kwemjkfjnrfrf, NULL, NULL, NULL, 0);
	std::stringstream ss;
	ss << std::hex << kwemjkfjnrfrf;
	std::string ejfekfrjnfrhjnf = ss.str();
	std::string efejdejfhhgf = ejfekfrjnfrhjnf + wdejdnwjkdfmnejfbn();
	return efejdejfhhgf;
}


namespace vars {
	/*
	char rijfjerifkefef[100] = ""; // Username
	char erifjejkfjrgrg[100] = ""; // Password
	std::string orfmgkemfkrg = ""; // Status Response
	std::string eifjeuifjeuf = ""; // Check Login function Return string and this string (login function must be fail and this string must be succes to confuse the cracker nigger)
	std::string iwefdefefkje = ""; // Needed to check for the Login Success (If Success, string will be set to "dednmwidrf")
	char ekfmwfmfiweiwd[100] = ""; // User (for displaying in the menu)
	char wwofmiejfewdfj[100] = ""; // Expiry (for displaying in the menu)
	//FileHandling UserData(edikeiofe("Vm9pZFBHQ29uZmlnLnR4dA==").c_str()); // VoidPGConfig.txt
	FileHandling UserData("VoidPGConfig.txt"); // VoidPGConfig.txt
	bool ijenujefnjerfnehnfef = false; // Remember Me
	bool ujirngjenujfgrgjgikr = true; // CheckAutoLogin
	bool wijdiwduefuejfieufiw = false; // Logged in (used for Auth Activity, can also be used for other shit which idk)
	std::string oeifjkeokfiegj = ""; // IP Address
	*/
	char rijfjerifkefef[100] = ""; // Username
	char erifjejkfjrgrg[100] = ""; // Password
	std::string orfmgkemfkrg = ""; // Status Response
	std::string eifjeuifjeuf = ""; // Check Login function Return string and this string (login function must be fail and this string must be succes to confuse the cracker nigger)
	std::string iwefdefefkje = "dednmwidrf"; // Needed to check for the Login Success (If Success, string will be set to "dednmwidrf")
	char ekfmwfmfiweiwd[100] = "Lifetime User"; // User (for displaying in the menu)
	char wwofmiejfewdfj[100] = "Never"; // Expiry (for displaying in the menu)
	//FileHandling UserData(edikeiofe("Vm9pZFBHQ29uZmlnLnR4dA==").c_str()); // VoidPGConfig.txt
	FileHandling UserData("VoidPGConfig.txt"); // VoidPGConfig.txt
	bool ijenujefnjerfnehnfef = false; // Remember Me
	bool ujirngjenujfgrgjgikr = true; // CheckAutoLogin
	bool wijdiwduefuejfieufiw = false; // Logged in (used for Auth Activity, can also be used for other shit which idk)
	std::string oeifjkeokfiegj = ""; // IP Address
}

namespace wdkdfjf { // Auth/Security api
	// Login (username, password, hwid, encodekey): returns: Fail___, 
	//														  ___Success (behave Success as Fail and Fail as Success)
	std::string wsjmdwkdiemfjerf(std::string ekjfekfmrjfgnrng, std::string deudef, std::string wwujewdfjef, std::string wdjwemdedmf)
	{
		std::string iofjkeofkeofg = OBF("___Success");
		std::string eifjweiodkeri = OBF("Fail___");
		if (wdjwemdedmf != OBF("wdwdwfeefw")) return iofjkeofkeofg;
		ojson efimefmrj = {
			{OBF("username"), irjfejfrnhgnrhjfjrgjrng(ekjfekfmrjfgnrng)}, // username
			{OBF("password"), irjfejfrnhgnrhjfjrgjrng(deudef)}, // password
			{OBF("deviceid"), irjfejfrnhgnrhjfjrgjrng(wwujewdfjef)}, // deviceid
			{OBF("ID"),		  vars::oeifjkeokfiegj} // actually ip address lol
		};
		// https://leminare.xyz/api/login
		std::string dferfgrgrg = httpSx::weikfnwejifnmeujfgnehfgew<ojson>(edikeiofe(OBF("aHR0cHM6Ly9sZW1pbmFyZS54eXovYXBpL2xvZ2lu")), httpSx::keomfeikfjmejfefnj, { OBF("User-Agent: myModMenu") }, efimefmrj); // response
		if (!ofmefnrjhfgn(dferfgrgrg, edikeiofe(OBF("InN1Y2Nlc3MiOiJPayI="))) && !ofmefnrjhfgn(irejmfioerjkfmierjgiueujigeujiguiewjfgiwefjwofjweihfnzuehdiewjfikenfeujfdhn, edikeiofe(OBF("InN1Y2Nlc3MiOiJPayI=")))) {
			if (strcmp(ekfmefjerhfgrehg(dferfgrgrg, edikeiofe(OBF("InN1Y2Nlc3MiOiJPayI="))).c_str(), OBF("Sifejmfgrlwfkmekgehgdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergwefegerhgodkbnrbmolekfekgrghodefgjret402446eofgkm462ergwfefgrehrhdkbnrbmwpfkerifejmfgrofkrfgodwef101201kaswsowpfker02446eofgkm462ergkijhdkbnrbmoegjr02446eofgkm462ergkeefolergoegjrwfefgrehrhdontwwdrfhelpdwef101201kaswsowpfkerodfkewdwoef02446eofgkm462ergekgerjgdwef101201kaswsoifejmfgrwfefgrehrh010009wfe")) == 0) {
				ojson mwidwkdfnefn = ojson::parse(dferfgrgrg); // Packet
				vars::orfmgkemfkrg = OBF("Success!");
				vars::eifjeuifjeuf = iofjkeofkeofg;
				std::string __ = mwidwkdfnefn[OBF("user")].dump();
				__.pop_back();
				__.erase(0, 1);

				std::string ___ = mwidwkdfnefn[OBF("expiry")].dump();
				___.pop_back();
				___.erase(0, 6);
				___.erase(___.length() - 4, ___.length());

				strcpy_s(vars::ekfmwfmfiweiwd, __.c_str());
				strcpy_s(vars::wwofmiejfewdfj, ___.c_str());
				return eifjweiodkeri;
			}
		}
		try {
			ojson jkedfjenfhrfbfg = ojson::parse(dferfgrgrg);
			vars::orfmgkemfkrg = jkedfjenfhrfbfg[OBF("error")];
			return iofjkeofkeofg;
		}
		catch (ojson::parse_error e) {
			vars::orfmgkemfkrg = OBF("Error: Server might be down, please contact\nthe VoidPG Team or be Patient!");
			return iofjkeofkeofg;
		}

		return iofjkeofkeofg;
	}

	void ierjfowejkfgierfi() // Security Check
	{
		// deprecated since void 2.0
	}
}