include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(unit)
add_subdirectory(integration)