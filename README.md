# Thread Synchronization Primitives
Implementations of spinlocks, queueing locks, etc.

## Spin Lock
Threads try to set a shared atomic flag to TRUE. If the flag is already TRUE, they retry until they succeed. This lock is simple, and efficient when contention is low. However, they are unfair because the thread owning the lock is the most likely to succeed if it immediately tries to grab the lock again, because the timing lines up well by definition.

## MCS Lock
This lock imposes first-come-first-served fairness through a linked-list-based queue. When threads attempt to grab the lock, they are placed in the queue and must spin on their personal atomic flag. When releasing the lock, the thread changes the next thread's flag to tell it to go ahead and take the lock next. Spinning on personal flags has the added benefit of reducing network contention.