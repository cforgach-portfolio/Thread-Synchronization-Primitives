#pragma once

#include <atomic>

using namespace std;

class SpinLock {
    atomic<bool> latch;

public:
    SpinLock() : latch(false) {}

    void lock() {
        bool expected = false;
        while (!latch.compare_exchange_weak(expected, true, memory_order_acquire))
            expected = false;
    }

    void unlock() {
        latch.store(false, memory_order_release);
    }
};