set(TARGET_NAME EDITORDRAWING)

set(SRCS
  include/Item.hpp

  include/items/Circle.hpp
  include/items/Line.hpp
  include/items/Rectangle.hpp

  include/fillings/IFilling.hpp
  include/fillings/ContourFilling.hpp
)

set(LIBS_PRIV
)

set(LIBS_PUB
)

set(DIRS_PRIV
)

set(DIRS_PUB
)

add_library(${TARGET_NAME} INTERFACE ${SRCS})

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

