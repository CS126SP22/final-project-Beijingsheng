cmake_minimum_required(VERSION 3.21)
project(final_project_Beijingsheng)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND SOURCE_FILES    src/simulator.cpp
                            src/brain.cpp
                            src/metro.cpp
                            src/passenger.cpp
                            src/dijkstra.cpp)

ci_make_app(
        APP_NAME        mini-metro
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/mini_metro_main.cpp ${SOURCE_FILES}
        INCLUDES        include
)
