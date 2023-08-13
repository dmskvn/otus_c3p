set(TARGET_NAME BAYAN)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)
find_package(Threads)

set(SRCS
        include/bayan/ICommandLineParser.hpp
        include/bayan/IFilesProcessor.hpp
        src/CommandLineParser.cpp
        src/FilesProcessor.hpp
        src/FilesProcessor.cpp
)

set(LIBS_PRIV
    Boost::program_options
    pthread
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

add_library(${TARGET_NAME} ${SRCS})

target_link_libraries(${TARGET_NAME}
        PRIVATE ${LIBS_PRIV}
        PUBLIC ${LIBS_PUB}
        )

target_include_directories(${TARGET_NAME}
        PRIVATE ${DIRS_PRIV}
        PUBLIC ${DIRS_PUB}
        )

target_compile_definitions(${TARGET_NAME}
        PRIVATE ${DEFS_PRIV}
        PUBLIC ${DEFS_PUB}
        )

