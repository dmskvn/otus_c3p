set(TARGET_NAME LOCK_FREE)

find_package(Threads)

set(SRCS
  include/lock_free/Motivation.hpp
  include/lock_free/SpinLockMtx.hpp
  include/lock_free/Stack.hpp
)

set(LIBS_PRIV
)

set(LIBS_PUB
)

set(DIRS_PRIV
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(DIRS_PUB
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(${TARGET_NAME} INTERFACE)

target_link_libraries(${TARGET_NAME}
  PRIVATE ${LIBS_PRIV}
  PUBLIC ${LIBS_PUB}
)

target_include_directories(${TARGET_NAME}
  INTERFACE
  ./include
)

target_compile_definitions(${TARGET_NAME}
  PRIVATE ${DEFS_PRIV}
  PUBLIC ${DEFS_PUB}
)

add_executable("lock_free_example" main.cpp)

target_link_libraries(${TARGET_NAME}
  PRIVATE ${LIBS_PRIV}
  PUBLIC ${LIBS_PUB}
)


target_link_libraries("lock_free_example" PRIVATE ${TARGET_NAME} pthread)


install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)
