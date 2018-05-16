// DynamicArray.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dynamic.h"
#include <vector>
#include <deque>
typedef std::vector<char> v_char;
static int last_handle = 0;

class DArray
{
public:
	DArray(int sizeof_type) :
		handle(++last_handle),
		sizeof_type(sizeof_type)
	{
	}
	~DArray()
	{
	}
	int get_handle()
	{
		return handle;
	}
	int get_sizeof_type()
	{
		return sizeof_type;
	}
	v_char darray;
private:
	int handle;
	int sizeof_type;

};
std::deque<DArray> dq_da;


int da_new(int sizeof_type)
{
	try {
		if (sizeof_type <= 0) return 0;
		DArray da(sizeof_type);
		dq_da.push_back(da);
		return da.get_handle();
	}
	catch (...) { return 0; }
}
int da_size(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle) return (int)(da.darray.size() / da.get_sizeof_type());
		}
		return 0; // no matches
	}
	catch (...) { return 0; }
}
int da_capacity(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle) return (int)(da.darray.capacity() / da.get_sizeof_type());
		}
		return 0; // no matches
	}
	catch (...) { return 0; }
}
int da_typesize(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle) return da.get_sizeof_type();
		}
		return 0; // no matches
	}
	catch (...) { return 0; }
}
int da_push_back(int handle, void* pElement)
{
	return da_insert(handle, pElement, da_size(handle), 1);
}




void* da_data(int handle, int nElement)
{
	try {
		char *ptr0 = NULL, *ptrN = NULL;
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				ptr0 = da.darray.data();
				if (ptr0) ptrN = ptr0 + (nElement * da.get_sizeof_type());
			}
		}
		return (void*)ptrN;
	}
	catch (...) { return NULL; }

}
bool da_resize(int handle, int nSize)
{
	try {
		if(nSize < 0) return false;
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				da.darray.resize(nSize * da.get_sizeof_type());
				return true;
			}
		}
		return false;
	}
	catch (...) { return false; }

}
bool da_reserve(int handle, int nSize)
{
	try {
		if(nSize < 0) return false;
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				da.darray.reserve(da.get_sizeof_type() * nSize);
				return true;
			}
		}
		return false;
	}
	catch (...) { return false; }
}
bool da_delete(int handle)
{
	try {
		int i = 0;
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				dq_da.erase(dq_da.begin() + i);
				return true;
			}
			++i;
		}
		return false;
	}
	catch (...) { return false; }
}
void da_delete_all()
{
	try {
		dq_da.clear();
	}
	catch (...) { return; }
}

int da_insert(int handle, void* pElement, int nPosition, int numElements)
try {

	if (numElements <= 0) return 0;
	if (!pElement) return 0;

	char* pChar = (char*)pElement;
	for (auto& da : dq_da)
	{
		if (da.get_handle() == handle)
		{
			// check that position is valid: 
			// must be: 0 <= (nPosition * sizeof type) <= (size before operation)
			if (nPosition < 0) return 0;
			if ((nPosition * da.get_sizeof_type()) > (int)da.darray.size()) return 0;

			// make sure enough memory is allocated for the entire push back operation
			if (da.darray.capacity() < (da.darray.size() + (numElements * da.get_sizeof_type())))
				da.darray.reserve(da.darray.size() + (numElements * da.get_sizeof_type()));
			
			//// insert all bytes at the same time
			v_char::iterator it = da.darray.begin();
			it += nPosition * da.get_sizeof_type();

			da.darray.insert(it, (char*)pElement, (char*)pElement + (numElements * da.get_sizeof_type()));
			
			return (int)(da.darray.size() / da.get_sizeof_type());

		}
	}
	return 0; // fail case
}
catch (...) { return 0; }

bool da_shrink_to_fit(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (handle != da.get_handle()) continue;
			da.darray.shrink_to_fit();
			return true;
		}
		return false;
	}
	catch (...) { return false; }
}

int da_erase(int handle, int nPosition, int numElements)
{
	try
	{
		if (numElements <= 0) return 0;
		
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				// check that position is valid: 
				// must be: 0 <= (nPosition * sizeof type) <= (size before operation)
				if (nPosition < 0) return 0;
				if ((nPosition * da.get_sizeof_type()) > (int)da.darray.size()) return 0;

				// check that final element to be deleted is valid:
				// must be: 0 <= (nPosition * sizeof type) <= (size before operation)
				int nEnd = nPosition + numElements;
				if (nEnd < 0) return 0;
				if ((nEnd * da.get_sizeof_type()) > (int)da.darray.size()) return 0;


				// make sure enough memory is allocated for the entire push back operation
				if (da.darray.capacity() < (da.darray.size() + (numElements * da.get_sizeof_type())))
					da.darray.reserve(da.darray.size() + (numElements * da.get_sizeof_type()));

				v_char::iterator it = da.darray.begin();
				it += nPosition * da.get_sizeof_type();
				da.darray.erase(it, it + (numElements * da.get_sizeof_type()));

				//da.darray.insert(it, (char*)pElement, (char*)pElement + (numElements * da.get_sizeof_type()));

				return (int)(da.darray.size() / da.get_sizeof_type());

			}
		}
		return 0;
	}
	catch (...) { return 0; }
}

int da_pop_back(int handle)
{
	if(!da_size(handle)) return 0;
	return da_resize(handle, da_size(handle) - 1);
}

bool da_clear(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (handle != da.get_handle()) continue;
			da.darray.clear();
			return true;
		}
		return false;
	}
	catch (...) { return false; }
}

bool da_exists(int handle)
{
	if (da_typesize(handle)) return true;
	else return false;
}

bool da_is_empty(int handle)
{
	if (!da_exists(handle)) return false;
	else if (!da_size(handle)) return true;
	else return false;
}

int da_max_size(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (handle != da.get_handle()) continue;
			return (int)(da.darray.max_size() / da.get_sizeof_type());
		}
		return 0;
	}
	catch (...) { return 0; }
}

