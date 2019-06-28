#include <itemProcessor/processor.h>

#include <catch2/catch.hpp>

#include <thread>

TEST_CASE("ItemProcessor can be instantiated")
{
    CHECK_NOTHROW(ItemProcessor());
}

TEST_CASE("ItemProcessor is destroyed gracefully when thread is processing data")
{
    ItemProcessor processor;
    processor.addItem(5);
}

TEST_CASE("ItemProcessor::data() returns empty vector if no data has been appended")
{
    ItemProcessor processor;
    CHECK(processor.data().empty());
}

TEST_CASE("ItemProcessor::data() throws if we call it before completing the set")
{
    ItemProcessor processor;
    processor.addItem(5);
    CHECK_THROWS_AS(processor.data(), std::runtime_error);
}

TEST_CASE("ItemProcessor::data() returns data when we complete the set")
{
    const std::vector<int> data{5, 10, 15};
    ItemProcessor processor;

    std::for_each(begin(data), end(data), [&processor](int d) {
        processor.addItem(d);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    });
    processor.completeSet();

    CHECK(processor.data() == data);
}

TEST_CASE("ItemProcessor can process more than 1 batch of items")
{
    const std::vector<int> data{5, 10, 15};
    ItemProcessor processor;

    for (size_t i = 0; i < 3; ++i) {
        std::for_each(begin(data), end(data), [&processor](int d) {
            processor.addItem(d);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        });
        processor.completeSet();
        CHECK(processor.data() == data);
    }
}
