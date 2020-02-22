#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"

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
	printf(1, "Start thread testing...\n");
	thread_create((void*(*)(void*))&print_1, 0);
	thread_join();
	thread_create((void*(*)(void*))&print_2, 0);
	thread_join();
	thread_create((void*(*)(void*))&print_3, 0);
	thread_join();
	
	exit();
}

