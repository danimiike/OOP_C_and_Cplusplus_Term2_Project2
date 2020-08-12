/*!	\file		array_t.h
	\author		Using the example given in the classroom. Teacher: Garth Santor
	\date		2020-02-28

	Array abstract data type.
*/

#define _CRT_DEBUG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef double array_value_t;

typedef struct array_t_tag {
	array_value_t* data;
	size_t nSize;
	size_t nCapacity;
} array_t;

// function prototype (or signature)
array_t	array();	

bool arrayPushBack(array_t* pArray, array_value_t value);

void arrayFree(array_t* pArray);

void clearArray(array_t pArray);