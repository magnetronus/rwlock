#include <stdint.h>

#include "rwlock.h"

void rwlock_init(rwlock_t *lock)
{
	atomic_init(lock, 0);
}

void rwlock_rdlock(rwlock_t *lock)
{
	int32_t _lock;

	do {
		_lock = atomic_load(lock);
	} while (!(_lock < 0) && !atomic_compare_exchange_weak(lock, &_lock, _lock + 1));
}

bool rwlock_tryrdlock(rwlock_t *lock)
{
	int32_t _lock = atomic_load(lock);

	return !(_lock < 0) && atomic_compare_exchange_weak(lock, &_lock, _lock + 1);
}

void rwlock_rdunlock(rwlock_t *lock)
{
	int32_t _lock;

	do {
		_lock = atomic_load(lock);
	} while (!atomic_compare_exchange_weak(lock, &_lock, _lock - 1));
}

void rwlock_wrlock(rwlock_t *lock)
{
	int32_t _lock = 0;

	while (!atomic_compare_exchange_weak(lock, &_lock, -1));
}

bool rwlock_trywrlock(rwlock_t *lock)
{
	int32_t _lock = 0;

	return atomic_compare_exchange_weak(lock, &_lock, -1);
}

void rwlock_wrunlock(rwlock_t *lock)
{
	int32_t _lock = -1;

	while (!atomic_compare_exchange_weak(lock, &_lock, 0));
}
