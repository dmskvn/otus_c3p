cmake_minimum_required(VERSION 3.16.3)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(otus-c3p-hw VERSION ${PROJECT_VESRION})

enable_testing()

add_subdirectory(version_provider)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE "VERSION_PROVIDER")

add_test(VERSION_PROVIDER_TEST version_provider/test/VERSION_PROVIDER_TEST)
