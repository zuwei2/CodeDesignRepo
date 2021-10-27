#include <iostream>
#include "HashFunction.h"
#include "HashTable.h"

int main()
{
	// Create hash table with 3 elements:
	HashTable ht(5);

	// Declare the data to be stored in the hash table
	unsigned char* my_arr[] = {(unsigned char*)"hello", (unsigned char*)"nyrtbdra ", (unsigned char*)"vpwqkejm", (unsigned char*)"seufi0jj", (unsigned char*)"asdasdsad"};

	// Insert all data declared into hashtable
	for (int i = 0; i < ht.GetTotalElement(); i++)
	{
		ht.insert_element(my_arr[i]);
	}
	ht.remove_element((unsigned char*)"hello");

	ht.print_all();

	system("pause");
}
