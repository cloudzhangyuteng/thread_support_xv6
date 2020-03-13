#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "spinlock.h"

int n = 0;

struct semaphore {
	int value;
	int active;
	struct spinlock lock;
};


void* cnt(struct semaphore* sem)
{
	int i = 0;
	for (; i < 10000; i++)
	{
		sem_wait(sem);
		n++;
		sem_signal(sem);
	}
	
	return 0;
}

__attribute__((stdcall)) void* print_1(void* a)
{
	printf(1, "thread calling function 1\n");
	return 0;
}

__attribute__((stdcall)) void* print_2(void* a)
{
	printf(1, "thread calling function 2\n");
	//thread_create((void*(*)(void*))&print_1, 0);
	//thread_join();
	return 0;
}

__attribute__((stdcall)) void* print_3(void* a)
{
	printf(1, "thread calling function 3\n");
	return 0;
}

int main(int argc, char *argv[])
{
	printf(1, "Start thread creation testing...\n");
	int i;
	for (i = 0; i < 10; i++) {
		thread_create((void*(*)(void*))&print_1, 0);
		printf(1, "thread %d created successfully!\n", i+1);
		thread_join();
	}
	
	/*thread_create((void*(*)(void*))&print_1, 0);
	thread_join();
	thread_create((void*(*)(void*))&print_2, 0);
	thread_join();
	thread_create((void*(*)(void*))&print_3, 0);
	thread_join();*/
	
	printf(1, "\nStart semaphore testing...\n");
	struct semaphore sem;
	int value = 1;
	n = 0;
	sem_init(&sem, value);
	printf(1, "\nSemaphore initialized to %d\n", value);
	printf(1, "Value before increment: %d\n", n);
	printf(1, "Increment 10000 twice...\n");
	thread_create((void*(*)(void*))&cnt, &sem);
	thread_create((void*(*)(void*))&cnt, &sem);
	thread_join();
	thread_join();
	printf(1, "Value after increment: %d\n", n);
	
	exit();
}

