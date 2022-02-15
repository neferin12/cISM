include_directories(${PROJECT_SOURCE_DIR}/src/headers)

add_executable(cism main.c fileInterface.c errorHandling.c organization.c)