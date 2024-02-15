# Tests need to be added as executables first
add_executable(testlib mltactoe-test.cpp)

# I'm using C++17 in the test
target_compile_features(testlib PRIVATE cxx_std_17)

# We need this directory, and users of our library will need it too
target_include_directories(testlib PUBLIC ../include)

# Should be linked to the main library, as well as the gtest testing library
target_link_libraries(testlib PRIVATE libmltactoe gtest)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testlibtest COMMAND testlib) # Command can be a target
