# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${mltactoe_SOURCE_DIR}/include/mltactoe/*.h")
file(GLOB HEADER_PRIV_LIST CONFIGURE_DEPENDS "${mltactoe_SOURCE_DIR}/src/*.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(libmltactoe mltactoe.cpp ${HEADER_LIST} ${HEADER_PRIV_LIST}
  mltactoe-impl.cpp
  agent-human.cpp
  agent-ml.cpp
  agent-ml-impl.cpp)

# We need this directory, and users of our library will need it too
target_include_directories(libmltactoe PUBLIC ../include)

# All users of this library will need at least C++17
target_compile_features(libmltactoe PUBLIC cxx_std_17)

pkg_check_modules(MLPack REQUIRED mlpack)
target_link_libraries(libmltactoe ${MLPack_LIBRARIES})
target_include_directories(libmltactoe PUBLIC ${MLPack_INCLUDE_DIRS})
target_compile_options(libmltactoe PUBLIC ${MLPak_CFLAGS_OTHER})

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
