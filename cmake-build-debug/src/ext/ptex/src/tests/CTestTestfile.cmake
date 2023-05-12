# CMake generated Testfile for 
# Source directory: /Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests
# Build directory: /Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug/src/ext/ptex/src/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(wtest "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug/src/ext/ptex/src/tests/wtest")
set_tests_properties(wtest PROPERTIES  _BACKTRACE_TRIPLES "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;32;add_test;/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;0;")
add_test(rtest "/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake" "-DOUT=/Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug/src/ext/ptex/src/tests/rtest.out" "-DDATA=/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/rtestok.dat" "-DCMD=/Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug/src/ext/ptex/src/tests/rtest" "-P" "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/compare_test.cmake")
set_tests_properties(rtest PROPERTIES  _BACKTRACE_TRIPLES "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;23;add_test;/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;33;add_compare_test;/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;0;")
add_test(ftest "/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake" "-DOUT=/Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug/src/ext/ptex/src/tests/ftest.out" "-DDATA=/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/ftestok.dat" "-DCMD=/Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug/src/ext/ptex/src/tests/ftest" "-P" "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/compare_test.cmake")
set_tests_properties(ftest PROPERTIES  _BACKTRACE_TRIPLES "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;23;add_test;/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;34;add_compare_test;/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;0;")
add_test(halftest "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/cmake-build-debug/src/ext/ptex/src/tests/halftest")
set_tests_properties(halftest PROPERTIES  _BACKTRACE_TRIPLES "/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;35;add_test;/Users/mitty/Documents/GitHub/pbrt-v3-coursework/src/ext/ptex/src/tests/CMakeLists.txt;0;")
