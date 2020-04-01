#pragma once
#include <stdatomic.h>
#include <stdbool.h>

/*
 *
 * For a reader:
 * 	- Taking a reader lock - from (*lock_ptr >= 0) to (*lock_ptr + 1)
 * 	- Releasing a reader lock - from (*lock_ptr > 0) to (*lock_ptr - 1)
 *
 *
 * For a writer:
 * 	- Taking a writer lock - from (*lock_ptr = 0) to (*lock_ptr = -1)
 * 	- Releasing a writer lock - from (*lock_ptr = -1) to (*lock_ptr = 0)
 *
 */

typedef atomic_int_fast32_t rwlock_t;

void rwlock_init(rwlock_t *lock);

void rwlock_rdlock(rwlock_t *lock);

bool rwlock_tryrdlock(rwlock_t *lock);

void rwlock_rdunlock(rwlock_t *lock);

void rwlock_wrlock(rwlock_t *lock);

bool rwlock_trywrlock(rwlock_t *lock);

void rwlock_wrunlock(rwlock_t *lock);
