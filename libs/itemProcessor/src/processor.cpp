#include <itemProcessor/processor.h>

#include <condition_variable>
#include <future>
#include <queue>
#include <thread>

struct ItemProcessor::Pimpl {
  Pimpl() {
  }

  ~Pimpl() {
    setCompleted = true;
  }

  void processingThread() {
    while (!setCompleted || (setCompleted && !dataInput.empty())) {
      std::unique_lock<std::mutex> lk(mut);
      cond.wait(lk, [this] { return !dataInput.empty() || setCompleted; });

      if (dataInput.empty())
        break;

      auto data = dataInput.front();
      dataInput.pop();
      lk.unlock();

      std::this_thread::sleep_for(std::chrono::milliseconds(10));  // This represents the processing
      dataOutput.push_back(data);
    }
  }

  void reset() {
    {  // Empty input data to finish processing thread ASAP
      std::lock_guard<std::mutex> lk(mut);
      while (!dataInput.empty()) {
        dataInput.pop();
      }
    }
    if (future.valid()) {
      future.wait();
    }
    dataOutput.clear();
    setCompleted = false;
    futureInitialized = false;
  }

  void addItem(int item) {
    if (setCompleted) {
      throw std::runtime_error("need to call reset() before adding items");
    }

    if (!futureInitialized) {
      future = std::async(std::launch::async, &Pimpl::processingThread, this);
      futureInitialized = true;
    }

    std::lock_guard<std::mutex> lk(mut);
    dataInput.push(item);
    cond.notify_one();
  }

  void completeSet() {
    setCompleted = true;
    cond.notify_one();
  }

  const std::vector<int>& data() const {
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
  bool futureInitialized{false};
};

ItemProcessor::ItemProcessor() : _p(std::make_unique<Pimpl>()) {
}

ItemProcessor::~ItemProcessor() {
}

void ItemProcessor::reset() {
  _p->reset();
}

void ItemProcessor::addItem(int item) {
  _p->addItem(item);
}

void ItemProcessor::completeSet() {
  _p->completeSet();
}

const std::vector<int>& ItemProcessor::data() const {
  return _p->data();
}
