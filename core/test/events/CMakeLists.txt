cmake_minimum_required(VERSION 3.0)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

include_directories(../lib/libledger-test/)

add_executable(ledger-core-events-tests main.cpp events_test.cpp)

target_link_libraries(ledger-core-events-tests gtest gtest_main)
target_link_libraries(ledger-core-events-tests ledger-core-static)
target_link_libraries(ledger-core-events-tests ledger-test)
include(CopyAndInstallImportedTargets)
if (SYS_OPENSSL)
    find_package(OpenSSL)
    if(WIN32)
        target_link_libraries( ledger-core-events-tests ws2_32 crypt32 )
    endif()
    copy_install_imported_targets(ledger-core-events-tests OpenSSL::Crypto uv)
else()
    copy_install_imported_targets(ledger-core-events-tests crypto uv)
endif()
add_test (NAME ledger-core-events-tests COMMAND ledger-core-events-tests)