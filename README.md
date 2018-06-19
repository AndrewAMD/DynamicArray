# DynamicArray

This is a basic library that allows one to easily create dynamic arrays using a C interface.  Actually, it was intended as a DLL plug-in for Zorro Trading Automation.  The backend was written in Win32 C++17 using Visual Studio. Its only dependency is the STL library.

## Build Instructions

Currently, the library is meant to be built in Visual Studio 2017, though it should not be hard to recycle the core code for UNIX.

To build a DLL for Zorro, simply open the solution file, and build in the Release/x86 mode.
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
