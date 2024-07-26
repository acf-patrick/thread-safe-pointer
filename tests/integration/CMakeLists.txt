add_executable(ThreadSafe_integration_test ThreadSafe.cc)

target_link_libraries(
    ThreadSafe_integration_test
    PRIVATE
    ThreadSafeTypes
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ThreadSafe_integration_test)