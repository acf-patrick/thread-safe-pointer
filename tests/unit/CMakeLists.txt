add_executable(ThreadSafe_unit_test ThreadSafe.cc)

target_link_libraries(
    ThreadSafe_unit_test
    PRIVATE
    ThreadSafeTypes
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ThreadSafe_unit_test)