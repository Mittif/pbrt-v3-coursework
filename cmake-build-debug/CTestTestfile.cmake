# CMake generated Testfile for 
# Source directory: /Users/mitty/Documents/GitHub/pbrt-v3-coursework
# Build directory: /Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pbrt_unit_test "pbrt_test")
set_tests_properties(pbrt_unit_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/CMakeLists.txt;559;ADD_TEST;/Users/mitty/Documents/GitHub/pbrt-v3-coursework/CMakeLists.txt;0;")
subdirs("src/ext/openexr")
subdirs("src/ext/glog")
subdirs("src/ext/ptex")
