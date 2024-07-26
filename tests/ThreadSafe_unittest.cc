#include <gtest/gtest.h>
#include <ThreadSafe.h>

#include "MockType.hh"

TEST(ThreadSafe, Constructor)
{
    ThreadSafe<MockType> object("hello world", std::vector<int>(), 0);

    MockType inner("hello world", std::vector<int>(), 0);
    EXPECT_EQ(inner, static_cast<MockType>(object));
}

TEST(ThreadSafe, Get)
{
    ThreadSafe<std::string> string("hello world");

    EXPECT_EQ(string.get(), "hello world");
}

TEST(ThreadSafe, Set)
{
    ThreadSafe<std::string> string;
    auto new_value = string.set("hello world");

    EXPECT_STREQ(new_value.c_str(), "hello world");
    EXPECT_EQ(string.get(), "hello world");
}

TEST(ThreadSafe, CastOperator)
{
    ThreadSafe<std::string> string("hello world");
    std::string native_string = string;

    EXPECT_EQ(native_string, string.get());
}

TEST(ThreadSafe, AccessWithFunction)
{
    ThreadSafe<std::string> string("hello world");
    std::string inner_value;

    string.access([&](std::string string)
                  { inner_value = string; });

    EXPECT_EQ(inner_value, string.get());
}

TEST(ThreadSafe, ApplyMutatingFunction)
{
    ThreadSafe<std::string> string("0");
    auto new_value = string.apply([](std::string &string)
                                  {
        string.pop_back();
        return string; });

    EXPECT_EQ(new_value, string.get());
    EXPECT_TRUE(new_value.empty());
}

TEST(ThreadSafe, Mutate)
{
    ThreadSafe<std::string> string("01");
    auto pop_back = [](std::string &string)
    { string.pop_back(); };

    string
        .mutate(pop_back)
        .mutate(pop_back);

    EXPECT_TRUE(string.get().empty());
}