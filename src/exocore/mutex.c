#include "exocore/atomics.h"
#include "exocore/machine.h"
#include "exocore/mutex.h"

void mutex_acquire(mutex_t* mutex)
{
    do
    {
        while (atomic_load(&mutex->locked))
            spin_pause();
    }
    while (atomic_test_and_set(&mutex->locked));
}

void mutex_release(mutex_t* mutex)
{
    atomic_clear(&mutex->locked);
}

bool mutex_locked(mutex_t* mutex)
{
    return atomic_load(&mutex->locked);
}
