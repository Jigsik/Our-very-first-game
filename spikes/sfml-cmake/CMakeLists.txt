cmake_minimum_required(VERSION 3.22)

project(our_very_first_game_sfml_spike LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(sfml_spike src/main.cpp)
target_link_libraries(sfml_spike PRIVATE sfml-graphics sfml-window sfml-system)

target_compile_definitions(sfml_spike PRIVATE
  REPO_ROOT="${CMAKE_CURRENT_LIST_DIR}/../.."
)
