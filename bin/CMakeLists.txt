add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE postprocessing_and_output)
target_link_libraries(${PROJECT_NAME} PRIVATE cache)
target_link_libraries(${PROJECT_NAME} PRIVATE API_DATA)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})