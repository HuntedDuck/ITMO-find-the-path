#include <cache.h>
#include <cpr/cpr.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


bool check_in_cache(std::string given_file){
    std::ifstream file(given_file);
    return file.is_open();
}

std::string get_data_from_cache(std::string given_file) {
    std::ifstream streaming_file(given_file);
    std::ostringstream output_string;
    output_string << streaming_file.rdbuf();
    std::string res = output_string.str();
    streaming_file.close();
    return res;
}

void upload_data_in_cache(std::string cache_file1, std::string cache_file2, std::string result_of_api_request1, std::string result_of_api_request2) {
    std::ofstream input_file1(cache_file1);
    std::ofstream input_file2(cache_file2);
    
    input_file1 << result_of_api_request1;
    input_file2 << result_of_api_request2;
    
    input_file1.close();
    input_file2.close();
}



std::pair<std::string, std::string> request_processing(std::string date_of_departure) {
    std::string cache_file_spb_ekb = "/Users/dmitrijgaev/labwork6-HuntedDuck/cache/SPB-EKB_" + date_of_departure + ".txt";
    std::string cache_file_ekb_spb = "/Users/dmitrijgaev/labwork6-HuntedDuck/cache/EKB-SPB_" + date_of_departure + ".txt";
    
    if (check_in_cache(cache_file_spb_ekb) && check_in_cache(cache_file_ekb_spb)) {
        std::string data_spb_ekb = get_data_from_cache(cache_file_spb_ekb);
        std::string data_ekb_spb = get_data_from_cache(cache_file_ekb_spb);
        std::pair<std::string, std::string> res;
        res.first = data_spb_ekb;
        res.second = data_ekb_spb;
        return res;
    }
    else {
        cpr::Response response_spb_ekb = cpr::Get(cpr::Url{"https://api.rasp.yandex.net/v3.0/search/"},
                                                  cpr::Parameters{{"apikey", ""},
                                                                  {"from", "c2"},
                                                                  {"to", "c54"},
                                                                  {"date", date_of_departure},
                                                                  {"transfers", "true"}});
        cpr::Response response_ekb_spb = cpr::Get(cpr::Url{"https://api.rasp.yandex.net/v3.0/search/"},
                                                  cpr::Parameters{{"apikey", ""},
                                                                  {"from", "c54"},
                                                                  {"to", "c2"},
                                                                  {"date", date_of_departure},
                                                                  {"transfers", "true"}});

        std::string result_spb_ekb = response_spb_ekb.text;
        std::string result_ekb_spb = response_ekb_spb.text;

        upload_data_in_cache(cache_file_spb_ekb, cache_file_ekb_spb, result_spb_ekb, result_ekb_spb);

        std::pair<std::string, std::string> res;
        res.first = result_spb_ekb;
        res.second = result_ekb_spb;
        return res;
    }
}