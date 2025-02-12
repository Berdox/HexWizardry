cmake_minimum_required(VERSION 3.10)

set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(NOT CMAKE_TOOLCHAIN_FILE AND EXISTS "${vcpkg}")
  set(CMAKE_TOOLCHAIN_FILE "${vcpkg}"
      CACHE FILEPATH "CMake toolchain file")
  message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project ("HexWizardry")

# Add source to this project's executable.
add_executable (hexWizardary "src/main.cpp" "include/HexEditor.hpp")

find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

target_link_libraries(hexWizardary PRIVATE imgui::imgui)
target_link_libraries(hexWizardary PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
target_link_libraries(hexWizardary PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET hexWizardary PROPERTY CXX_STANDARD 23) 
endif()
 
# TODO: Add tests and install targets if needed.
