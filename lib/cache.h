#pragma once
#include <cpr/cpr.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


bool check_in_cache(std::string given_file);

std::string get_data_from_cache(std::string given_file);

void upload_data_in_cache(std::string cache_file1, std::string cache_file2, std::string result_of_api_request1, std::string result_of_api_request2);

std::pair<std::string, std::string> request_processing(std::string date_of_departure);

