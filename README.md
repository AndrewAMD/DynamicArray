# DynamicArray

This is a basic library that allows one to easily create dynamic arrays using a C interface.  Actually, it was intended as a DLL plug-in for Zorro Trading Automation.  The backend was written in Win32 C++17 using Visual Studio. Its only dependency is the STL library.

## What This Library Does

* A dynamic array is basically the equivalent of a C++ std::vector.
* Dynamic arrays can be created, modified, and deleted from memory.
* When you create an array, you define its element size permanently. (For example, sizeof(int) for a dynamic array of ints, or sizeof(STRUCTNAME) for an array of STRUCTNAMEs.)
* You can track an array with a handler, returned from da_new().
* You are advised to delete any dynamic array no longer needed.  Simply call da_delete(h), where **h** is the handler.
* You also have the option of clearing **all** dynamic arrays.  Simply call da_delete_all().  It will clear all dynamic arrays from the stack, no exceptions.
* All of the remaining functions are simply wrappers for the std::vector library.  You can insert elements or arrays of elements at any location in a given dynamic array.
* All of the individual functions are documented in detail in the include/dynamic.h file.

## Build Instructions

Currently, the library is meant to be built in Visual Studio 2017, though it should not be hard to recycle the core code for UNIX, since it only depends on the STL library.

To build a DLL for Zorro, simply open the solution file, and build in the Release/x86 mode.

## Zorro Installation Instructions

To install DynamicArray in Zorro, the procedure is simple:
1. Build DynamicArray.dll
2. Copy the newly built DynamicArray.dll to your Zorro folder.
3. Copy dynamic.h to your Zorro/include folder.
4. Optionally, copy Zorro/Dynamic.c to your Zorro/Strategy folder.  This script demonstrates the functionality of the library.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
