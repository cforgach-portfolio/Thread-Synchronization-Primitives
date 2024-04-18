#pragma once

#include <atomic>

using namespace std;

struct Node {
    atomic<bool> wait;
    atomic<Node *> next;
    Node() : wait(false), next(nullptr) {}
};

class MCSLock {
    atomic<Node *> tail;

public:
    MCSLock() : tail(nullptr) {}

    void lock(Node *p) {
        p->wait = true;
        p->next = nullptr;

        Node *prev = tail.exchange(p);  // #1
        if (prev) {
            prev->next = p;             // #2
            while (p->wait);
        }
    }

    void unlock(Node *p) {
        Node *next = p->next;

        if (!next) {
            Node *expected = p;
            if (tail.compare_exchange_strong(expected, nullptr))
                return;

            // We may reach here if another thread is between #1 and #2 in lock()
            while (!next)
                next = p->next;
        }

        next->wait = false;
    }
};