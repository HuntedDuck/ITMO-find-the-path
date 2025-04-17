#include <postprocessing_and_output.h>

#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include<cache.h>
#include<API_DATA.h>


std::pair<total_data, total_data> postprocessing(std::string date_of_departure){
    std::pair<std::string, std::string> responces = request_processing(date_of_departure);
    std::string spb_ekb_responce = responces.first;
    std::string ekb_spb_responce = responces.second;

    nlohmann::json spb_ekb = nlohmann::json::parse(spb_ekb_responce);
    nlohmann::json ekb_spb = nlohmann::json::parse(ekb_spb_responce);

    total_data data_spb_ekb;
    total_data data_ekb_spb;

    data_spb_ekb.numeration = { spb_ekb["pagination"]["total"], spb_ekb["pagination"]["limit"], spb_ekb["pagination"]["offset"] };

    for (const auto& seg : spb_ekb["segments"]) {
        segment s;
        s.arrival = seg["arrival"];
        s.from = { seg["from"]["code"], seg["from"]["title"], seg["from"]["station_type"], seg["from"]["transport_type"] };
        s.departure_platform = seg["departure_platform"];
        s.departure = seg["departure"];
        s.departure_terminal = seg["departure_terminal"].is_null() ? "" : seg["departure_terminal"];
        s.to = { seg["to"]["code"], seg["to"]["title"], seg["to"]["station_type"], seg["to"]["transport_type"] };
        s.has_transfers = seg["has_transfers"];
        s.duration = seg["duration"];
        s.arrival_terminal = seg["arrival_terminal"].is_null() ? "" : seg["departure_terminal"];
        s.start_date = seg["start_date"];
        s.arrival_platform = seg["arrival_platform"];
        data_spb_ekb.segments.push_back(s);
    }


    data_ekb_spb.numeration = { ekb_spb["pagination"]["total"], ekb_spb["pagination"]["limit"], ekb_spb["pagination"]["offset"] };

    for (const auto& seg : ekb_spb["segments"]) {
        segment s;
        s.arrival = seg["arrival"];
        s.from = { seg["from"]["code"], seg["from"]["title"], seg["from"]["station_type"], seg["from"]["transport_type"] };
        s.departure_platform = seg["departure_platform"];
        s.departure = seg["departure"];
        s.departure_terminal = seg["departure_terminal"].is_null() ? "" : seg["departure_terminal"];
        s.to = { seg["to"]["code"], seg["to"]["title"], seg["to"]["station_type"], seg["to"]["transport_type"] };
        s.has_transfers = seg["has_transfers"];
        s.duration = seg["duration"];
        s.arrival_terminal = seg["arrival_terminal"].is_null() ? "" : seg["departure_terminal"];
        s.start_date = seg["start_date"];
        s.arrival_platform = seg["arrival_platform"];
        data_ekb_spb.segments.push_back(s);
    }

    std::pair<total_data, total_data> res;
    res.first = data_spb_ekb;
    res.second = data_ekb_spb;
    return res;
}


std::string format_duration(int seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

void output(std::pair<total_data, total_data> data) {
    for (const auto& seg : data.first.segments) {
        std::string transport_type = seg.from.transport_type;
        std::string departure_type = (transport_type == "plane") ? "вылета" : "выезда";
        
        std::cout << seg.from.title << " (" << seg.from.station_type << ") -> "
                  << seg.to.title << " (" << seg.to.station_type << ")\n";
        
        std::cout << "Время " << departure_type << ": " << seg.departure
                  << " - " << seg.arrival << "\n";
        
        std::cout << "Тип транспорта: " << transport_type << "\n";

        std::cout << "Продолжительность: " << format_duration(seg.duration) << "\n";
    }

    for (const auto& seg : data.second.segments) {
        std::string transport_type = seg.from.transport_type;
        std::string departure_type = (transport_type == "plane") ? "вылета" : "выезда";
        
        std::cout << seg.from.title << " (" << seg.from.station_type << ") -> "
                  << seg.to.title << " (" << seg.to.station_type << ")\n";
        
        std::cout << "Время " << departure_type << ": " << seg.departure
                  << " - " << seg.arrival << "\n";
        
        std::cout << "Тип транспорта: " << transport_type << "\n";

        std::cout << "Продолжительность: " << format_duration(seg.duration) << "\n\n";
    }
}


