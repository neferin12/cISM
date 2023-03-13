include_directories(${PROJECT_SOURCE_DIR}/src/headers)

add_executable(cism main.c fileInterface.c errorHandling.c organization.c headers/algorithm.h algorithm.c headers/constants.h constants.c cismMPI.c headers/cismMPI.h)

find_package(PkgConfig REQUIRED)
find_package(MPI REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
target_link_libraries(cism PkgConfig::deps MPI_C)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
