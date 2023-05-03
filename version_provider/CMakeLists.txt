set(TARGET_NAME VERSION_PROVIDER)

add_subdirectory(test)

configure_file(src/version.hpp.in src/version.hpp)

set(SRCS
  include/version_provider/VersionProvider.hpp
  src/VersionProviderImpl.hpp
  src/VersionProviderImpl.cpp
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

