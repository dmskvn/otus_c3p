set(TARGET_NAME CMD)

set(SRCS
    include/cmd/ICommand.hpp
    include/cmd/ICommandStorage.hpp
    include/cmd/ICommandFactory.hpp

    src/Add.hpp
    src/Add.cpp

    src/BlockClosing.cpp
    src/BlockClosing.hpp

    src/BlockOpening.cpp
    src/BlockOpening.hpp

    src/CommandStorage.cpp
    src/CommandStorage.hpp

    src/CommandFactory.cpp
    src/CommandFactory.hpp

)

set(LIBS_PRIV
)

set(LIBS_PUB
)

set(DIRS_PRIV
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
