#pragma once
#ifdef DYNAMICARRAY_EXPORTS 
#define DLLFUNC_C extern "C" __declspec(dllexport)
#else  
#define DLLFUNC_C extern "C" __declspec(dllimport)
#endif  


// Creates a new dynamic array. Each element of the array has size of sizeof_type.
// Returns a handle to the array.
DLLFUNC_C int darr_new(int sizeof_type);

// Returns the size of the dynamic array, in number of elements,
// or zero if the handle does not exist.
DLLFUNC_C int darr_size(int handle);

// Returns the size of each individual element,
// or zero if the handle does not exist.
DLLFUNC_C int darr_typesize(int handle);

// Pushes the input element to the back of the dynamic array.
// If the current 
// Returns the new size of the dynamic array, in number of elements,
// or zero if the handle does not exist.
DLLFUNC_C int darr_push_back(int handle, void* pElement);

// Returns a (temporary) pointer to element number nElement of the array,
// or NULL if the handle does not exist.
// The pointer should be assumed invalid once the array is resized or reserved.
DLLFUNC_C void* darr_pointer(int handle, int nElement);

// Resizes the array in terms of number of elements.  
// Behavior is similar to that of std::vector.
// Returns true if completed, false if handle not recognized.
DLLFUNC_C bool darr_resize(int handle, int nSize);

// Pre-allocates contiguous memory without changing the size of the dynamic array.
// Behavior is similar to that of std::vector.
// Returns true if completed, false if handle not recognized.
DLLFUNC_C bool darr_reserve(int handle, int nSize);

// De-allocates the dynamic vector from memory
// After this function, the handle will no longer be recognized.
// Returns true if completed, false if handle not recognized.
DLLFUNC_C bool darr_destroy(int handle);

