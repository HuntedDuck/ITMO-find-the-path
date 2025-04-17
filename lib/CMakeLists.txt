add_library(postprocessing_and_output postprocessing_and_output.cpp postprocessing_and_output.h)
add_library(cache cache.cpp cache.h)
add_library(API_DATA API_DATA.h)


target_link_libraries(cache PRIVATE cpr::cpr)
target_link_libraries(cache PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(postprocessing_and_output PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(postprocessing_and_output PRIVATE cache)
target_link_libraries(postprocessing_and_output PRIVATE API_DATA)



target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})