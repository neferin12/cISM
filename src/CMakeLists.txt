include_directories(${PROJECT_SOURCE_DIR}/src/headers)

add_executable(cism main.c fileInterface.c errorHandling.c organization.c headers/algorithm.h algorithm.c headers/constants.h constants.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(cism PkgConfig::deps)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")