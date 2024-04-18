#include "spinlock.hpp"
#include "mcslock.hpp"
#include "test.hpp"

int main(int argc, char **argv) {
    int iters = 50000;
    testSpinLock(iters);
    testMCSLock(iters);
    return 0;
}