set(TARGET_NAME ASYNC)

message ("!!!!!!!!!!! I AM IN SYNC !!!!!!!!!!!!!!!")

set(SRCS
  include/async/async.h
  src/Impl.cpp
)

set (CMAKE_CXX_STANDARD 17)

set(LIBS_PRIV
    CMD
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

