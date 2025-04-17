#pragma once

#include <string>
#include <vector>

struct pugination{
    int total;
    int limit;
    int offset;
};

struct station{
    std::string code;
    std::string title;
    std::string station_type;
    std::string transport_type;
};

struct place{
    std::string code;
    std::string type;
    std::string title;
};

struct segment{
    std::string arrival;
    station from;
    std::string departure_platform;
    std::string departure;
    std::string departure_terminal;
    station to;
    bool has_transfers;
    int duration;
    std::string arrival_terminal;
    std::string start_date;
    std::string arrival_platform;
};

struct search{
    std::string date;
    place to; 
    place from;
};

struct total_data{
    pugination numeration;
    std::vector<segment> segments;
};