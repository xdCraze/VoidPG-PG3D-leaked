#pragma once

//#define CURL_STATICLIB
#include <curl/curl.h>
#include <Wbemidl.h>
#include <comdef.h>
#include <Iphlpapi.h>
#pragma comment(lib, "libcurl_a.lib")

#include "Backend/Misc.h"


std::string irejmfioerjkfmierjgiueujigeujiguiewjfgiwefjwofjweihfnzuehdiewjfikenfeujfdhn = ""; // when you call the request method, it will set the response to this variable (for double checking, in case it gets hooked)
class httpSx
{
public:
	enum eoekmfkeeugeufgewu { // RequestMethod
		efkmefkeoifmejkfgn, // GET
		keomfeikfjmejfefnj, // POST
		edfmefkerofkeifefe, // OPTIONS
		efmefioefiekfikefd, // PUT
		eofkmeifeifjefefij, // DELETE
		kemfkewdfkemfkeefi  // PATCH
	};

	static std::string weikfnwejifnmeujfgnehfgew(const std::string& url, eoekmfkeeugeufgewu method, std::vector<const char*> _headers = { OBF("Content-Type: application/json") }, std::string payload = "") { // Request
		curl_global_init(CURL_GLOBAL_ALL);
		CURL* curl = curl_easy_init();
		CURLcode res;
		std::string ediknmfujwejdfiejfmerjnfwehf; // response_data

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

			if (method == eoekmfkeeugeufgewu::keomfeikfjmejfefnj) {
				curl_easy_setopt(curl, CURLOPT_POST, 1L);
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
			}
			else if (method == eoekmfkeeugeufgewu::efkmefkeoifmejkfgn) {
				curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
			}
			else if (method == eoekmfkeeugeufgewu::efmefioefiekfikefd) {
				curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, OBF("PUT"));
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
			}
			else if (method == eoekmfkeeugeufgewu::eofkmeifeifjefefij) {
				curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, OBF("DELETE"));
			}
			else if (method == eoekmfkeeugeufgewu::kemfkewdfkemfkeefi) {
				curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, OBF("PATCH"));
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
			}
			else if (method == eoekmfkeeugeufgewu::edfmefkerofkeifefe) {
				curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, OBF("OPTIONS"));
			}

			struct curl_slist* headers = NULL;
			for (int i = 0; i < _headers.size(); i++) {
				headers = curl_slist_append(headers, _headers[i]);
			}

			if (!payload.empty()) {
				headers = curl_slist_append(headers, OBF("Content-Type: application/json"));
			}

			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, weikfweodlwofeikgeikfeikfjm);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ediknmfujwejdfiejfmerjnfwehf);

			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
		}

		curl_global_cleanup();
		irejmfioerjkfmierjgiueujigeujiguiewjfgiwefjwofjweihfnzuehdiewjfikenfeujfdhn = ediknmfujwejdfiejfmerjnfwehf;
		return ediknmfujwejdfiejfmerjnfwehf;
	}

	template<typename T>
	static std::string weikfnwejifnmeujfgnehfgew(const std::string& url, eoekmfkeeugeufgewu method, std::vector<const char*> _headers = { OBF("Content-Type: application/json") }, T _json = T::object()) { // ojson or json
		return weikfnwejifnmeujfgnehfgew(url, method, _headers, _json.dump());
	}

private:
	static size_t weikfweodlwofeikgeikfeikfjm(char* ptr, size_t size, size_t nmemb, std::string* data) { // WriteCallback
		size_t bytes = size * nmemb;
		data->append(ptr, bytes);
		return bytes;
	}
};