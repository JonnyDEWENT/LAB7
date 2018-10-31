#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int initialData = 10;
static int uninitialData;

int stack1(int i, int j){
	printf("%d: %p\n", i, &i);
	printf("%d: %p\n", j, &j);

	char *heap = malloc(sizeof(char));
	printf("\nHEAP1: %p\n", heap);
	heap = malloc(sizeof(char));
	printf("\nHEAP2: %p\n", heap);
    return 1;
}

int main()
{
    char *stackA = malloc(sizeof(char));
    char *stackB = malloc(sizeof(char));
    stack1(1,2);
    
	printf("Initial: %p\n", &initialData);
	printf("Uninitial: %p\n", &uninitialData);
    
	printf("SA: %p\n", &stackA);
	printf("SB: %p\n", &stackB);

	printf("HA: %p\n", stackA);
	printf("HB: %p\n", stackB);
	
	printf("\nPID: %d\n", getpid());
    
	pause();
    return 1;
}
