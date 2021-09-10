#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char share_array test_clone[100];

int change_array(void* ptr) {
	char* array = (char*) ptr;
	for(int i = 0;i < 50;i ++)
		array[i] = i;
	return 0;
}

int check_array(void* ptr){
	char* array = (char*) ptr;
	for(int i = 0;i< 50;i ++){
		assert(array[i] == i);
	}
	return 0;
}

int main()
{
	memset(test_clone, 0, sizeof(test_clone));
	pthread_create(change_array, CLONE_VM, (void*) test_clone);
	sleep(50);
	pthread_create(check_array, CLONE_VM, (void*) test_clone);
	sleep(50);
	printf("Test Clone OK!!\n");
	return 0;
}
