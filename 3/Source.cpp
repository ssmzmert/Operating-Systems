#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h> 
#include <queue> 
#include <semaphore.h>
using namespace std;

#define NUM_THREADS 10
#define MEMORY_SIZE 150

struct node
{
	int id;
	int size;
};


queue<node> myqueue; // shared que
pthread_mutex_t sharedLock = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_t server; // server thread handle
sem_t semlist[NUM_THREADS]; // thread semaphores

int thread_message[NUM_THREADS]; // thread memory information
char  memory[MEMORY_SIZE]; // memory size
int  thread_id[NUM_THREADS];




void my_malloc(int thread_id, int size)
{
	//This function will add the struct to the queue
	pthread_mutex_lock(&sharedLock); //lock
	node str;
	str.id=thread_id;
	str.size=size;
	myqueue.push(str); //adds to the queue
	pthread_mutex_unlock(&sharedLock); //unlock

}

void * server_function(void *)
{
	//This function should grant or decline a thread depending on memory size.
	int index=0;
	
	bool server_run = true;

	while(server_run)  //THIS MUST RUN IN A LOOP AS LONG AS PROGRAM RUNS.
	{

		if(!myqueue.empty())
		{
			node str = myqueue.front();
			myqueue.pop();
			
			if(str.size<MEMORY_SIZE-index) //allocate memory 
			{
				thread_message[str.id] = index;
				index = index + str.size + 1;
			}
			else
			{				
				thread_message[str.id] = -1;//if not enough then -1		
			}


			sem_post(&(semlist[str.id])); //up
		}
	}
	return NULL;
}

void * thread_function(void * id) 
{
	//This function will create a random size, and call my_malloc
	//Block
	int * my_thread = (int*) id;
	int size = rand() % ((MEMORY_SIZE / 6)+1);

	my_malloc(*my_thread, size);

	sem_wait(&(semlist[*my_thread])); // down
	//pthread_mutex_lock(&sharedLock); //lock

	
	if(thread_message[*my_thread]== -1)
	{
		 printf("Thread %d: Not enough memory \n", *my_thread);
	}
	else
	{
		if(*my_thread==0)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '0';}
		}
		else if(*my_thread==1)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '1';}
		}
		else if(*my_thread==2)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '2';}
		}
		else if(*my_thread==3)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '3';}
		}
		else if(*my_thread==4)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '4';}
		}
		else if(*my_thread==5)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '5';}
		}
		else if(*my_thread==6)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '6';}
		}
		else if(*my_thread==7)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '7';}
		}
		else if(*my_thread==8)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '8';}
		}
		else if(*my_thread==9)
		{
			for (int i=0; i <= size; i++){
			memory[thread_message[*my_thread]+i] = '9';}
		}

		
	} 	//Then fill the memory with id's or give an error prompt
	
	//pthread_mutex_unlock(&sharedLock); //unlock
	
	return NULL;
}

void init()	 
{
	pthread_mutex_lock(&sharedLock);	//lock
	for(int i = 0; i < NUM_THREADS; i++) //initialize semaphores
	{sem_init(&semlist[i],0,0);}
	for (int i = 0; i < MEMORY_SIZE; i++)	//initialize memory 
  	{char zero = '0'; memory[i] = zero;}
   	pthread_create(&server,NULL,server_function,NULL); //start server 
	pthread_mutex_unlock(&sharedLock); //unlock
}



void dump_memory() 
{
 // You need to print the whole memory array here.
	for(int i=0; i<MEMORY_SIZE; i++)
	{
		cout << memory[i];
	}
}

int main (int argc, char *argv[])
 {

 	//You need to create a thread ID array here
	
	for(int i=0; i<NUM_THREADS;i++)
	{
		thread_id[i] = i;
	}

 	init();	// call init

 	//You need to create threads with using thread ID array, using pthread_create()
	pthread_t id[NUM_THREADS];
	for(int i=0; i<NUM_THREADS; i++)
	{
		pthread_create(&id[i], NULL, &thread_function, (void*)&thread_id[i]);
	}

 	//You need to join the threads
	for(int i=0; i<NUM_THREADS; i++)
	{
		pthread_join(id[i],NULL);
	}
	//pthread_join(server,NULL);

 	dump_memory(); // this will print out the memory
 	
 	printf("\nMemory Indexes:\n" );
 	for (int i = 0; i < NUM_THREADS; i++)
 	{
 		printf("[%d]" ,thread_message[i]); // this will print out the memory indexes
 	}
 	printf("\nTerminating...\n");

	return 0;
 }