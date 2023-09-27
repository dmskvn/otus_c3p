cmake_minimum_required(VERSION 3.16.3)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(otus-c3p VERSION ${PROJECT_VESRION})

enable_testing()

add_subdirectory(allocator)

add_subdirectory(version_provider)

add_subdirectory(ip_filter)

add_subdirectory(ip_template)

add_subdirectory(editor)

add_subdirectory(matrix)

add_subdirectory(cmd)

add_subdirectory(bayan)

add_subdirectory(async)

add_subdirectory(lock_free)

#add_executable(${PROJECT_NAME} main.cpp)

#target_link_libraries(${PROJECT_NAME} PRIVATE "ALLOCATOR")
#target_link_libraries(${PROJECT_NAME} PRIVATE "VERSION_PROVIDER")
#target_link_libraries(${PROJECT_NAME} PRIVATE "IP_FILTER")
#target_link_libraries(${PROJECT_NAME} PRIVATE "IP_TEMPLATE")
#target_link_libraries(${PROJECT_NAME} PRIVATE "EDITORPLOT")
#target_link_libraries(${PROJECT_NAME} PRIVATE "EDITORDRAWING")
#target_link_libraries(${PROJECT_NAME} PRIVATE "EDITORDOCUMENT")
#target_link_libraries(${PROJECT_NAME} PRIVATE "MATRIX")
#target_link_libraries(${PROJECT_NAME} PRIVATE "ASYNC")
#target_link_libraries(${PROJECT_NAME} PRIVATE "LOCK_FREE")


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
