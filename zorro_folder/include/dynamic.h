#ifndef windows_h
#include <windows.h>
#endif

// Creates a new dynamic array. Each element of the array has size of sizeof_type.
// Returns a handle to the array.
int __cdecl darr_new(int sizeof_type);
API(darr_new,DynamicArray)

// Returns the size of the dynamic array, in number of elements,
// or zero if the handle does not exist.
int __cdecl darr_size(int handle);
API(darr_size,DynamicArray)

// Returns the size of each individual element,
// or zero if the handle does not exist.
int __cdecl darr_typesize(int handle);
API(darr_typesize,DynamicArray)

// Pushes the input element to the back of the dynamic array.
// If the current 
// Returns the new size of the dynamic array, in number of elements,
// or zero if the handle does not exist.
int __cdecl darr_push_back(int handle, void* pElement);
API(darr_push_back,DynamicArray)

// Returns a (temporary) pointer to element number nElement of the array,
// or NULL if the handle does not exist.
// The pointer should be assumed invalid once the array is resized or reserved.
void* __cdecl darr_pointer(int handle, int nElement);
API(darr_pointer,DynamicArray)

// Resizes the array in terms of number of elements.  
// Behavior is similar to that of std::vector.
// Returns true if completed, false if handle not recognized.
bool __cdecl darr_resize(int handle, int nSize);
API(darr_resize,DynamicArray)

// Pre-allocates contiguous memory without changing the size of the dynamic array.
// Behavior is similar to that of std::vector.
// Returns true if completed, false if handle not recognized.
bool __cdecl darr_reserve(int handle, int nSize);
API(darr_reserve,DynamicArray)

// De-allocates the dynamic vector from memory
// After this function, the handle will no longer be recognized.
// Returns true if completed, false if handle not recognized.
bool __cdecl darr_destroy(int handle);
API(darr_destroy,DynamicArray)

// De-allocates **all** dynamic vectors from memory.
// After this function, **all handles** will no longer be recognized.
void __cdecl darr_destroy_all();
API(darr_destroy_all,DynamicArray)
