#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include "sort.h"
using namespace std;

/******* If you change the file in line 23, change the type in line 15 appropriately.*******
	
			"phonenumber.txt" : int type //#data: 783268
			"primes_1million.txt" : int type //#data: 1000000
			"X_test.txt" : float type // #data: 1653268
		
***************************************************************************************/
typedef float element;
void fileWriting(char* filename, element* data, int cnt);

int main(int argc, char** argv) {
	
	element *data = new element[1653270]; // Sized to accommodate the number of data in "X_test" where the most data exists
	int size = 0;

	char filename[30]= "data/primes_1million.txt";
	ifstream file(filename, ios::in);
	if(!file) cout << "Failed to open input file" << endl;
	while(!file.eof()) {
		if(!file.eof()) {
			file >> data[size];
			size++;
		}
	}
	file.close();

	clock_t start, finish;
	start = clock();
	

	/* Check by uncommenting the sort you want to check.*/
	//insertionsort<element>(data, size);
	//selectionsort<element>(data, size);
	//bubblesort<element>(data, size);
	//mergesort<element>(data, 0, size - 1);
	//mergesort_sequential<element>(data,size);
	//quicksort<element>(data, 0, size - 1);
	//quicksort_sequential<element>(data, 0, size - 1);
	heapsort<element>(data, size);
	
	finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "Sorting time: " << duration << endl;

	/* Checking by writing to a file that it is properly aligned */
	char outputFilename[25] = "Sort.txt";
	fileWriting(outputFilename, data, size);
	delete[] data;		
	return 0;
}

void fileWriting(char* filename, element* data, int cnt) {
	fstream file;
	file.open(filename, ios::out);
	if (!file) cout << "Failed to open output file" <<endl; 
	for (int i = 0; i < cnt; ++i) {
		file << data[i] << endl;
	}
	file.close();
}
