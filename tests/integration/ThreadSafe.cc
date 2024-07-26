#include <gtest/gtest.h>
#include <ThreadSafe.h>
#include <thread>

TEST(ThreadSafe, AccessConcurrentlyModifiedData)
{
    int scrapped = 0;
    ThreadSafe sharedData(0);

    std::thread threads[] = {
        std::thread([&]()
                    {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            scrapped = sharedData.get(); }),
        std::thread([&]()
                    { sharedData.set(1); })};

    for (auto& thread: threads) {
        thread.join();
    }

    EXPECT_EQ(sharedData.get(), scrapped);
    EXPECT_EQ(scrapped, 1);
}

TEST(ThreadSafe, MutateDataConcurrently)
{
    ThreadSafe data(0);

    std::thread threads[] = {
        std::thread([&]() {
            data.set(1);
        }),
        std::thread([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            data.set(2);
        })
    };

    threads[0].join();
    EXPECT_EQ(data.get(), 1);
    threads[1].join();
    EXPECT_EQ(data.get(), 2);
}