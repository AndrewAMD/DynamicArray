#include <dynamic.h>

// demo #1: Demonstrates usage of dynamic arrays with an EXAMPLE struct.
void demo1();

// demo #2: Analyze a dynamic array of ints and its memory allocations.
void demo2();

// Helper function for demonstration purposes only.  It will print:
// 1) The address of the initial data pointer (at the beginning of the contiguous array),
// 2) The individual int element values, and
// 3) The size and capacity of the array.
// print int dy-array
void pr_int(int handle);

int main()
{
	da_delete_all();  // probably wise to run this at the beginning of every script, on INITRUN or main only.
	demo1();
	demo2();
	return 0;
}


// EXAMPLE struct used in demo #1.
typedef struct
{
	bool a;
	int b;
	char c[32];
	double d;

} EXAMPLE;


void demo1()
{
	printf("\n%d",sizeof(char));
	printf("\n%d",sizeof(EXAMPLE));
	
	int h = da_new(sizeof(EXAMPLE));
	
	// declare four blank structs
	EXAMPLE e1, e2; // single structs
	EXAMPLE ea[2];  // array of two structs
	memset(&e1, 0, sizeof(EXAMPLE));
	memset(&e2, 0, sizeof(EXAMPLE));
	memset(ea, 0, 2 * sizeof(EXAMPLE));
	
	// fill the structs with values
	e1.a = true; e1.b = 20; strcpy(e1.c,"banana"); e1.d = 24.5;
	e2.a = false; e2.b = -50; strcpy(e2.c,"orange"); e2.d = 51.4;
	ea[0].a = true; ea[0].b = 30; strcpy(ea[0].c,"cherry"); ea[0].d = 68.5;
	ea[1].a = false; ea[1].b = -10; strcpy(ea[1].c,"lime"); ea[1].d = 58.4;

	// allocate enough memory for five elements and only add four
	if(!da_reserve(h,5)) return 0;  
	da_push_back(h, &e1); // push back one element at a time
	da_push_back(h, &e2);
	da_insert(h,ea,da_size(h),2); // insert 2-element-array to position# "size" (back of array)

	// the dynamic array knows that only four elements e,
	// even though we allocated enough memory for five.
	int size = da_size(h);
	printf("\nsize: %d",size);
		
	int i; EXAMPLE* pEx;
	// Below, we retrieve the values by getting a pointer to each individual elemement.
	printf("\nRetrieving individual elements...");
	for (i = 0; i < size; i++)
	{
		pEx = da_data(h,i);
		if(i==1) strcpy(pEx->c,"whiskey"); // Let's modify a value.
		const char* tf;
		if (pEx->a) tf = "true";
		else tf = "false";
		printf("\ni: %d, %s, %d, %s, %.2f\n", i, tf, pEx->b, pEx->c, pEx->d);
	}

	// Actually, the array is contiguous, so you have the option of direct array access.
	printf("\nArray-style access...");
	pEx = da_data(h,0);
	strcpy(pEx[2].c,"fruit cake"); // Let's modify a value.
	for (i = 0; i < size; i++)
	{
		const char* tf;
		if (pEx[i].a) tf = "true";
		else tf = "false";
		printf("\ni: %d, %s, %d, %s, %.2f\n", i, tf, pEx[i].b, pEx[i].c, pEx[i].d);
	}
	
	// let's delete this dynamic array
	da_delete(h);
	
	// check if the dynamic array has been deleted...
	if(da_exists(h)) printf("\nDeletion unsuccessful.");
	else printf("\nDeletion successful.");
	
	printf("\ndemo1 complete!");
	
}

void demo2()
{
	printf("\nsizeof(int): %d",sizeof(int));
	
	// Let's make a dynamic array of ints.
	int h = da_new(sizeof(int));
	
	// Set the capacity of the array for 20.  The size will still be zero.
	da_reserve(h, 7);
	pr_int(h);
	
	// Here's an array of six ints.  Let's add them all at the same time.
	// The address does not move.  The less it moves, the faster your code.
	int a[6] = { 101, 102, 103, 104, 105, 106};
	da_insert(h,a, da_size(h), 6);
	pr_int(h);
	
	// Let's insert two more, right in the middle (3).  
	// We will exceed capacity, so the address will change, and size and capacity will increase.
	int b[2] = {201, 202};
	da_insert(h,b,da_size(h),2);
	pr_int(h);
	
	// Let's put more room in there.  This will also be a reallocation.
	da_reserve(h,30);
	pr_int(h);
	
	// Add three more to the back...
	int c[3] = {301, 302, 303};
	da_insert(h,c,da_size(h),3);
	pr_int(h);
	
	// Let's erase all but the first and the last elements.
	// Note that there is no reallocation.
	da_erase(h,1,da_size(h)-2);
	pr_int(h);
	
	// One more in the front...
	int d = 401;
	da_insert(h, &d, 0, 1);
	pr_int(h);
	
	// We are done with this dynamic array completely.  The handle should not be found after completion.
	da_delete(h);
	pr_int(h);
	
	printf("\ndemo2 complete!");
}




void pr_int(int handle)
{
	int sz = da_size(handle);
	if (!da_data(handle,0)) {
		printf("\nNo handle found!");
		return;
	}
	printf("\n%p: [", da_data(handle, 0)); // Take note of when the address changes... and why.

	int i;
	for (i = 0; i < sz; i++)
	{
		if (i) printf(",");
		int* pVal = (int*)da_data(handle, i);
		printf("%d",(*pVal));
	}
	printf("] (%d/%d)",da_size(handle),da_capacity(handle));
}




