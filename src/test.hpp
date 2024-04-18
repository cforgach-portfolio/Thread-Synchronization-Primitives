#pragma once

#include <iostream>
#include <chrono>
#include "omp.h"
#include "spinlock.hpp"
#include "mcslock.hpp"

void testSpinLock(int iters = 50000) {
    SpinLock lock;
    int ctr = 0;
    chrono::time_point t1 = chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i=0; i < iters; i += 1) {
        lock.lock();
        ctr += 1;
        lock.unlock();
    }

    chrono::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration t = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
    printf("Spinlock:   ctr: %i   time: %ld ns\n", ctr, t.count());
}

void testMCSLock(int iters = 50000) {
    MCSLock lock;
    Node p;
    int ctr = 0;
    chrono::time_point t1 = chrono::high_resolution_clock::now();

    #pragma omp parallel for private(p)
    for (int i=0; i < iters; i += 1) {
        lock.lock(&p);
        ctr += 1;
        lock.unlock(&p);
    }

    chrono::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration t = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
    printf("MCS Lock:   ctr: %i   time: %ld ns\n", ctr, t.count());
}