# Define a list of executables
set(EXECUTABLES trainer player ai_players)

# Loop over each executable
foreach(EXECUTABLE ${EXECUTABLES})
  # Add executable
  add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)

  # Set include directories
  target_include_directories(${EXECUTABLE} PRIVATE ../include)

  # Link libraries
  target_link_libraries(${EXECUTABLE} PRIVATE libmltactoe ${MLPack_LIBRARIES})

  # Set compile features
  target_compile_features(${EXECUTABLE} PRIVATE cxx_std_17)
endforeach()
