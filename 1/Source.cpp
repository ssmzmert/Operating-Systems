#include<iostream>	//Mert Sasmaz CS307 HW1
#include<pthread.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

//Creating the matrix
const int row=2;
const int col=50;
int seatingplan[col][row];

bool finished = false;
int turn = 0;


//Prints the matrix
void print()
{
	for (int i=0; i<row; i++){
		for (int j=0; j<col; j++){
			cout << seatingplan[i][j];
		}
		cout << endl;
	}
}

//In order to change row and collumn number into numbers in between 1-100
int numberFunction(int row, int col)
{
	row++;
	col++;
	int number;
	if (row ==1)
		number = col;
	else if (row ==2)
		number = 50+col;

	return number;
}


void *travelAgencyOne(void*)
{
	while(!finished)
	{
		while (turn == 0)
		{
			int row1 = rand() % 2;	//To get a number between 1-2
			int col1 = rand() % 50;
			int number = numberFunction(row1, col1);
			bool reservation = false; //To check if the reservation is made. 
			if(seatingplan[row1][col1] != 1 && seatingplan[row1][col1] != 2)
			{
				cout << "Agency 1 Entered Critical Region" << endl;
				cout << "Seat Number " << number << " is reserved by Agency 1" << endl;
				seatingplan[row1][col1] = 1;
				reservation = true;
				cout << "Agency 1 Exit Critical Region" << endl << endl;
			}
			if(reservation)
				turn = 1;
		}
	}

	return 0;
}


void *travelAgencyTwo(void*)
{
	
	while(!finished)
	{

		while (turn == 1)
		{
			int row1 = rand() % 2;	//To get a number between 1-2
			int col1 = rand() % 50;
			int number = numberFunction(row1, col1);
			bool reservation = false; //To check if the reservation is made. 
			if(seatingplan[row1][col1] != 1 && seatingplan[row1][col1] != 2)
			{
				cout << "Agency 2 Entered Critical Region" << endl;
				cout << "Seat Number " << number << " is reserved by Agency 2" << endl;
				seatingplan[row1][col1] = 2;
				reservation = true;
				cout << "Agency 2 Exit Critical Region" << endl << endl;
			}
			if(reservation)
				turn = 0;
		}
	}

	return 0;
}


int main(){

	//initializes the matrix with 0s
	for (int i=0; i<row; i++){
		for (int j=0; j<col; j++){
			seatingplan[i][j]=0;
		}
	}

	//to generate random number each time.
	srand(time(NULL));

	pthread_t agency1;
	pthread_t agency2;

	pthread_create(&agency1, NULL, travelAgencyOne, NULL);
	pthread_create(&agency2, NULL, travelAgencyTwo, NULL);

	int counter = 0;
    while(!finished)
    {
        for(int i=0; i<2; i++)
            for(int j=0; j<50; j++)
                if(seatingplan[i][j] != 0)
                    counter++;
        
        if(counter == 100)
            finished = true;
        else
            counter = 0;
    }
	
	pthread_join(agency1, NULL);
	pthread_join(agency2, NULL);

	cout << endl << "Plane is full:" << endl << endl;
	print();

	return 0;
}