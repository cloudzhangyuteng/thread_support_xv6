#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "spinlock.h"

int n;

struct semaphore {
	int value;
	int active;
	struct spinlock lock;
};


void* cnt(struct semaphore* sem)
{
	int i = 0;
	for (; i < 100; i++)
	{
		sem_wait(sem);
		n++;
		sem_signal(sem);
	}
	
	return 0;
}

__attribute__((stdcall)) void* print_1(void* a)
{
	printf(1, "create thread from print_1\n");
	return 0;
}

__attribute__((stdcall)) void* print_2(void* a)
{
	printf(1, "create thread from print_2\n");
	return 0;
}

__attribute__((stdcall)) void* print_3(void* a)
{
	printf(1, "create thread from print_3\n");
	return 0;
}

int main(int argc, char *argv[])
{
	printf(1, "\nStart thread testing...\n");
	thread_create((void*(*)(void*))&print_1, 0);
	thread_join();
	thread_create((void*(*)(void*))&print_2, 0);
	thread_join();
	thread_create((void*(*)(void*))&print_3, 0);
	thread_join();
	
	printf(1, "\nStart semaphore testing...\n");
	struct semaphore sem;
	int value = 1;
	sem_init(&sem, value);
	printf(1, "Semaphore initialized to %d\n", value);
	printf(1, "Value before increment: %d\n", n);
	printf(1, "Increment 100 twice...\n");
	thread_create((void*(*)(void*))&cnt, &sem);
	thread_create((void*(*)(void*))&cnt, &sem);
	thread_join();
	thread_join();
	printf(1, "Value after increment: %d\n", n);
	
	exit();
}

