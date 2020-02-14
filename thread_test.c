#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"

__attribute__((stdcall)) void* print_1(void* a)
{
	printf(1, "Hello\n");
	return 0;
}

void* print_2(void* a)
{
	printf(1, "Hello World\n");
	return 0;
}

void* print_3(void* a)
{
	printf(1, "123456789\n");
	return 0;
}

int main(int argc, char *argv[])
{
	printf(1, "Start thread testing...\n");
	thread_create((void*(*)(void*))&print_1, 0);
	
	exit();
}

