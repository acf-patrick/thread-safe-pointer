include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ThreadSafe_test ThreadSafe_unittest.cc)

target_link_libraries(
    ThreadSafe_test
    PRIVATE
    ThreadSafeTypes
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ThreadSafe_test)