#include <itemProcessor/processor.h>

#include <condition_variable>
#include <future>
#include <queue>
#include <thread>

struct ItemProcessor::Pimpl {
    Pimpl() {}

    ~Pimpl()
    {
        setCompleted = true;
//        if (future.valid()) {
//            future.wait();
//        }
    }

    void processingThread()
    {
        while (!setCompleted || !dataInput.empty()) {
            std::unique_lock<std::mutex> lk(mut);
            cond.wait(lk, [this] { return !dataInput.empty(); });

            auto data=dataInput.front();
            dataInput.pop();
            lk.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // This represents the processing
            dataOutput.push_back(data);
        }
    }

    void startProcessing(int item)
    {
        if (setCompleted) {
            dataOutput.clear(); // This could happen with a reset() call
            setCompleted = false;
            future = std::async(std::launch::async, &Pimpl::processingThread, this);
        }
        std::lock_guard<std::mutex> lk(mut);
        dataInput.push(item);
        cond.notify_one();
    }

    void completeSet()
    {
        setCompleted = true;
    }

    const std::vector<int>& data() const
    {
        if (!setCompleted) {
            throw std::runtime_error("Impossible to access the data yet");
        }
        if (future.valid()) {
            future.wait();
        }
        return dataOutput;
    }

    std::mutex mut;
    std::future<void> future;
    std::condition_variable cond;
    std::queue<int> dataInput;
    std::vector<int> dataOutput;

    bool setCompleted{true};
};

ItemProcessor::ItemProcessor()
    : _p(std::make_unique<Pimpl>())
{
}

ItemProcessor::~ItemProcessor() {}

void ItemProcessor::addItem(int item)
{
    _p->startProcessing(item);
}

void ItemProcessor::completeSet()
{
    _p->completeSet();
}

const std::vector<int>& ItemProcessor::data() const
{
    return _p->data();
}
