#include <stdio.h>	//Mert Sasmaz
#include <stdlib.h>

int main()
{
	char file[25] = "loremipsum.txt";
	char cr;
	int count = 0;
	FILE *fp;
	fp = fopen(file, "r");

	while ((cr=fgetc(fp)) != EOF)
	{
		if (cr == 'a')
			count++;
	}


	printf("Number of occurance of 'a' in the text file is: %d \n",  count);
	
	
return 0;
}
