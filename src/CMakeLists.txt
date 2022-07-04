include_directories(${PROJECT_SOURCE_DIR}/src/headers)

add_executable(cism main.c fileInterface.c errorHandling.c organization.c headers/algorithm.h algorithm.c)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")