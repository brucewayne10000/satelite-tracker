
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

using json = nlohmann::json;

// Callback to collect the response into a std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl = curl_easy_init();
    CURLcode res;
    std::string responce;
    std::string apiKey = "AJ65NB-DVTCA4-X6ZG5M-5KAH";
    std::string url = "https://api.n2yo.com/rest/v1/satellite/positions/36122/44.88312/-68.67198/38/2/&apiKey=AJ65NB-DVTCA4-X6ZG5M-5KAH";
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            json sateliteInfo = json::parse(responce);
            std::string sateliteName = sateliteInfo["info"]["satname"].get<std::string>();
            double satLatitude = sateliteInfo["positions"][0]["satlatitude"].get<double>();
            double satlongtitude = sateliteInfo["positions"][0]["satlongitude"];
            std::cout << "the satelite name is " << sateliteName << " the latitude is " << satLatitude << " the longtitude " << satlongtitude;

        }
        else {
            std::cerr << "CURL failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}
