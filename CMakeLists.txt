cmake_minimum_required(VERSION 3.16.3)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(otus-c3p-hw VERSION ${PROJECT_VESRION})

enable_testing()

add_subdirectory(version_provider)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE "VERSION_PROVIDER")

add_test(VERSION_PROVIDER_TEST version_provider/test/VERSION_PROVIDER_TEST)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(VERSION_PROVIDER PRIVATE
        /W4
    )
    target_compile_options(VERSION_PROVIDER_TEST PRIVATE
        /W4
    )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(VERSION_PROVIDER PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(VERSION_PROVIDER_TEST PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

