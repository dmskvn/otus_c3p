# CMake generated Testfile for 
# Source directory: /home/denis/study/otus/c3p/repo/otus_c3p
# Build directory: /home/denis/study/otus/c3p/repo/otus_c3p/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(VERSION_PROVIDER_TEST "version_provider/test/VERSION_PROVIDER_TEST")
set_tests_properties(VERSION_PROVIDER_TEST PROPERTIES  _BACKTRACE_TRIPLES "/home/denis/study/otus/c3p/repo/otus_c3p/CMakeLists.txt;23;add_test;/home/denis/study/otus/c3p/repo/otus_c3p/CMakeLists.txt;0;")
subdirs("allocator")
subdirs("version_provider")
subdirs("ip_filter")
