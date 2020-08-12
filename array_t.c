/*!	\file		array_t.c
	\author		Using the example given in the classroom. Teacher: Garth Santor
	\date		2020-02-28

	Array abstract data type.
*/

#include "array_t.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>

unsigned const DEFAULT_CAP = 8;
int const OK = 1;
int const FAIL = 0;
#ifdef _M_X64
void* const DBG_PTR = (void* const)0xcccccccccccccccc;
#else
void* const DBG_PTR = (void* const)0xcccccccc;
#endif

/* Make an empty array object. */
array_t array() {
	array_t arr;
	arr.data = NULL;
	arr.nCapacity = 0;
	arr.nSize = 0;
	return arr;
}

/*! \method		arrayPushBack
	\recieve	an array an a double value
	\return		boolean
	\Purpose	array push back adds an element to the end of the array.
				More memory is allocated if needed.*/

bool arrayPushBack(array_t* pArray, array_value_t value) {

	//esses dois asserts checam se o array existe e se é diferente de null. 
	assert(pArray != NULL && "pArray is NULL, should point to an array_t structure"); //the value of a string literal is true because it is an array and has value
	//assert library do.This function works to se if there is an array and if the array is null, if it is than an error will apears
	assert(pArray != DBG_PTR && "pArray has not been initialized");
	assert(pArray->data != DBG_PTR && "the array_t object has not been initialized, use array()");
	assert(pArray->nSize <= pArray->nCapacity && "Array size should never exceed capacity - corruption!");
	//Expand if necessary
	if (pArray->nCapacity == pArray->nSize)
	{
		size_t newCapacity = pArray->nCapacity * 2; //usually we double the capacity but if the capacity is 0 than
		if (newCapacity == 0) ++newCapacity; // make it one
		array_value_t* pNewBlock = realloc(pArray->data, newCapacity * sizeof(array_value_t));
		if (pNewBlock == NULL)
			return false;//if quit now the array will not change the capacity or create a new variable for it

		pArray->nCapacity = newCapacity;
		pArray->data = pNewBlock;

	}
	pArray->data[pArray->nSize++] = value;
	return true;
}


/*! \method		arrayFree
	\recieve	an array
	\return		void
	\Purpose	free the array and reebots the array to use it again.*/

void arrayFree(array_t* pArray)
{
	assert(pArray->nSize <= pArray->nCapacity && "Array size should never exceed capacity - corruption!");
	free(pArray->data);
	*pArray = array(); 

}
