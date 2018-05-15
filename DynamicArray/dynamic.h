#pragma once
#ifndef dynamic_h
#define dynamic_h
#ifdef WIN32

#include<Windows.h>
#ifdef DYNAMICARRAY_EXPORTS 
#define DLLFUNC_C extern "C" __declspec(dllexport)
#else  
#define DLLFUNC_C extern "C" __declspec(dllimport)
#endif  
#define API(x,y)		// force ignorance
#define DynamicArray	// force ignorance
//#define __POINTER__ void*

#else // if Zorro Trading Automation
#include <windows.h>	// Zorro windows API header
//#define __POINTER__ void*
#define DLLFUNC_C		// force ignorance
#endif

// ** CREATION, EXISTENCE, AND DELETION **

// Creates a new dynamic array. Each element of the array has size of sizeof_type.
// Returns a handle to the array.
DLLFUNC_C int __cdecl da_new(int sizeof_type);
API(da_new,DynamicArray)

// Confirms the existence of a dynamic array.
DLLFUNC_C bool __cdecl da_exists(int handle);
API(da_exists, DynamicArray)

// De-allocates the dynamic vector from memory
// After this function, the handle will no longer be recognized.
// Returns true if completed, false if handle not recognized.
DLLFUNC_C bool __cdecl da_delete(int handle);
API(da_delete, DynamicArray)

// De-allocates **all** dynamic vectors from memory.
// After this function, **all handles** will no longer be recognized.
DLLFUNC_C void __cdecl da_delete_all();
API(da_delete_all, DynamicArray)

// ** SIZING **

// Returns the size of the dynamic array, in number of elements,
// or zero if the handle does not exist.
DLLFUNC_C int __cdecl da_size(int handle);
API(da_size, DynamicArray)

// Returns the capacity of the dynamic array, in number of elements,
// or zero if the handle does not exist.
DLLFUNC_C int __cdecl da_capacity(int handle);
API(da_capacity, DynamicArray)

// Returns the max number of elements the dynamic array is capable of holding,
// or zero if the handle does not exist.
DLLFUNC_C int __cdecl da_max_size(int handle);
API(da_max_size, DynamicArray)

// Returns true if an existing array is empty
// or false if either the array has elements or does not exist.
DLLFUNC_C bool __cdecl da_is_empty(int handle);
API(da_is_empty, DynamicArray)

// Returns the size of each individual element,
// or zero if the handle does not exist.
DLLFUNC_C int __cdecl da_typesize(int handle);
API(da_typesize, DynamicArray)

// Resizes the array in terms of number of elements.  
// Behavior is similar to that of std::vector.
// Returns true if completed, false if handle not recognized.
DLLFUNC_C bool __cdecl da_resize(int handle, int nSize);
API(da_resize, DynamicArray)

// Pre-allocates contiguous memory without changing the size of the dynamic array.
// Behavior is similar to that of std::vector.
// Returns true if completed, false if handle not recognized.
DLLFUNC_C bool __cdecl da_reserve(int handle, int nSize);
API(da_reserve, DynamicArray)

// At the STL implementation's discretion, the capacity will be reduced to the size.
// Behavior is similar to that of std::vector.
// handle: Dynamic array handle.
DLLFUNC_C bool __cdecl da_shrink_to_fit(int handle);
API(da_shrink_to_fit, DynamicArray)

// ** DATA ACCESS **

// Returns a (temporary) pointer to element number nElement of the array,
// or NULL if the handle does not exist,
// or NULL if the element number does not exist.
// Note: if size==0, no pointer can be returned.
// handle: Dynamic array handle.
// The pointer should be assumed invalid once the array is resized or reserved.
DLLFUNC_C void* __cdecl da_data(int handle, int nElement);
API(da_data, DynamicArray)

// ** ADD ELEMENTS **

// Pushes the input element to the back of the dynamic array.
// handle: Dynamic array handle.
// Returns the new size of the dynamic array, in number of elements,
// or zero if the handle does not exist.
//DLLFUNC_C int da_push_back(int handle, void* pElement);
DLLFUNC_C int __cdecl da_push_back(int handle, void* pElement);
API(da_push_back, DynamicArray)

// Inserts elements to a given position in the dynamic array.
// Behavior is similar to that of std::vector.
// handle: Dynameic array handle.
// pElement: Pointer to element or array of elements to be inserted.
// nPosition: Position where the new element(s) are to be placed,
//	          where 0 = front and size = back.
// numElements: Number of fixed-size elements to be inserted. Must be 1 or greater.
// Returns the new size if completed or zero if unsuccessful.
//DLLFUNC_C int da_insert(int handle, void* pElement, int nPosition, int numElements);
DLLFUNC_C int __cdecl da_insert(int handle, void* pElement, int nPosition, int numElements);
API(da_insert, DynamicArray)

// ** REMOVE ELEMENTS **

// Erases elements at a given position in the dynamic array.
// Behavior is similar to that of std::vector.
// handle: Dynamic array handle.
// nPosition: Position where the first element is to be erased,
//			  where 0 = front and size = back.
// numElements: Number of fixed-size elements to be deleted. Must be 1 or greater.
//				For example, nPosition = 2, numElements = 3 :: 2 thru 5 get deleted.
DLLFUNC_C int __cdecl da_erase(int handle, int nPosition, int numElements);
API(da_erase, DynamicArray)

// Removes the last element of the dynamic array.
// handle: Dynamic array handle.
// Returns the new size if completed or zero if unsuccessful.
DLLFUNC_C int __cdecl da_pop_back(int handle);
API(da_pop_back, DynamicArray)

// Clears the contents of the dynamic array.
// (The size become zero but not the capacity per se.)
// handle: Dynamic array handle.
// Returns true if successful or false if handle not recognized.
DLLFUNC_C bool __cdecl da_clear(int handle);
API(da_clear, DynamicArray)


#endif // dynamic_h