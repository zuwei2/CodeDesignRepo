#include "HashFunction.h"
namespace HashFunction
{
	// implementation of a basic addition hash
	unsigned int badHash(const char* data, unsigned int length)
	{
		unsigned int hash = 0; 
		for (unsigned int i = 0; i < length; ++i)
			hash += data[i]; 
		return hash;
	}

	// BKDR Hash
	unsigned int BKDRHash(unsigned char* data, unsigned int size)
	{
		unsigned int hash = 0;
		for (unsigned int i = 0; i < size; ++i)
		{
			hash = (hash * 1313) + data[i];
		}
		return(hash & 0x7FFFFFFF);
	}
}