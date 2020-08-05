#pragma once

#include <thread>
#include <vector>

namespace otus {
  template <typename Function>
  class ThreadPool {
  public:
    ThreadPool(size_t size) { pool.reserve(size); }

    void run(Function func) { pool.emplace_back(func); }

    void join() { for (auto &thread: pool) thread.join(); }

  private:
    std::vector<std::thread> pool { };
  };
}
