#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "spinlock.h"
//#include <stdlib.h>

#define NUM_PLAYER 5

struct semaphore {
	int value;
	int active;
	struct spinlock lock;
};

struct semaphore sem;
int throw = 0;
int self;

// reference from https://stackoverflow.com/questions/1167253/implementation-of-rand
uint random(int range)
{
	static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
	unsigned int b;
	b  = ((z1 << 6) ^ z1) >> 13;
	z1 = ((z1 & 4294967294U) << 18) ^ b;
	b  = ((z2 << 2) ^ z2) >> 27; 
	z2 = ((z2 & 4294967288U) << 2) ^ b;
	b  = ((z3 << 13) ^ z3) >> 21;
	z3 = ((z3 & 4294967280U) << 7) ^ b;
	b  = ((z4 << 3) ^ z4) >> 12;
	z4 = ((z4 & 4294967168U) << 13) ^ b;
	return (z1 ^ z2 ^ z3 ^ z4)%range;
}

void player(void*);

int main(int argc, char *argv[])
{
	printf(1, "\nStart frisbee game\n\n");
	sem_init(&sem, 1);
	int i;
	
	for(i = 1; i <= NUM_PLAYER; i++) {
		thread_create((void*(*)(void*))&player, 0);
		thread_join();
		sleep(10);
	}
	
	sem_destroy(&sem);
	printf(1, "\nfirsbee game finished\n");
	
	exit();
}

void player(void *a) {	
	while(1) {
		self = random(NUM_PLAYER);
		if (self != throw)
			break;
	}
	
	if (self != throw) {
		sem_wait(&sem);
		printf(1, "pass frisbee\n");
		printf(1, "player %d caught frisbee from player%d\n\n", self, throw);
		throw = self;
		sem_signal(&sem);
	}
}
