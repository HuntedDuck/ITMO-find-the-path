#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include<cache.h>
#include<API_DATA.h>

total_data postprocessing(std::string date_of_departure);

std::string format_duration(int seconds);

void output(const total_data& data);