#pragma once
#include <iostream>
#include <list>
#include "HashFunction.h"

class HashTable
{
private:
	std::list<unsigned char*>* table;
	int total_elements;

	int get_hash(unsigned char* key)
	{
		return (HashFunction::BKDRHash(key, total_elements)) % total_elements;
	}

public:
	const int GetTotalElement()
	{
		return total_elements;
	}

	// constructor
	HashTable(int n)
	{
		total_elements = n;
		table = new std::list<unsigned char*>[total_elements];
	}

	// insert data in hash table
	void insert_element(unsigned char* key)
	{
		int temp_hash = get_hash(key);
		// check if already a value in element
		if (!table[temp_hash].empty()) // if occupied
		{
			// iterate through table
			for (int i = 0; i < total_elements; i++)
			{
				// if spot empty, place there
				if (table[i].empty())
				{
					table[i].push_back(key);
					return;
				}
			}
		}
		else
		{
			table[temp_hash].push_back(key);
		}
	}

	// remove data in hash table
	void remove_element(unsigned char* key)
	{
		int x = get_hash(key);
		std::list<unsigned char*>::iterator i;
		for (i = table[x].begin(); i != table[x].end(); i++) {
			// Check if the iterator points to the required item:
			if (*i == key)
				break;
		}

		// If the item was found in the list, then delete it:
		if (i != table[x].end())
			table[x].erase(i);


	}

	void print_all()
	{
		// Traverse each index:
		for (int i = 0; i < total_elements; i++)
		{
			std::cout << "Index " << i << ": ";
			// Traverse the list at current index:
			for (unsigned char* j : table[i])
				std::cout << j << " => ";

			std::cout << std::endl;
		}
	}

};


