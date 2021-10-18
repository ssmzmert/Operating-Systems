#include<iostream>	//Mert Sasmaz
#include <fstream>
#include <string>

using namespace std;

int main(){


	string line;
	char ch;
	int count = 0;
	ifstream myfile ("loremipsum.txt");

	if (myfile.is_open())
	{
		 while(myfile.get(ch)){
			 if (ch=='a')
				 count++;
		}
		myfile.close();
	 }
	else cout << "Unable to open file"; 


	cout << "Number of occurance of 'a' in the text file is: " << count<<endl;

	return 0;
}