set(TARGET_NAME ASYNC)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)
find_package(Threads)

set (CMAKE_CXX_STANDARD 17)

set(SRCS
        include/async/async.h
        src/async.cpp
)

set(LIBS_PRIV
    Boost::program_options
    pthread
    "CMD"
)

set(LIBS_PUB
        )

set(DIRS_PRIV
        #${CMAKE_CURRENT_BINARY_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

set(DIRS_PUB
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

add_library("async" ${SRCS})

target_link_libraries("async"
        PRIVATE ${LIBS_PRIV}
        PUBLIC ${LIBS_PUB}
        )

target_include_directories("async"
        PRIVATE ${DIRS_PRIV}
        PUBLIC ${DIRS_PUB}
        )

target_compile_definitions("async"
        PRIVATE ${DEFS_PRIV}
        PUBLIC ${DEFS_PUB}
        )

add_executable("async_example" main.cpp)

target_link_libraries("async"
  PRIVATE ${LIBS_PRIV}
  PUBLIC ${LIBS_PUB}
)


target_link_libraries("async_example" PRIVATE "async")


install(TARGETS "async" RUNTIME DESTINATION bin)
