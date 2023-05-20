set(TARGET_NAME IP_FILTER_TEST)

find_package(GTest REQUIRED)

set(SRCS
  tests.cpp
)

set(LIBS_PRIV
  IP_FILTER
  gtest
  gmock
  pthread
)

set(LIBS_PUB
)

set(DIRS_PRIV
  ${GTEST_INCLUDE_DIRS}
)

set(DIRS_PUB
)

add_executable(${TARGET_NAME} ${SRCS})

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
