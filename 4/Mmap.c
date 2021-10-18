#include <stdio.h>	//Mert Sasmaz
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

	int fd = open("loremipsum.txt", O_RDONLY);
	int count = 0, i;
	struct stat s;
	size_t size;
	int status = fstat(fd, &s);
	size = s.st_size;
	char *ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (ptr == MAP_FAILED){
		printf("Failed");
		return 1;
	}
	while(i<size){
		if(ptr[i]=='a')
			count++;
		i++;
	}


	close(fd);
	printf("Number of occurance of 'a' in the text file is: %d", count);

	status = munmap(ptr,size);
	return 0;
}