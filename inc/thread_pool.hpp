#pragma once

#include <thread>
#include <vector>

namespace otus {
  template <typename Function, typename... Args>
  class ThreadPool {
  public:
    ThreadPool(size_t size) { pool.reserve(size); }

    void run(Function &&func, Args &&...args) {
      pool.emplace_back(func, args...);
    }

    void join() { for (auto &thread: pool) thread.join(); }

  private:
    std::vector<std::thread> pool { };
  };
}
