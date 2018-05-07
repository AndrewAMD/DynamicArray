// For this example to work, dynamic.h needs to be in Zorro's include folder,
// and DynamicArray.dll must be in the Zorro main folder.


#include <dynamic.h>

typedef struct
{
	bool a;
	int b;
	char c[32];
	double d;

} EXAMPLE;


int main()
{
	printf("\n%d",sizeof(char));
	printf("\n%d",sizeof(EXAMPLE));
	
	int h = darr_new(sizeof(EXAMPLE));
	EXAMPLE e1, e2, e3, e4;
	memset(&e1, 0, sizeof(EXAMPLE));
	memset(&e2, 0, sizeof(EXAMPLE));
	memset(&e3, 0, sizeof(EXAMPLE));
	memset(&e4, 0, sizeof(EXAMPLE));

	e1.a = true; e1.b = 20; strcpy(e1.c,"banana"); e1.d = 24.5;
	e2.a = false; e2.b = -50; strcpy(e2.c,"orange"); e2.d = 51.4;
	e3.a = true; e3.b = 30; strcpy(e3.c,"cherry"); e3.d = 68.5;
	e4.a = false; e4.b = -10; strcpy(e4.c,"bud light lime"); e4.d = 58.4;

	darr_reserve(h,5);  // the memory will not reallocate until size exceeds five
	darr_push_back(h, &e1);
	darr_push_back(h, &e2);
	darr_push_back(h, &e3);
	darr_push_back(h, &e4);

	int size = darr_size(h);
	printf("\nsize: %d",size);
	// EXAMPLE* pEx = (EXAMPLE*)darr_pointer(h, 0);
	int i; EXAMPLE* pEx;
	for (i = 0; i < size; i++)
	{
		pEx = darr_pointer(h,i);
		const char* tf;
		if (pEx->a) tf = "true";
		else tf = "false";
		printf("\ni: %d, %s, %d, %s, %.2f\n", i, tf, pEx->b, pEx->c, pEx->d);
	}

	pEx = (EXAMPLE*)darr_pointer(h, 3);
	char* pExc = pEx[0].c;
	printf("\n");
	int j;
	for (j = 0; j < 32; j++)
	{
		char a[2]; a[1] = 0;
		a[0]= pExc[j];
		if (a[0] == '\0') a[0]='_';
		printf("%s",a);
	}
	//printf("\r\n");
	printf("\ndone!");
	return 0;
}
