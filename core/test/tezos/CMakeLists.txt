cmake_minimum_required(VERSION 3.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(ledger-core-tezos-tests main.cpp address_test.cpp)

target_link_libraries(ledger-core-tezos-tests gtest gtest_main)
target_link_libraries(ledger-core-tezos-tests ledger-core-static)
target_link_libraries(ledger-core-tezos-tests ledger-test)
target_link_libraries(ledger-core-tezos-tests leveldb)
target_include_directories(ledger-core-tezos-tests PUBLIC ../../../core/lib/leveldb/include)
include_directories(../lib/libledger-test/)

include(CopyAndInstallImportedTargets)
if (SYS_OPENSSL)
    find_package(OpenSSL)
    if(WIN32)
        target_link_libraries( ledger-core-tezos-tests crypt32 ws2_32)
    endif()
    copy_install_imported_targets(ledger-core-tezos-tests OpenSSL::Crypto ledger-core)
else()
    copy_install_imported_targets(ledger-core-tezos-tests crypto ledger-core)
endif()
add_test (NAME ledger-core-tezos-tests COMMAND ledger-core-tezos-tests)
